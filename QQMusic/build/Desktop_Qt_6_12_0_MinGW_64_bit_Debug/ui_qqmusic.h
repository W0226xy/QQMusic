/********************************************************************************
** Form generated from reading UI file 'qqmusic.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QQMUSIC_H
#define UI_QQMUSIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <btform.h>
#include <commonpage.h>
#include <musicslider.h>
#include <recbox.h>

QT_BEGIN_NAMESPACE

class Ui_QQMusic
{
public:
    QWidget *background;
    QVBoxLayout *verticalLayout;
    QWidget *head;
    QHBoxLayout *horizontalLayout_2;
    QWidget *headLeft;
    QLabel *logo;
    QWidget *headRight;
    QHBoxLayout *horizontalLayout_3;
    QWidget *searchBox;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit;
    QWidget *settingBox;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *min;
    QPushButton *max;
    QPushButton *quit;
    QWidget *body;
    QHBoxLayout *horizontalLayout_6;
    QWidget *bodyLeft;
    QVBoxLayout *verticalLayout_2;
    QWidget *leftBox;
    QVBoxLayout *verticalLayout_3;
    QWidget *onlineMusic;
    QVBoxLayout *verticalLayout_4;
    QLabel *onlineMusicText;
    BtForm *rec;
    BtForm *radio;
    BtForm *music;
    QWidget *myMusic;
    QVBoxLayout *verticalLayout_5;
    QLabel *myMusicText;
    BtForm *like;
    BtForm *local;
    BtForm *recent;
    QSpacerItem *verticalSpacer;
    QWidget *bodyRight;
    QVBoxLayout *verticalLayout_6;
    QStackedWidget *stackedWidget;
    QWidget *recPage;
    QVBoxLayout *verticalLayout_8;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_7;
    QLabel *recText;
    QLabel *recMusic;
    RecBox *recMusicBox;
    QLabel *supplyMusicText;
    RecBox *supplyMusicBox;
    QWidget *radioPage;
    QLabel *label_5;
    QWidget *musicPage;
    QLabel *label_6;
    CommonPage *likePage;
    CommonPage *localPage;
    CommonPage *recentPage;
    MusicSlider *progressBar;
    QWidget *controlBox;
    QHBoxLayout *horizontalLayout_7;
    QWidget *play1;
    QLabel *musicCover;
    QLabel *musicName;
    QLabel *musicSinger;
    QWidget *play2;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *playMode;
    QPushButton *playUp;
    QPushButton *play;
    QPushButton *playDown;
    QPushButton *volume;
    QPushButton *addLocal;
    QWidget *play3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_12;
    QLabel *currentTime;
    QLabel *line;
    QLabel *totalTime;
    QPushButton *lrcWord;

    void setupUi(QWidget *QQMusic)
    {
        if (QQMusic->objectName().isEmpty())
            QQMusic->setObjectName("QQMusic");
        QQMusic->resize(1113, 848);
        background = new QWidget(QQMusic);
        background->setObjectName("background");
        background->setGeometry(QRect(9, 9, 1092, 822));
        background->setStyleSheet(QString::fromUtf8("#background {\n"
"    background-color: #FAFAFA;\n"
"    color: #202020;\n"
"}\n"
"\n"
"#headLeft, #bodyLeft {\n"
"    background-color: #F3F3F3;\n"
"}\n"
"\n"
"#headRight, #bodyRight, #controlBox, QStackedWidget, CommonPage {\n"
"    background-color: #FAFAFA;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: #202020;\n"
"}\n"
"\n"
"QPushButton {\n"
"    color: #202020;\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(background);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        head = new QWidget(background);
        head->setObjectName("head");
        head->setMinimumSize(QSize(0, 80));
        head->setMaximumSize(QSize(16777215, 80));
        head->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(head);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        headLeft = new QWidget(head);
        headLeft->setObjectName("headLeft");
        headLeft->setMinimumSize(QSize(200, 0));
        headLeft->setMaximumSize(QSize(200, 16777215));
        headLeft->setStyleSheet(QString::fromUtf8("#headLeft\n"
"{\n"
" background-color:#F3F3F3;/*\350\256\276\347\275\256\350\203\214\346\231\257\351\242\234\342\276\212\344\270\272\346\265\205\347\201\260\342\276\212*/\n"
"}"));
        logo = new QLabel(headLeft);
        logo->setObjectName("logo");
        logo->setGeometry(QRect(30, 20, 131, 41));
        logo->setStyleSheet(QString::fromUtf8("#logo\n"
"{\n"
" border-radius:0px;\n"
" background-image: url(:/images/Logo.png);\n"
" background-repeat:no-repeat;\n"
" border:none;\n"
" background-position:center center;\n"
"}"));

        horizontalLayout_2->addWidget(headLeft);

        headRight = new QWidget(head);
        headRight->setObjectName("headRight");
        headRight->setStyleSheet(QString::fromUtf8("#headRight\n"
"{\n"
" background-color:#FAFAFA; /*\350\256\276\347\275\256\350\203\214\346\231\257\351\242\234\342\276\212\344\270\272\344\272\256\347\201\260\342\276\212*/\n"
"}"));
        horizontalLayout_3 = new QHBoxLayout(headRight);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        searchBox = new QWidget(headRight);
        searchBox->setObjectName("searchBox");
        searchBox->setMinimumSize(QSize(300, 0));
        searchBox->setMaximumSize(QSize(300, 16777215));
        searchBox->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_4 = new QHBoxLayout(searchBox);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(5, 0, 5, 0);
        lineEdit = new QLineEdit(searchBox);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMinimumSize(QSize(0, 35));
        lineEdit->setMaximumSize(QSize(16777215, 35));
        lineEdit->setStyleSheet(QString::fromUtf8("#lineEdit\n"
"{\n"
" background-color: #EAEAEA; /*\350\256\276\347\275\256\350\203\214\346\231\257\351\242\234\342\276\212*/\n"
"border:none;\n"
" border-radius: 17px; /*\350\256\276\347\275\256\345\233\233\344\270\252\342\273\206\347\232\204\345\234\206\342\273\206*/\n"
" padding-left: 17px; /*\345\206\205\351\203\250\342\275\202\345\255\227\345\210\260\350\276\271\347\232\204\350\267\235\347\246\273*/\n"
"}"));

        horizontalLayout_4->addWidget(lineEdit);


        horizontalLayout_3->addWidget(searchBox);

        settingBox = new QWidget(headRight);
        settingBox->setObjectName("settingBox");
        settingBox->setStyleSheet(QString::fromUtf8("/* \347\261\273\345\236\213\351\200\211\346\213\251\345\231\250 */\n"
"QPushButton\n"
"{\n"
" border-radius:0px; /*\350\256\276\347\275\256\346\214\211\351\222\256\347\232\204\350\276\271\346\241\206\345\234\206\342\273\206\344\270\272 0 \345\203\217\347\264\240\357\274\214\n"
"\345\256\236\347\216\260\347\233\264\342\273\206\350\276\271\347\274\230*/\n"
" background-repeat:no-repeat; /* \350\203\214\346\231\257\345\233\276\342\275\232\344\270\215\351\207\215\345\244\215\345\271\263\351\223\272\n"
"*/\n"
" border: none; /*\342\275\206\350\276\271\346\241\206*/\n"
" background-position:center center; /*\350\203\214\346\231\257\345\233\276\342\275\232\346\224\276\347\275\256\345\234\250\n"
"\346\214\211\351\222\256\347\232\204\344\270\255\342\274\274\344\275\215\347\275\256*/\n"
"}\n"
"/*\346\202\254\345\201\234\347\212\266\346\200\201*/\n"
"QPushButton:hover\n"
"{\n"
" background-color: rgba(230,0,0,0.5); /*\350\256\276\347\275\256\350\203\214\346\231\257\351\242\234\n"
"\342\276\212\344\270\272\345\215\212\351"
                        "\200\217\346\230\216\347\232\204\347\272\242\342\276\212*/\n"
"}"));
        horizontalLayout_5 = new QHBoxLayout(settingBox);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer = new QSpacerItem(466, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        min = new QPushButton(settingBox);
        min->setObjectName("min");
        min->setMinimumSize(QSize(30, 0));
        min->setMaximumSize(QSize(30, 16777215));
        min->setStyleSheet(QString::fromUtf8("background-image: url(:/images/min.png);"));

        horizontalLayout_5->addWidget(min);

        max = new QPushButton(settingBox);
        max->setObjectName("max");
        max->setMinimumSize(QSize(30, 0));
        max->setMaximumSize(QSize(30, 16777215));
        max->setStyleSheet(QString::fromUtf8("background-image: url(:/images/max.png);"));

        horizontalLayout_5->addWidget(max);

        quit = new QPushButton(settingBox);
        quit->setObjectName("quit");
        quit->setMinimumSize(QSize(30, 0));
        quit->setMaximumSize(QSize(30, 16777215));
        quit->setStyleSheet(QString::fromUtf8("background-image: url(:/images/quit.png);"));

        horizontalLayout_5->addWidget(quit);


        horizontalLayout_3->addWidget(settingBox);


        horizontalLayout_2->addWidget(headRight);


        verticalLayout->addWidget(head);

        body = new QWidget(background);
        body->setObjectName("body");
        body->setMaximumSize(QSize(16777215, 16777215));
        body->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_6 = new QHBoxLayout(body);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        bodyLeft = new QWidget(body);
        bodyLeft->setObjectName("bodyLeft");
        bodyLeft->setMinimumSize(QSize(200, 0));
        bodyLeft->setMaximumSize(QSize(200, 16777215));
        bodyLeft->setStyleSheet(QString::fromUtf8("#bodyLeft\n"
"{\n"
" background-color:#F3F3F3;/*\350\256\276\347\275\256\350\203\214\346\231\257\351\242\234\342\276\212\344\270\272\346\265\205\347\201\260\342\276\212*/\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(bodyLeft);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        leftBox = new QWidget(bodyLeft);
        leftBox->setObjectName("leftBox");
        leftBox->setMinimumSize(QSize(0, 400));
        leftBox->setMaximumSize(QSize(16777215, 400));
        leftBox->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(leftBox);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        onlineMusic = new QWidget(leftBox);
        onlineMusic->setObjectName("onlineMusic");
        onlineMusic->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_4 = new QVBoxLayout(onlineMusic);
        verticalLayout_4->setObjectName("verticalLayout_4");
        onlineMusicText = new QLabel(onlineMusic);
        onlineMusicText->setObjectName("onlineMusicText");

        verticalLayout_4->addWidget(onlineMusicText);

        rec = new BtForm(onlineMusic);
        rec->setObjectName("rec");
        rec->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_4->addWidget(rec);

        radio = new BtForm(onlineMusic);
        radio->setObjectName("radio");
        radio->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_4->addWidget(radio);

        music = new BtForm(onlineMusic);
        music->setObjectName("music");
        music->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_4->addWidget(music);


        verticalLayout_3->addWidget(onlineMusic);

        myMusic = new QWidget(leftBox);
        myMusic->setObjectName("myMusic");
        myMusic->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_5 = new QVBoxLayout(myMusic);
        verticalLayout_5->setObjectName("verticalLayout_5");
        myMusicText = new QLabel(myMusic);
        myMusicText->setObjectName("myMusicText");

        verticalLayout_5->addWidget(myMusicText);

        like = new BtForm(myMusic);
        like->setObjectName("like");
        like->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_5->addWidget(like);

        local = new BtForm(myMusic);
        local->setObjectName("local");
        local->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_5->addWidget(local);

        recent = new BtForm(myMusic);
        recent->setObjectName("recent");
        recent->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_5->addWidget(recent);


        verticalLayout_3->addWidget(myMusic);


        verticalLayout_2->addWidget(leftBox);

        verticalSpacer = new QSpacerItem(20, 342, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_6->addWidget(bodyLeft);

        bodyRight = new QWidget(body);
        bodyRight->setObjectName("bodyRight");
        bodyRight->setStyleSheet(QString::fromUtf8("#bodyRight\n"
"{\n"
" background-color:#FAFAFA; /*\350\256\276\347\275\256\350\203\214\346\231\257\351\242\234\342\276\212\344\270\272\344\272\256\347\201\260\342\276\212*/\n"
"}"));
        verticalLayout_6 = new QVBoxLayout(bodyRight);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(bodyRight);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setMinimumSize(QSize(0, 30));
        stackedWidget->setMaximumSize(QSize(16777215, 16777215));
        recPage = new QWidget();
        recPage->setObjectName("recPage");
        recPage->setStyleSheet(QString::fromUtf8("background-color: #FAFAFA;"));
        verticalLayout_8 = new QVBoxLayout(recPage);
        verticalLayout_8->setObjectName("verticalLayout_8");
        scrollArea = new QScrollArea(recPage);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setMinimumSize(QSize(0, 0));
        scrollArea->setStyleSheet(QString::fromUtf8("#scrollArea {\n"
"    background-color: #FAFAFA;\n"
"    border: none;\n"
"}\n"
"\n"
"#scrollArea QScrollBar:vertical {\n"
"    width: 10px;\n"
"    margin: 6px 2px 6px 2px;\n"
"    background: transparent;\n"
"}\n"
"\n"
"#scrollArea QScrollBar::handle:vertical {\n"
"    min-height: 48px;\n"
"    border-radius: 3px;\n"
"    background: #D5D9DC;\n"
"}\n"
"\n"
"#scrollArea QScrollBar::handle:vertical:hover {\n"
"    background: #AEB5BA;\n"
"}\n"
"\n"
"#scrollArea QScrollBar::handle:vertical:pressed {\n"
"    background: #1ECD97;\n"
"}\n"
"\n"
"#scrollArea QScrollBar::add-line:vertical,\n"
"#scrollArea QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"    border: none;\n"
"    background: transparent;\n"
"}\n"
"\n"
"#scrollArea QScrollBar::add-page:vertical,\n"
"#scrollArea QScrollBar::sub-page:vertical {\n"
"    background: transparent;\n"
"}"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 874, 634));
        scrollAreaWidgetContents->setMinimumSize(QSize(820, 500));
        scrollAreaWidgetContents->setStyleSheet(QString::fromUtf8("background-color: #FAFAFA;"));
        verticalLayout_7 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_7->setObjectName("verticalLayout_7");
        recText = new QLabel(scrollAreaWidgetContents);
        recText->setObjectName("recText");
        recText->setMinimumSize(QSize(0, 50));
        recText->setMaximumSize(QSize(16777215, 50));
        QFont font;
        font.setPointSize(24);
        recText->setFont(font);

        verticalLayout_7->addWidget(recText);

        recMusic = new QLabel(scrollAreaWidgetContents);
        recMusic->setObjectName("recMusic");
        recMusic->setMinimumSize(QSize(0, 30));
        recMusic->setMaximumSize(QSize(16777215, 30));
        QFont font1;
        font1.setPointSize(18);
        recMusic->setFont(font1);

        verticalLayout_7->addWidget(recMusic);

        recMusicBox = new RecBox(scrollAreaWidgetContents);
        recMusicBox->setObjectName("recMusicBox");
        recMusicBox->setMinimumSize(QSize(0, 50));
        recMusicBox->setMaximumSize(QSize(16777215, 1677216));

        verticalLayout_7->addWidget(recMusicBox);

        supplyMusicText = new QLabel(scrollAreaWidgetContents);
        supplyMusicText->setObjectName("supplyMusicText");
        supplyMusicText->setMinimumSize(QSize(0, 30));
        supplyMusicText->setMaximumSize(QSize(16777215, 30));
        supplyMusicText->setFont(font1);

        verticalLayout_7->addWidget(supplyMusicText);

        supplyMusicBox = new RecBox(scrollAreaWidgetContents);
        supplyMusicBox->setObjectName("supplyMusicBox");
        supplyMusicBox->setMinimumSize(QSize(0, 50));
        supplyMusicBox->setMaximumSize(QSize(16777215, 1677215));

        verticalLayout_7->addWidget(supplyMusicBox);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_8->addWidget(scrollArea);

        stackedWidget->addWidget(recPage);
        radioPage = new QWidget();
        radioPage->setObjectName("radioPage");
        label_5 = new QLabel(radioPage);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(330, 230, 54, 12));
        stackedWidget->addWidget(radioPage);
        musicPage = new QWidget();
        musicPage->setObjectName("musicPage");
        label_6 = new QLabel(musicPage);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(390, 240, 54, 12));
        stackedWidget->addWidget(musicPage);
        likePage = new CommonPage();
        likePage->setObjectName("likePage");
        stackedWidget->addWidget(likePage);
        localPage = new CommonPage();
        localPage->setObjectName("localPage");
        stackedWidget->addWidget(localPage);
        recentPage = new CommonPage();
        recentPage->setObjectName("recentPage");
        stackedWidget->addWidget(recentPage);

        verticalLayout_6->addWidget(stackedWidget);

        progressBar = new MusicSlider(bodyRight);
        progressBar->setObjectName("progressBar");
        progressBar->setMinimumSize(QSize(0, 30));
        progressBar->setMaximumSize(QSize(16777215, 30));
        progressBar->setStyleSheet(QString::fromUtf8("background-color:rgb(173, 173, 173)"));

        verticalLayout_6->addWidget(progressBar);

        controlBox = new QWidget(bodyRight);
        controlBox->setObjectName("controlBox");
        controlBox->setMinimumSize(QSize(0, 60));
        controlBox->setMaximumSize(QSize(16777215, 60));
        controlBox->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_7 = new QHBoxLayout(controlBox);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 5);
        play1 = new QWidget(controlBox);
        play1->setObjectName("play1");
        play1->setStyleSheet(QString::fromUtf8(""));
        musicCover = new QLabel(play1);
        musicCover->setObjectName("musicCover");
        musicCover->setGeometry(QRect(30, 10, 60, 60));
        musicCover->setMinimumSize(QSize(60, 60));
        musicCover->setMaximumSize(QSize(60, 60));
        musicName = new QLabel(play1);
        musicName->setObjectName("musicName");
        musicName->setGeometry(QRect(140, 10, 131, 16));
        musicSinger = new QLabel(play1);
        musicSinger->setObjectName("musicSinger");
        musicSinger->setGeometry(QRect(140, 20, 131, 16));

        horizontalLayout_7->addWidget(play1);

        play2 = new QWidget(controlBox);
        play2->setObjectName("play2");
        play2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
" border: none; /* \345\216\273\351\231\244\350\276\271\346\241\206 */\n"
" background-repeat:no-repeat;\n"
"background-position:center center\n"
"}\n"
"/*\346\202\254\345\201\234\347\212\266\346\200\201*/\n"
"QPushButton:hover\n"
"{\n"
" /*\350\256\276\347\275\256\350\203\214\346\231\257\351\242\234\342\276\212\344\270\272\345\215\212\351\200\217\346\230\216\347\232\204\347\272\242\342\276\212*/\n"
" background-color: rgba(220,220,220,0.5); \n"
"}\n"
""));
        horizontalLayout_8 = new QHBoxLayout(play2);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        playMode = new QPushButton(play2);
        playMode->setObjectName("playMode");
        playMode->setMinimumSize(QSize(30, 30));
        playMode->setMaximumSize(QSize(30, 30));
        playMode->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_8->addWidget(playMode);

        playUp = new QPushButton(play2);
        playUp->setObjectName("playUp");
        playUp->setMinimumSize(QSize(30, 30));
        playUp->setMaximumSize(QSize(30, 30));
        playUp->setStyleSheet(QString::fromUtf8("#playUp\n"
"{\n"
" background-image: url(:/images/up.png);\n"
"}"));

        horizontalLayout_8->addWidget(playUp);

        play = new QPushButton(play2);
        play->setObjectName("play");
        play->setMinimumSize(QSize(30, 30));
        play->setMaximumSize(QSize(30, 30));
        play->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_8->addWidget(play);

        playDown = new QPushButton(play2);
        playDown->setObjectName("playDown");
        playDown->setMinimumSize(QSize(30, 30));
        playDown->setMaximumSize(QSize(30, 30));
        playDown->setStyleSheet(QString::fromUtf8("#playDown\n"
"{\n"
" background-image: url(:/images/down.png);\n"
"}"));

        horizontalLayout_8->addWidget(playDown);

        volume = new QPushButton(play2);
        volume->setObjectName("volume");
        volume->setMinimumSize(QSize(30, 30));
        volume->setMaximumSize(QSize(30, 30));
        volume->setStyleSheet(QString::fromUtf8("#volume\n"
"{\n"
" background-image: url(:/images/volumn.png);\n"
"}"));

        horizontalLayout_8->addWidget(volume);

        addLocal = new QPushButton(play2);
        addLocal->setObjectName("addLocal");
        addLocal->setMinimumSize(QSize(30, 30));
        addLocal->setMaximumSize(QSize(30, 30));
        addLocal->setStyleSheet(QString::fromUtf8("#addLocal\n"
"{\n"
" background-image: url(:/images/add.png);\n"
"}"));

        horizontalLayout_8->addWidget(addLocal);


        horizontalLayout_7->addWidget(play2);

        play3 = new QWidget(controlBox);
        play3->setObjectName("play3");
        play3->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_9 = new QHBoxLayout(play3);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_12 = new QLabel(play3);
        label_12->setObjectName("label_12");
        label_12->setMinimumSize(QSize(100, 0));
        label_12->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_9->addWidget(label_12);

        currentTime = new QLabel(play3);
        currentTime->setObjectName("currentTime");
        currentTime->setMinimumSize(QSize(30, 0));
        currentTime->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_9->addWidget(currentTime);

        line = new QLabel(play3);
        line->setObjectName("line");
        line->setMinimumSize(QSize(10, 0));
        line->setMaximumSize(QSize(10, 16777215));

        horizontalLayout_9->addWidget(line);

        totalTime = new QLabel(play3);
        totalTime->setObjectName("totalTime");
        totalTime->setMinimumSize(QSize(30, 0));

        horizontalLayout_9->addWidget(totalTime);

        lrcWord = new QPushButton(play3);
        lrcWord->setObjectName("lrcWord");
        lrcWord->setMinimumSize(QSize(30, 0));
        lrcWord->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_9->addWidget(lrcWord);


        horizontalLayout_7->addWidget(play3);


        verticalLayout_6->addWidget(controlBox);


        horizontalLayout_6->addWidget(bodyRight);


        verticalLayout->addWidget(body);


        retranslateUi(QQMusic);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QQMusic);
    } // setupUi

    void retranslateUi(QWidget *QQMusic)
    {
        QQMusic->setWindowTitle(QCoreApplication::translate("QQMusic", "QQMusic", nullptr));
        logo->setText(QString());
        min->setText(QString());
        max->setText(QString());
        quit->setText(QString());
        onlineMusicText->setText(QCoreApplication::translate("QQMusic", "\345\234\250\347\272\277\351\237\263\344\271\220", nullptr));
        myMusicText->setText(QCoreApplication::translate("QQMusic", "\346\210\221\347\232\204\351\237\263\344\271\220", nullptr));
        recText->setText(QCoreApplication::translate("QQMusic", "\346\216\250\350\215\220", nullptr));
        recMusic->setText(QCoreApplication::translate("QQMusic", "\344\273\212\346\227\245\344\270\272\344\275\240\346\216\250\350\215\220", nullptr));
        supplyMusicText->setText(QCoreApplication::translate("QQMusic", "\344\275\240\347\232\204\351\237\263\344\271\220\350\241\245\347\273\231", nullptr));
        label_5->setText(QCoreApplication::translate("QQMusic", "radio", nullptr));
        label_6->setText(QCoreApplication::translate("QQMusic", "Music", nullptr));
        musicCover->setText(QString());
        musicName->setText(QCoreApplication::translate("QQMusic", "\346\255\214\346\233\262", nullptr));
        musicSinger->setText(QCoreApplication::translate("QQMusic", "\346\255\214\346\211\213", nullptr));
        playMode->setText(QString());
        playUp->setText(QString());
        play->setText(QString());
        playDown->setText(QString());
        volume->setText(QString());
        addLocal->setText(QString());
        label_12->setText(QString());
        currentTime->setText(QCoreApplication::translate("QQMusic", "00:00", nullptr));
        line->setText(QCoreApplication::translate("QQMusic", "/", nullptr));
        totalTime->setText(QCoreApplication::translate("QQMusic", "00:00", nullptr));
        lrcWord->setText(QCoreApplication::translate("QQMusic", "\350\257\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QQMusic: public Ui_QQMusic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QQMUSIC_H
