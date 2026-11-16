/********************************************************************************
** Form generated from reading UI file 'commonpage.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMONPAGE_H
#define UI_COMMONPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CommonPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *PageTittle;
    QWidget *musicPlayBox;
    QHBoxLayout *horizontalLayout;
    QLabel *musicImageLabel;
    QWidget *playAll;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *playAllBtn;
    QSpacerItem *horizontalSpacer;
    QWidget *listLabelBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *musicNameLabel;
    QLabel *musicSingerLabel;
    QLabel *musicAlbumLabel;
    QListWidget *pageMusicList;

    void setupUi(QWidget *CommonPage)
    {
        if (CommonPage->objectName().isEmpty())
            CommonPage->setObjectName("CommonPage");
        CommonPage->resize(800, 500);
        verticalLayout = new QVBoxLayout(CommonPage);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 9, 0);
        PageTittle = new QLabel(CommonPage);
        PageTittle->setObjectName("PageTittle");
        PageTittle->setMinimumSize(QSize(0, 30));
        PageTittle->setMaximumSize(QSize(16777215, 30));

        verticalLayout->addWidget(PageTittle);

        musicPlayBox = new QWidget(CommonPage);
        musicPlayBox->setObjectName("musicPlayBox");
        musicPlayBox->setMinimumSize(QSize(0, 170));
        musicPlayBox->setMaximumSize(QSize(16777215, 170));
        musicPlayBox->setStyleSheet(QString::fromUtf8("#PageTittle, #listLabelBox QLabel {\n"
"    color: #202020;\n"
"}"));
        horizontalLayout = new QHBoxLayout(musicPlayBox);
        horizontalLayout->setObjectName("horizontalLayout");
        musicImageLabel = new QLabel(musicPlayBox);
        musicImageLabel->setObjectName("musicImageLabel");
        musicImageLabel->setMinimumSize(QSize(150, 0));
        musicImageLabel->setMaximumSize(QSize(150, 16777215));
        musicImageLabel->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(musicImageLabel);

        playAll = new QWidget(musicPlayBox);
        playAll->setObjectName("playAll");
        playAll->setMinimumSize(QSize(120, 0));
        playAll->setMaximumSize(QSize(120, 16777215));
        playAll->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(playAll);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer = new QSpacerItem(20, 75, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        playAllBtn = new QPushButton(playAll);
        playAllBtn->setObjectName("playAllBtn");
        playAllBtn->setMinimumSize(QSize(100, 30));
        playAllBtn->setMaximumSize(QSize(100, 30));
        playAllBtn->setStyleSheet(QString::fromUtf8("#playAllBtn\n"
"{\n"
"	background-color:#E3E3E3;\n"
"	border-radius:10px;\n"
"}\n"
"\n"
"#playAllBtn:hover\n"
"{\n"
"	background-color:#1ECD97;\n"
"}"));

        verticalLayout_2->addWidget(playAllBtn);


        horizontalLayout->addWidget(playAll);

        horizontalSpacer = new QSpacerItem(488, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(musicPlayBox);

        listLabelBox = new QWidget(CommonPage);
        listLabelBox->setObjectName("listLabelBox");
        listLabelBox->setMinimumSize(QSize(0, 40));
        listLabelBox->setMaximumSize(QSize(16777215, 40));
        listLabelBox->setStyleSheet(QString::fromUtf8("#listLabelBox {\n"
"    background-color: #FAFAFA;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(listLabelBox);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, -1, 0);
        musicNameLabel = new QLabel(listLabelBox);
        musicNameLabel->setObjectName("musicNameLabel");
        musicNameLabel->setMinimumSize(QSize(380, 0));
        musicNameLabel->setMaximumSize(QSize(380, 16777215));

        horizontalLayout_2->addWidget(musicNameLabel);

        musicSingerLabel = new QLabel(listLabelBox);
        musicSingerLabel->setObjectName("musicSingerLabel");

        horizontalLayout_2->addWidget(musicSingerLabel);

        musicAlbumLabel = new QLabel(listLabelBox);
        musicAlbumLabel->setObjectName("musicAlbumLabel");

        horizontalLayout_2->addWidget(musicAlbumLabel);


        verticalLayout->addWidget(listLabelBox);

        pageMusicList = new QListWidget(CommonPage);
        pageMusicList->setObjectName("pageMusicList");
        pageMusicList->setMinimumSize(QSize(0, 40));
        pageMusicList->setStyleSheet(QString::fromUtf8("#pageMusicList {\n"
"    background-color: #FFFFFF;\n"
"    color: #202020;\n"
"    border: 1px solid #B9B9B9;\n"
"    outline: none;\n"
"}\n"
"\n"
"#pageMusicList::item:selected\n"
"{\n"
"	background-color:#EFFAF6;\n"
"}\n"
"\n"
"QScrollBar:vertical\n"
"{\n"
"	border:none;\n"
"	background-color:#FFFFFF;\n"
"	width:10px;\n"
"	margin:0px 0px 0px 0px;\n"
"	\n"
"}\n"
"\n"
"QScrollBar::handle:vertical\n"
"{\n"
"	border-radius:5px;\n"
"	background-color:#E3E3E3;\n"
"	width:10px;\n"
"	min-height:20px;\n"
"	\n"
"}"));

        verticalLayout->addWidget(pageMusicList);


        retranslateUi(CommonPage);

        QMetaObject::connectSlotsByName(CommonPage);
    } // setupUi

    void retranslateUi(QWidget *CommonPage)
    {
        CommonPage->setWindowTitle(QCoreApplication::translate("CommonPage", "Form", nullptr));
        PageTittle->setText(QCoreApplication::translate("CommonPage", "\346\234\254\345\234\260\351\237\263\344\271\220", nullptr));
        musicImageLabel->setText(QCoreApplication::translate("CommonPage", "\345\233\276\347\211\207", nullptr));
        playAllBtn->setText(QCoreApplication::translate("CommonPage", "\345\205\250\351\203\250\346\222\255\346\224\276", nullptr));
        musicNameLabel->setText(QCoreApplication::translate("CommonPage", "\346\255\214\346\233\262\345\220\215\347\247\260", nullptr));
        musicSingerLabel->setText(QCoreApplication::translate("CommonPage", "\346\255\214\346\211\213\345\220\215\347\247\260", nullptr));
        musicAlbumLabel->setText(QCoreApplication::translate("CommonPage", "\344\270\223\350\276\221\345\220\215\347\247\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CommonPage: public Ui_CommonPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMONPAGE_H
