/********************************************************************************
** Form generated from reading UI file 'recbox.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECBOX_H
#define UI_RECBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RecBox
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *LeftPage;
    QVBoxLayout *verticalLayout;
    QPushButton *btUp;
    QWidget *musicContent;
    QVBoxLayout *verticalLayout_3;
    QWidget *recListUp;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *recListUpHlayout;
    QWidget *recListDown;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *recListDownLayout;
    QWidget *rightPage;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btDown;

    void setupUi(QWidget *RecBox)
    {
        if (RecBox->objectName().isEmpty())
            RecBox->setObjectName("RecBox");
        RecBox->setStyleSheet(QString::fromUtf8("#RecBox {\n"
"    background-color: #FAFAFA;\n"
"}"));
        RecBox->resize(695, 400);
        RecBox->setMinimumSize(QSize(685, 400));
        RecBox->setMaximumSize(QSize(695, 400));
        horizontalLayout = new QHBoxLayout(RecBox);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        LeftPage = new QWidget(RecBox);
        LeftPage->setObjectName("LeftPage");
        LeftPage->setMinimumSize(QSize(30, 0));
        LeftPage->setMaximumSize(QSize(30, 16777215));
        LeftPage->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(LeftPage);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btUp = new QPushButton(LeftPage);
        btUp->setObjectName("btUp");
        btUp->setMinimumSize(QSize(0, 220));
        btUp->setMaximumSize(QSize(16777215, 220));
        btUp->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
" background-repeat:no-repeat;\n"
" border:none;\n"
" background-image : url(:/images/up_page.png);\n"
" background-position:center center;\n"
"}\n"
"QPushButton:hover\n"
"{background-color: #1ECD97;\n"
"}"));

        verticalLayout->addWidget(btUp);


        horizontalLayout->addWidget(LeftPage);

        musicContent = new QWidget(RecBox);
        musicContent->setObjectName("musicContent");
        musicContent->setEnabled(true);
        musicContent->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(musicContent);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        recListUp = new QWidget(musicContent);
        recListUp->setObjectName("recListUp");
        recListUp->setEnabled(true);
        recListUp->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_4 = new QHBoxLayout(recListUp);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        recListUpHlayout = new QHBoxLayout();
        recListUpHlayout->setSpacing(0);
        recListUpHlayout->setObjectName("recListUpHlayout");

        horizontalLayout_4->addLayout(recListUpHlayout);


        verticalLayout_3->addWidget(recListUp);

        recListDown = new QWidget(musicContent);
        recListDown->setObjectName("recListDown");
        recListDown->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_5 = new QHBoxLayout(recListDown);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        recListDownLayout = new QHBoxLayout();
        recListDownLayout->setSpacing(0);
        recListDownLayout->setObjectName("recListDownLayout");

        horizontalLayout_5->addLayout(recListDownLayout);


        verticalLayout_3->addWidget(recListDown);


        horizontalLayout->addWidget(musicContent);

        rightPage = new QWidget(RecBox);
        rightPage->setObjectName("rightPage");
        rightPage->setMinimumSize(QSize(30, 0));
        rightPage->setMaximumSize(QSize(30, 16777215));
        rightPage->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(rightPage);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        btDown = new QPushButton(rightPage);
        btDown->setObjectName("btDown");
        btDown->setMinimumSize(QSize(0, 220));
        btDown->setMaximumSize(QSize(16777215, 220));
        btDown->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
" background-repeat:no-repeat;\n"
" border:none;\n"
" background-image : url(:/images/down_page.png);\n"
" background-position:center center;\n"
"}\n"
"QPushButton:hover\n"
"{\n"
" background-color: #1ECD97;\n"
"}"));

        verticalLayout_2->addWidget(btDown);


        horizontalLayout->addWidget(rightPage);


        retranslateUi(RecBox);

        QMetaObject::connectSlotsByName(RecBox);
    } // setupUi

    void retranslateUi(QWidget *RecBox)
    {
        RecBox->setWindowTitle(QCoreApplication::translate("RecBox", "Form", nullptr));
        btUp->setText(QString());
        btDown->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RecBox: public Ui_RecBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECBOX_H
