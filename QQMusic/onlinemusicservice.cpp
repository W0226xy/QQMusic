#include "onlinemusicservice.h"

//解析服务器返回的 JSON 数据
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
//封装“我要请求哪个 URL、携带哪些请求头”。
#include <QNetworkReply>
//这一次请求的响应”，里面有状态码、返回数据、错误信息等
#include <QNetworkRequest>
//生成随机偏移量，让每次刷新更可能得到不同歌曲。
#include <QRandomGenerator>
//安全地拼接 URL 参数，自动处理空格、中文等特殊字符编码
#include <QUrlQuery>

//向 Jamendo 音乐接口发请求，解析返回的 JSON，然后把可播放歌曲通过 tracksReady 信号交给推荐页面
//这段实现的核心优点是：网络逻辑完全封装在服务类中，推荐页面不需要直接处理 HTTP、超时、JSON 或错误判断，只需要接收两个结果：
//1.tracksReady(tracks);       // 成功，显示歌曲
//2.requestFailed(message);    // 失败，显示提示

OnlineMusicService::OnlineMusicService(QObject *parent)//调用父类 QObject 的构造函数，并将 parent 传进去，使 Qt 的对象树机制能够管理这个对象的生命周期。
    : QObject(parent)
{
    timeoutTimer.setSingleShot(true);//计时到达后只执行一次，后续不会重复计时
    timeoutTimer.setInterval(12000);//超时时间为 12000 毫秒，即 12 秒
    //connect：//参数1：谁发射信号 参数2：发射了什么信号 参数3：谁处理 参数4：处理的槽函数
    //定时器如果超时，会强制取消当前网络请求
    connect(&timeoutTimer, &QTimer::timeout, this, [this]() {
        if (activeReply)
            activeReply->abort();
    });
}

//返回当前是否正在加载歌曲。
bool OnlineMusicService::isLoading() const
{
    return loading;
}

//发起在线歌曲请求
void OnlineMusicService::fetchTracks(int limit, int offset)
{
    //如果正在加载，直接返回，防止用户快速点击了刷新歌曲，多个请求覆盖
    if (loading)
        return;

    //从系统环境变量中读取 JAMENDO_CLIENT_ID
    const QString clientId = qEnvironmentVariable("JAMENDO_CLIENT_ID").trimmed();
    if (clientId.isEmpty()) {
        //如果没有配置 Client ID，就发出失败信号，让界面提示用户
        emit requestFailed(QStringLiteral(
            "未配置 JAMENDO_CLIENT_ID。请在 PowerShell 中设置 "
            "$env:JAMENDO_CLIENT_ID=\"你的client_id\" 后重新启动应用。"));
        return;
    }

    //修改加载状态与请求编号
    loading = true;
    emit loadingChanged(true);
    const quint64 serial = ++requestSerial;//每次发请求，请求编号加一，并记录当前请求自己的编号
    //它的目的是防止旧请求的结果覆盖新请求。后面收到响应时会验证：serial != requestSerial
    //若不相等，说明这个回复已经过期，就忽略它。

    //拼接 Jamendo 请求地址
    //基础接口地址：https://api.jamendo.com/v3.0/tracks/
    QUrl url(QStringLiteral("https://api.jamendo.com/v3.0/tracks/"));
    //query 用来添加 URL 参数。
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("client_id"), clientId);//添加api身份标识
    query.addQueryItem(QStringLiteral("format"), QStringLiteral("json"));//要求返回json数据
    query.addQueryItem(QStringLiteral("limit"), QString::number(qBound(1, limit, 200)));//限制歌曲请求数量
    //除非指定offset，否则在0-4999之间随机选一个偏移量，找不同位置的歌曲
    const int requestOffset = offset >= 0
            ? offset : QRandomGenerator::global()->bounded(0, 5000);
    query.addQueryItem(QStringLiteral("offset"), QString::number(requestOffset));
    //按一周流行音乐热度排行
    query.addQueryItem(QStringLiteral("order"), QStringLiteral("popularity_week"));
    //音频格式mp3
    query.addQueryItem(QStringLiteral("audioformat"), QStringLiteral("mp32"));
    //封面图300像素
    query.addQueryItem(QStringLiteral("imagesize"), QStringLiteral("300"));
    // Jamendo 的有效枚举是 single 和 albumtrack；空格表示同时请求两类。
    // 交给 QUrlQuery 编码，不能用旧写法 album+single。
    query.addQueryItem(QStringLiteral("type"), QStringLiteral("single albumtrack"));//请求单曲/专辑内歌曲
    url.setQuery(query);

    //发送网络请求，用刚才拼接的URL请求对象
    QNetworkRequest request(url);
    //设置 User-Agent：QQMusic-Qt/1.0 ，服务器可以知道请求来自哪个客户端
    request.setHeader(QNetworkRequest::UserAgentHeader, QStringLiteral("QQMusic-Qt/1.0"));
    //QT网络层设置12s超时，超时后自动调用abort()
    request.setTransferTimeout(12000);
    //发送 GET 请求，并保存当前响应对象；然后启动超时计时器。
    activeReply = manager.get(request);
    timeoutTimer.start();

    //请求结束后回调
    //connect：//参数1：谁发射信号 参数2：发射了什么信号 参数3：谁处理 参数4：处理的槽函数
    connect(activeReply, &QNetworkReply::finished, this, [this, serial]() {
        QNetworkReply *reply = activeReply.data();
        if (!reply || serial != requestSerial)//请求不存在，或者是旧请求，不再处理
            return;
        //请求完成，不需要触发超时
        timeoutTimer.stop();
        //从响应中取出：
        const QNetworkReply::NetworkError networkError = reply->error();//网络错误码；
        const int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//HTTP 状态码，例如 200、401、500；
        const QByteArray body = reply->readAll();//返回的完整内容；
        const QString errorText = reply->errorString();//可读的错误描述
        reply->deleteLater();//deleteLater()：让 Qt 在合适的事件循环时机销毁响应对象
        activeReply = nullptr;//清空当前请求指针
        finishRequest();//调用 finishRequest()，将加载状态恢复为 false

        //如果网络层出错，例如没网、DNS 解析失败、超时等。
        if (networkError != QNetworkReply::NoError) {
            const QString reason = networkError == QNetworkReply::OperationCanceledError
                    ? QStringLiteral("请求超时") : errorText;
            emit requestFailed(QStringLiteral("获取在线推荐失败：%1").arg(reason));
            return;
        }
        //第二层失败：HTTP 状态异常
        //401：身份认证失败；
        //403：没有权限；
        //404：接口不存在；
        //429：请求过于频繁；
        //500：服务器内部错误。
        if (status < 200 || status >= 300) {
            emit requestFailed(QStringLiteral("Jamendo 返回 HTTP %1").arg(status));
            return;
        }

        //返回内容不是合法JSON
        QJsonParseError parseError;
        const QJsonDocument document = QJsonDocument::fromJson(body, &parseError);
        if (parseError.error != QJsonParseError::NoError || !document.isObject()) {
            emit requestFailed(QStringLiteral("Jamendo 返回的数据无法解析：%1")
                               .arg(parseError.errorString()));
            return;
        }

        //检查 Jamendo 的业务错误，比如Client id无效
        const QJsonObject root = document.object();
        const QJsonObject headers = root.value(QStringLiteral("headers")).toObject();
        if (headers.value(QStringLiteral("status")).toString() == QStringLiteral("failed")) {
            emit requestFailed(QStringLiteral("Jamendo API 错误：%1")
                               .arg(headers.value(QStringLiteral("error_message")).toString()));
            return;
        }

        //将 JSON 歌曲转换为 OnlineTrack
        QList<OnlineTrack> tracks;
        //从 JSON 的 results 数组中取出歌曲列表。
        const QJsonArray results = root.value(QStringLiteral("results")).toArray();
        for (const QJsonValue &value : results) {
            const QJsonObject object = value.toObject();
            OnlineTrack track;
            track.id = object.value(QStringLiteral("id")).toString();//歌曲id
            track.name = object.value(QStringLiteral("name")).toString();//歌曲名称
            track.artist = object.value(QStringLiteral("artist_name")).toString();//歌手
            track.album = object.value(QStringLiteral("album_name")).toString();//专辑
            track.audioUrl = QUrl(object.value(QStringLiteral("audio")).toString());//在线音频播放地址
            track.coverUrl = QUrl(object.value(QStringLiteral("image")).toString());//封面地址
            track.duration = object.value(QStringLiteral("duration")).toVariant().toLongLong() * 1000;//时长
            //过滤掉信息不完整的歌曲
            if (!track.id.isEmpty() && !track.name.isEmpty() && track.audioUrl.isValid()
                    && track.audioUrl.scheme().startsWith(QStringLiteral("http"))) {
                tracks.append(track);
            }
        }
        //如果接口有返回，但过滤后没有任何可播放歌曲，则提示用户重试。
        if (tracks.isEmpty()) {
            emit requestFailed(QStringLiteral("Jamendo 没有返回可播放的歌曲，请稍后重试。"));
            return;
        }
        //成功时，发出歌曲列表信号。推荐页面只要连接这个信号，就能刷新歌曲卡片，并把 audioUrl 交给播放器播放。
        emit tracksReady(tracks);
    });
}

//统一结束加载状态，避免重复结束请求
void OnlineMusicService::finishRequest()
{
    //当前加载状态已结束，直接返回
    if (!loading)
        return;
    //加载状态设置为false，并通知界面恢复可操作状态
    loading = false;
    emit loadingChanged(false);
}
