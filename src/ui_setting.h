/********************************************************************************
** Form generated from reading UI file 'setting.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_setting
{
public:
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *ledit_minLs;
    QLineEdit *ledit_maxLs;
    QLabel *label_8;
    QLabel *label_ls;
    QGridLayout *gridLayout;
    QLineEdit *ledit_minRs;
    QLineEdit *ledit_maxRs;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_maxRs;
    QPushButton *btn_send;

    void setupUi(QDialog *setting)
    {
        if (setting->objectName().isEmpty())
            setting->setObjectName("setting");
        setting->resize(271, 379);
        gridLayout_3 = new QGridLayout(setting);
        gridLayout_3->setObjectName("gridLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        label_5 = new QLabel(setting);
        label_5->setObjectName("label_5");

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        label_6 = new QLabel(setting);
        label_6->setObjectName("label_6");

        gridLayout_2->addWidget(label_6, 3, 0, 1, 1);

        label_7 = new QLabel(setting);
        label_7->setObjectName("label_7");

        gridLayout_2->addWidget(label_7, 3, 2, 1, 1);

        ledit_minLs = new QLineEdit(setting);
        ledit_minLs->setObjectName("ledit_minLs");

        gridLayout_2->addWidget(ledit_minLs, 3, 1, 1, 1);

        ledit_maxLs = new QLineEdit(setting);
        ledit_maxLs->setObjectName("ledit_maxLs");

        gridLayout_2->addWidget(ledit_maxLs, 1, 1, 1, 1);

        label_8 = new QLabel(setting);
        label_8->setObjectName("label_8");

        gridLayout_2->addWidget(label_8, 1, 2, 1, 1);

        label_ls = new QLabel(setting);
        label_ls->setObjectName("label_ls");
        QFont font;
        font.setFamilies({QString::fromUtf8("Calibri")});
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(true);
        label_ls->setFont(font);
        label_ls->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_ls, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        ledit_minRs = new QLineEdit(setting);
        ledit_minRs->setObjectName("ledit_minRs");

        gridLayout->addWidget(ledit_minRs, 2, 1, 1, 1);

        ledit_maxRs = new QLineEdit(setting);
        ledit_maxRs->setObjectName("ledit_maxRs");

        gridLayout->addWidget(ledit_maxRs, 1, 1, 1, 1);

        label_2 = new QLabel(setting);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_4 = new QLabel(setting);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 2, 2, 1, 1);

        label_3 = new QLabel(setting);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 1, 2, 1, 1);

        label = new QLabel(setting);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_maxRs = new QLabel(setting);
        label_maxRs->setObjectName("label_maxRs");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Calibri")});
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setItalic(true);
        label_maxRs->setFont(font1);
        label_maxRs->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_maxRs, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        btn_send = new QPushButton(setting);
        btn_send->setObjectName("btn_send");

        verticalLayout->addWidget(btn_send);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);

        QWidget::setTabOrder(ledit_maxLs, ledit_minLs);
        QWidget::setTabOrder(ledit_minLs, ledit_maxRs);
        QWidget::setTabOrder(ledit_maxRs, ledit_minRs);
        QWidget::setTabOrder(ledit_minRs, btn_send);

        retranslateUi(setting);

        QMetaObject::connectSlotsByName(setting);
    } // setupUi

    void retranslateUi(QDialog *setting)
    {
        setting->setWindowTitle(QCoreApplication::translate("setting", "Dialog", nullptr));
        label_5->setText(QCoreApplication::translate("setting", "MAX", nullptr));
        label_6->setText(QCoreApplication::translate("setting", "MIN", nullptr));
        label_7->setText(QCoreApplication::translate("setting", "kHz", nullptr));
        label_8->setText(QCoreApplication::translate("setting", "kHz", nullptr));
        label_ls->setText(QCoreApplication::translate("setting", "LS", nullptr));
        label_2->setText(QCoreApplication::translate("setting", "MIN", nullptr));
        label_4->setText(QCoreApplication::translate("setting", "kHz", nullptr));
        label_3->setText(QCoreApplication::translate("setting", "kHz", nullptr));
        label->setText(QCoreApplication::translate("setting", "MAX", nullptr));
        label_maxRs->setText(QCoreApplication::translate("setting", "RS ", nullptr));
        btn_send->setText(QCoreApplication::translate("setting", "Send Max/Mins", nullptr));
    } // retranslateUi

};

namespace Ui {
    class setting: public Ui_setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
