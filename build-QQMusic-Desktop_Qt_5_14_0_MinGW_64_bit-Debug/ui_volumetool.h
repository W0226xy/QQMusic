/********************************************************************************
** Form generated from reading UI file 'volumetool.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOLUMETOOL_H
#define UI_VOLUMETOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VolumeTool
{
public:
    QWidget *volumeWidget;
    QPushButton *silenceBtn;
    QLabel *volumeRatio;
    QWidget *volumeBox;
    QFrame *inLine;
    QFrame *outLine;
    QPushButton *silderBtn;

    void setupUi(QWidget *VolumeTool)
    {
        if (VolumeTool->objectName().isEmpty())
            VolumeTool->setObjectName(QString::fromUtf8("VolumeTool"));
        VolumeTool->resize(100, 350);
        volumeWidget = new QWidget(VolumeTool);
        volumeWidget->setObjectName(QString::fromUtf8("volumeWidget"));
        volumeWidget->setGeometry(QRect(10, 10, 80, 300));
        volumeWidget->setStyleSheet(QString::fromUtf8("#volumeWidget{\n"
" background-color:#F5F5F5;\n"
"border-radius:5px;\n"
"}"));
        silenceBtn = new QPushButton(volumeWidget);
        silenceBtn->setObjectName(QString::fromUtf8("silenceBtn"));
        silenceBtn->setGeometry(QRect(0, 255, 80, 45));
        silenceBtn->setMinimumSize(QSize(80, 45));
        silenceBtn->setMaximumSize(QSize(80, 45));
        silenceBtn->setStyleSheet(QString::fromUtf8("#silenceBtn\n"
"{\n"
"	border:none;\n"
"}\n"
"#silenceBtn:hover\n"
"{\n"
"	background-color:#F0F0F0;\n"
"}"));
        volumeRatio = new QLabel(volumeWidget);
        volumeRatio->setObjectName(QString::fromUtf8("volumeRatio"));
        volumeRatio->setGeometry(QRect(0, 225, 80, 30));
        volumeRatio->setMinimumSize(QSize(0, 30));
        volumeRatio->setMaximumSize(QSize(16777215, 30));
        volumeRatio->setStyleSheet(QString::fromUtf8(""));
        volumeRatio->setAlignment(Qt::AlignCenter);
        volumeBox = new QWidget(volumeWidget);
        volumeBox->setObjectName(QString::fromUtf8("volumeBox"));
        volumeBox->setGeometry(QRect(0, 0, 80, 225));
        volumeBox->setStyleSheet(QString::fromUtf8(""));
        inLine = new QFrame(volumeBox);
        inLine->setObjectName(QString::fromUtf8("inLine"));
        inLine->setGeometry(QRect(38, 25, 4, 180));
        inLine->setStyleSheet(QString::fromUtf8("#inline\n"
"{\n"
"	background-color:#ECECEC\n"
"}"));
        inLine->setFrameShape(QFrame::StyledPanel);
        inLine->setFrameShadow(QFrame::Raised);
        outLine = new QFrame(volumeBox);
        outLine->setObjectName(QString::fromUtf8("outLine"));
        outLine->setGeometry(QRect(38, 25, 4, 180));
        outLine->setStyleSheet(QString::fromUtf8("#outLine\n"
"{\n"
"	background-color:#1ECC94;\n"
"}"));
        outLine->setFrameShape(QFrame::StyledPanel);
        outLine->setFrameShadow(QFrame::Raised);
        silderBtn = new QPushButton(volumeBox);
        silderBtn->setObjectName(QString::fromUtf8("silderBtn"));
        silderBtn->setGeometry(QRect(33, 18, 14, 14));
        silderBtn->setMinimumSize(QSize(14, 0));
        silderBtn->setStyleSheet(QString::fromUtf8("#silderBtn\n"
"{\n"
"	border-radius:7px;\n"
"	background-color:#1ECC94;\n"
"}"));

        retranslateUi(VolumeTool);

        QMetaObject::connectSlotsByName(VolumeTool);
    } // setupUi

    void retranslateUi(QWidget *VolumeTool)
    {
        VolumeTool->setWindowTitle(QCoreApplication::translate("VolumeTool", "Form", nullptr));
        silenceBtn->setText(QString());
        volumeRatio->setText(QString());
        silderBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VolumeTool: public Ui_VolumeTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOLUMETOOL_H
