#include "onlinemusicservice.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QRandomGenerator>
#include <QUrlQuery>

OnlineMusicService::OnlineMusicService(QObject *parent)
    : QObject(parent)
{
    timeoutTimer.setSingleShot(true);
    timeoutTimer.setInterval(12000);
    connect(&timeoutTimer, &QTimer::timeout, this, [this]() {
        if (activeReply)
            activeReply->abort();
    });
}

bool OnlineMusicService::isLoading() const
{
    return loading;
}

void OnlineMusicService::fetchTracks(int limit, int offset)
{
    if (loading)
        return;

    const QString clientId = qEnvironmentVariable("JAMENDO_CLIENT_ID").trimmed();
    if (clientId.isEmpty()) {
        emit requestFailed(QStringLiteral(
            "未配置 JAMENDO_CLIENT_ID。请在 PowerShell 中设置 "
            "$env:JAMENDO_CLIENT_ID=\"你的client_id\" 后重新启动应用。"));
        return;
    }

    loading = true;
    emit loadingChanged(true);
    const quint64 serial = ++requestSerial;

    QUrl url(QStringLiteral("https://api.jamendo.com/v3.0/tracks/"));
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("client_id"), clientId);
    query.addQueryItem(QStringLiteral("format"), QStringLiteral("json"));
    query.addQueryItem(QStringLiteral("limit"), QString::number(qBound(1, limit, 200)));
    const int requestOffset = offset >= 0
            ? offset : QRandomGenerator::global()->bounded(0, 5000);
    query.addQueryItem(QStringLiteral("offset"), QString::number(requestOffset));
    query.addQueryItem(QStringLiteral("order"), QStringLiteral("popularity_week"));
    query.addQueryItem(QStringLiteral("audioformat"), QStringLiteral("mp32"));
    query.addQueryItem(QStringLiteral("imagesize"), QStringLiteral("300"));
    // Jamendo 的有效枚举是 single 和 albumtrack；空格表示同时请求两类。
    // 交给 QUrlQuery 编码，不能用旧写法 album+single。
    query.addQueryItem(QStringLiteral("type"), QStringLiteral("single albumtrack"));
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, QStringLiteral("QQMusic-Qt/1.0"));
    request.setTransferTimeout(12000);
    activeReply = manager.get(request);
    timeoutTimer.start();

    connect(activeReply, &QNetworkReply::finished, this, [this, serial]() {
        QNetworkReply *reply = activeReply.data();
        if (!reply || serial != requestSerial)
            return;

        timeoutTimer.stop();
        const QNetworkReply::NetworkError networkError = reply->error();
        const int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        const QByteArray body = reply->readAll();
        const QString errorText = reply->errorString();
        reply->deleteLater();
        activeReply = nullptr;
        finishRequest();

        if (networkError != QNetworkReply::NoError) {
            const QString reason = networkError == QNetworkReply::OperationCanceledError
                    ? QStringLiteral("请求超时") : errorText;
            emit requestFailed(QStringLiteral("获取在线推荐失败：%1").arg(reason));
            return;
        }
        if (status < 200 || status >= 300) {
            emit requestFailed(QStringLiteral("Jamendo 返回 HTTP %1").arg(status));
            return;
        }

        QJsonParseError parseError;
        const QJsonDocument document = QJsonDocument::fromJson(body, &parseError);
        if (parseError.error != QJsonParseError::NoError || !document.isObject()) {
            emit requestFailed(QStringLiteral("Jamendo 返回的数据无法解析：%1")
                               .arg(parseError.errorString()));
            return;
        }

        const QJsonObject root = document.object();
        const QJsonObject headers = root.value(QStringLiteral("headers")).toObject();
        if (headers.value(QStringLiteral("status")).toString() == QStringLiteral("failed")) {
            emit requestFailed(QStringLiteral("Jamendo API 错误：%1")
                               .arg(headers.value(QStringLiteral("error_message")).toString()));
            return;
        }

        QList<OnlineTrack> tracks;
        const QJsonArray results = root.value(QStringLiteral("results")).toArray();
        for (const QJsonValue &value : results) {
            const QJsonObject object = value.toObject();
            OnlineTrack track;
            track.id = object.value(QStringLiteral("id")).toString();
            track.name = object.value(QStringLiteral("name")).toString();
            track.artist = object.value(QStringLiteral("artist_name")).toString();
            track.album = object.value(QStringLiteral("album_name")).toString();
            track.audioUrl = QUrl(object.value(QStringLiteral("audio")).toString());
            track.coverUrl = QUrl(object.value(QStringLiteral("image")).toString());
            track.duration = object.value(QStringLiteral("duration")).toVariant().toLongLong() * 1000;
            if (!track.id.isEmpty() && !track.name.isEmpty() && track.audioUrl.isValid()
                    && track.audioUrl.scheme().startsWith(QStringLiteral("http"))) {
                tracks.append(track);
            }
        }

        if (tracks.isEmpty()) {
            emit requestFailed(QStringLiteral("Jamendo 没有返回可播放的歌曲，请稍后重试。"));
            return;
        }
        emit tracksReady(tracks);
    });
}

void OnlineMusicService::finishRequest()
{
    if (!loading)
        return;
    loading = false;
    emit loadingChanged(false);
}
