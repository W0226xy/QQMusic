# QQMusic（Qt 6 Widgets）

本项目支持本地音乐播放，以及通过 Jamendo 官方 API 展示和播放合法的在线独立音乐。推荐页启动时自动加载 12 首歌曲，其中“今日为你推荐”显示 4 首，“你的音乐补给”显示 8 首；点击卡片即可播放，点击“刷新推荐”可换一批。

## 配置 Jamendo

1. 在 [Jamendo Developer](https://devportal.jamendo.com/) 注册应用并获取 `client_id`。
2. 不要把 `client_id` 写进源码。程序只读取环境变量 `JAMENDO_CLIENT_ID`。

在 Windows PowerShell 中临时设置（仅对当前终端及其启动的程序生效）：

```powershell
$env:JAMENDO_CLIENT_ID="你的client_id"
```

如果从 Qt Creator 启动，请打开项目的 **Projects（项目）→ Run（运行）→ Environment（环境）**，添加：

```text
JAMENDO_CLIENT_ID=你的client_id
```

未配置该变量时程序仍可正常启动并使用本地音乐，推荐页会显示明确的配置提示。

## 构建

工程需要 Qt 6 的 Widgets、Multimedia、Network 和 SQL 模块。环境变量改变后需要重新启动应用；工程文件改变后请重新运行 qmake：

```powershell
qmake QQMusic.pro
nmake
```

MinGW 工具链通常使用：

```powershell
qmake QQMusic.pro
mingw32-make
```

也可以在 Qt Creator 中执行 **Build → Run qmake**，再执行 **Rebuild Project**。

## 说明

- 在线歌曲和封面依赖网络可用性。
- Jamendo 曲库以独立音乐为主。
- 在线推荐只保存在当前运行时播放队列中，不会写入本地 SQLite 数据库，也不会尝试读取本地歌词文件。
- 刷新失败时会保留当前推荐内容；连续点击刷新不会创建并发请求。
