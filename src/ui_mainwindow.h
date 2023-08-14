/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionsettings;
    QWidget *centralwidget;
    QGridLayout *gridLayout_6;
    QCustomPlot *Plot;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_3;
    QPushButton *btn_zoomout_y;
    QPushButton *btn_zoom_x;
    QPushButton *btn_zoom_y;
    QPushButton *btn_zoomout_x;
    QGridLayout *gridLayout_7;
    QRadioButton *radioButton_Ls;
    QRadioButton *radioButton_Rs;
    QLabel *label_4;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label_freq;
    QLabel *label_value;
    QLineEdit *lineEdit_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *cbox_Tracer;
    QComboBox *comboBox_tracer;
    QCheckBox *cbox_legend;
    QPushButton *btn_tablo;
    QPushButton *btn_tablo_clear;
    QGridLayout *gridLayout_4;
    QLineEdit *ledit_minValue;
    QCheckBox *cbox_Lines;
    QPushButton *btn_clearLine;
    QLineEdit *ledit_maxValue;
    QPushButton *btn_addValue;
    QComboBox *combobox_line_color;
    QVBoxLayout *verticalLayout;
    QCheckBox *cbox_r_zoom;
    QPushButton *btn_avg;
    QPushButton *btn_export_avg;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *doubleSpinBox;
    QPushButton *btn_HighlightGraphs;
    QGridLayout *gridLayout_2;
    QPushButton *btn_load_plot;
    QPushButton *btn_clear_plot;
    QPushButton *btn_start_plot;
    QPushButton *btn_save_plot;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QMenuBar *menuBar;
    QMenu *menuSettings;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1548, 832);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(241, 246, 249, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(248, 250, 252, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(120, 123, 124, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(161, 164, 166, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush3);
        QBrush brush6(QColor(255, 255, 220, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        QBrush brush7(QColor(0, 0, 0, 127));
        brush7.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush7);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush7);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        QBrush brush8(QColor(120, 123, 124, 127));
        brush8.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush8);
#endif
        MainWindow->setPalette(palette);
        actionsettings = new QAction(MainWindow);
        actionsettings->setObjectName("actionsettings");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/general/icons/resource/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionsettings->setIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);"));
        gridLayout_6 = new QGridLayout(centralwidget);
        gridLayout_6->setObjectName("gridLayout_6");
        Plot = new QCustomPlot(centralwidget);
        Plot->setObjectName("Plot");
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush9(QColor(155, 164, 181, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush9);
        QBrush brush10(QColor(235, 242, 255, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush10);
        QBrush brush11(QColor(195, 203, 218, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush11);
        QBrush brush12(QColor(77, 82, 90, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush12);
        QBrush brush13(QColor(103, 109, 121, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush13);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush9);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush9);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush14(QColor(205, 209, 218, 255));
        brush14.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush14);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush6);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush7);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush11);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush12);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush13);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush14);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush7);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush11);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush13);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        QBrush brush15(QColor(77, 82, 90, 127));
        brush15.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush15);
#endif
        Plot->setPalette(palette1);
        Plot->setStyleSheet(QString::fromUtf8("background-color: rgb(155, 164, 181);"));

        gridLayout_6->addWidget(Plot, 0, 0, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setHorizontalSpacing(15);
        gridLayout_5->setVerticalSpacing(1);
        gridLayout_5->setContentsMargins(-1, -1, -1, 0);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        btn_zoomout_y = new QPushButton(centralwidget);
        btn_zoomout_y->setObjectName("btn_zoomout_y");
        btn_zoomout_y->setFocusPolicy(Qt::TabFocus);

        gridLayout_3->addWidget(btn_zoomout_y, 3, 1, 1, 1);

        btn_zoom_x = new QPushButton(centralwidget);
        btn_zoom_x->setObjectName("btn_zoom_x");
        btn_zoom_x->setFocusPolicy(Qt::TabFocus);

        gridLayout_3->addWidget(btn_zoom_x, 1, 0, 1, 1);

        btn_zoom_y = new QPushButton(centralwidget);
        btn_zoom_y->setObjectName("btn_zoom_y");
        btn_zoom_y->setFocusPolicy(Qt::TabFocus);

        gridLayout_3->addWidget(btn_zoom_y, 1, 1, 1, 1);

        btn_zoomout_x = new QPushButton(centralwidget);
        btn_zoomout_x->setObjectName("btn_zoomout_x");
        btn_zoomout_x->setFocusPolicy(Qt::TabFocus);

        gridLayout_3->addWidget(btn_zoomout_x, 3, 0, 1, 1);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName("gridLayout_7");
        radioButton_Ls = new QRadioButton(centralwidget);
        radioButton_Ls->setObjectName("radioButton_Ls");
        QFont font;
        font.setFamilies({QString::fromUtf8("Sylfaen")});
        font.setPointSize(12);
        font.setBold(false);
        radioButton_Ls->setFont(font);
        radioButton_Ls->setStyleSheet(QString::fromUtf8(""));
        radioButton_Ls->setChecked(true);

        gridLayout_7->addWidget(radioButton_Ls, 2, 0, 1, 1);

        radioButton_Rs = new QRadioButton(centralwidget);
        radioButton_Rs->setObjectName("radioButton_Rs");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Sylfaen")});
        font1.setPointSize(12);
        radioButton_Rs->setFont(font1);
        radioButton_Rs->setStyleSheet(QString::fromUtf8(""));

        gridLayout_7->addWidget(radioButton_Rs, 2, 1, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial Rounded MT Bold")});
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setItalic(false);
        label_4->setFont(font2);
        label_4->setStyleSheet(QString::fromUtf8(""));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_4, 1, 0, 1, 2);


        gridLayout_3->addLayout(gridLayout_7, 0, 0, 1, 2);


        gridLayout_5->addLayout(gridLayout_3, 0, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(7);
        gridLayout->setObjectName("gridLayout");
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setEnabled(false);
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setItalic(true);
        lineEdit->setFont(font3);
        lineEdit->setFocusPolicy(Qt::NoFocus);
        lineEdit->setStyleSheet(QString::fromUtf8(""));
        lineEdit->setAlignment(Qt::AlignCenter);
        lineEdit->setReadOnly(true);

        gridLayout->addWidget(lineEdit, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setEnabled(false);
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        lineEdit_2->setFont(font4);
        lineEdit_2->setFocusPolicy(Qt::NoFocus);
        lineEdit_2->setStyleSheet(QString::fromUtf8(""));
        lineEdit_2->setAlignment(Qt::AlignCenter);
        lineEdit_2->setReadOnly(true);

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        label_freq = new QLabel(centralwidget);
        label_freq->setObjectName("label_freq");
        label_freq->setFont(font2);
        label_freq->setStyleSheet(QString::fromUtf8(""));
        label_freq->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_freq, 0, 0, 1, 1);

        label_value = new QLabel(centralwidget);
        label_value->setObjectName("label_value");
        label_value->setFont(font2);
        label_value->setStyleSheet(QString::fromUtf8(""));
        label_value->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_value, 0, 1, 1, 1);

        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setEnabled(false);
        lineEdit_3->setFont(font4);
        lineEdit_3->setFocusPolicy(Qt::NoFocus);
        lineEdit_3->setStyleSheet(QString::fromUtf8(""));
        lineEdit_3->setAlignment(Qt::AlignCenter);
        lineEdit_3->setReadOnly(true);

        gridLayout->addWidget(lineEdit_3, 2, 0, 1, 2);


        gridLayout_5->addLayout(gridLayout, 0, 2, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(10);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(-1, 10, -1, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        cbox_Tracer = new QCheckBox(centralwidget);
        cbox_Tracer->setObjectName("cbox_Tracer");
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Calibri")});
        font5.setPointSize(12);
        cbox_Tracer->setFont(font5);
        cbox_Tracer->setFocusPolicy(Qt::TabFocus);
        cbox_Tracer->setStyleSheet(QString::fromUtf8(""));
        cbox_Tracer->setChecked(true);

        horizontalLayout_2->addWidget(cbox_Tracer);

        comboBox_tracer = new QComboBox(centralwidget);
        comboBox_tracer->addItem(QString());
        comboBox_tracer->addItem(QString());
        comboBox_tracer->addItem(QString());
        comboBox_tracer->addItem(QString());
        comboBox_tracer->addItem(QString());
        comboBox_tracer->setObjectName("comboBox_tracer");
        comboBox_tracer->setFocusPolicy(Qt::TabFocus);

        horizontalLayout_2->addWidget(comboBox_tracer);

        cbox_legend = new QCheckBox(centralwidget);
        cbox_legend->setObjectName("cbox_legend");
        cbox_legend->setFont(font5);
        cbox_legend->setFocusPolicy(Qt::TabFocus);
        cbox_legend->setStyleSheet(QString::fromUtf8(""));
        cbox_legend->setChecked(true);

        horizontalLayout_2->addWidget(cbox_legend);


        verticalLayout_3->addLayout(horizontalLayout_2);

        btn_tablo = new QPushButton(centralwidget);
        btn_tablo->setObjectName("btn_tablo");
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Calibri")});
        font6.setPointSize(11);
        btn_tablo->setFont(font6);
        btn_tablo->setFocusPolicy(Qt::TabFocus);
        btn_tablo->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_3->addWidget(btn_tablo);

        btn_tablo_clear = new QPushButton(centralwidget);
        btn_tablo_clear->setObjectName("btn_tablo_clear");
        btn_tablo_clear->setFont(font5);
        btn_tablo_clear->setFocusPolicy(Qt::TabFocus);
        btn_tablo_clear->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_3->addWidget(btn_tablo_clear);


        gridLayout_5->addLayout(verticalLayout_3, 0, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        ledit_minValue = new QLineEdit(centralwidget);
        ledit_minValue->setObjectName("ledit_minValue");
        ledit_minValue->setFocusPolicy(Qt::StrongFocus);

        gridLayout_4->addWidget(ledit_minValue, 1, 1, 1, 1);

        cbox_Lines = new QCheckBox(centralwidget);
        cbox_Lines->setObjectName("cbox_Lines");
        cbox_Lines->setFocusPolicy(Qt::TabFocus);

        gridLayout_4->addWidget(cbox_Lines, 0, 0, 1, 1);

        btn_clearLine = new QPushButton(centralwidget);
        btn_clearLine->setObjectName("btn_clearLine");
        btn_clearLine->setFocusPolicy(Qt::TabFocus);

        gridLayout_4->addWidget(btn_clearLine, 2, 1, 1, 1);

        ledit_maxValue = new QLineEdit(centralwidget);
        ledit_maxValue->setObjectName("ledit_maxValue");
        ledit_maxValue->setFocusPolicy(Qt::StrongFocus);

        gridLayout_4->addWidget(ledit_maxValue, 1, 0, 1, 1);

        btn_addValue = new QPushButton(centralwidget);
        btn_addValue->setObjectName("btn_addValue");
        btn_addValue->setFocusPolicy(Qt::TabFocus);

        gridLayout_4->addWidget(btn_addValue, 2, 0, 1, 1);

        combobox_line_color = new QComboBox(centralwidget);
        combobox_line_color->addItem(QString());
        combobox_line_color->addItem(QString());
        combobox_line_color->addItem(QString());
        combobox_line_color->addItem(QString());
        combobox_line_color->addItem(QString());
        combobox_line_color->setObjectName("combobox_line_color");
        combobox_line_color->setFocusPolicy(Qt::TabFocus);

        gridLayout_4->addWidget(combobox_line_color, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 0, 4, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        cbox_r_zoom = new QCheckBox(centralwidget);
        cbox_r_zoom->setObjectName("cbox_r_zoom");
        cbox_r_zoom->setFont(font5);
        cbox_r_zoom->setStyleSheet(QString::fromUtf8(""));
        cbox_r_zoom->setChecked(false);

        verticalLayout->addWidget(cbox_r_zoom);

        btn_avg = new QPushButton(centralwidget);
        btn_avg->setObjectName("btn_avg");
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Calibri")});
        font7.setPointSize(12);
        font7.setItalic(true);
        btn_avg->setFont(font7);
        btn_avg->setFocusPolicy(Qt::TabFocus);
        btn_avg->setAutoFillBackground(false);
        btn_avg->setStyleSheet(QString::fromUtf8(""));
        btn_avg->setAutoDefault(false);
        btn_avg->setFlat(false);

        verticalLayout->addWidget(btn_avg);

        btn_export_avg = new QPushButton(centralwidget);
        btn_export_avg->setObjectName("btn_export_avg");
        btn_export_avg->setFont(font5);
        btn_export_avg->setFocusPolicy(Qt::TabFocus);
        btn_export_avg->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(btn_export_avg);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        doubleSpinBox = new QDoubleSpinBox(centralwidget);
        doubleSpinBox->setObjectName("doubleSpinBox");
        doubleSpinBox->setFocusPolicy(Qt::TabFocus);
        doubleSpinBox->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(doubleSpinBox);

        btn_HighlightGraphs = new QPushButton(centralwidget);
        btn_HighlightGraphs->setObjectName("btn_HighlightGraphs");
        btn_HighlightGraphs->setFont(font5);
        btn_HighlightGraphs->setFocusPolicy(Qt::TabFocus);
        btn_HighlightGraphs->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(btn_HighlightGraphs);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_5->addLayout(verticalLayout, 0, 3, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(-1, 5, -1, -1);
        btn_load_plot = new QPushButton(centralwidget);
        btn_load_plot->setObjectName("btn_load_plot");
        btn_load_plot->setFont(font7);
        btn_load_plot->setFocusPolicy(Qt::TabFocus);
        btn_load_plot->setAutoFillBackground(false);
        btn_load_plot->setStyleSheet(QString::fromUtf8(""));
        btn_load_plot->setAutoDefault(false);
        btn_load_plot->setFlat(false);

        gridLayout_2->addWidget(btn_load_plot, 0, 0, 1, 1);

        btn_clear_plot = new QPushButton(centralwidget);
        btn_clear_plot->setObjectName("btn_clear_plot");
        btn_clear_plot->setFont(font5);
        btn_clear_plot->setFocusPolicy(Qt::TabFocus);
        btn_clear_plot->setStyleSheet(QString::fromUtf8(""));
        btn_clear_plot->setCheckable(false);

        gridLayout_2->addWidget(btn_clear_plot, 0, 1, 1, 1);

        btn_start_plot = new QPushButton(centralwidget);
        btn_start_plot->setObjectName("btn_start_plot");
        btn_start_plot->setFont(font7);
        btn_start_plot->setFocusPolicy(Qt::TabFocus);
        btn_start_plot->setAutoFillBackground(false);
        btn_start_plot->setStyleSheet(QString::fromUtf8(""));
        btn_start_plot->setAutoDefault(false);
        btn_start_plot->setFlat(false);

        gridLayout_2->addWidget(btn_start_plot, 1, 0, 1, 1);

        btn_save_plot = new QPushButton(centralwidget);
        btn_save_plot->setObjectName("btn_save_plot");
        btn_save_plot->setFont(font5);
        btn_save_plot->setFocusPolicy(Qt::TabFocus);
        btn_save_plot->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(btn_save_plot, 1, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_2, 0, 5, 1, 2);

        gridLayout_5->setColumnStretch(1, 5);
        gridLayout_5->setColumnStretch(2, 7);
        gridLayout_5->setColumnStretch(3, 7);
        gridLayout_5->setColumnStretch(6, 8);

        gridLayout_6->addLayout(gridLayout_5, 1, 0, 1, 1);

        gridLayout_6->setRowStretch(0, 9);
        gridLayout_6->setRowStretch(1, 2);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setLayoutDirection(Qt::LeftToRight);
        statusbar->setAutoFillBackground(false);
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1548, 21));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName("menuSettings");
        MainWindow->setMenuBar(menuBar);
        QWidget::setTabOrder(cbox_Tracer, comboBox_tracer);
        QWidget::setTabOrder(comboBox_tracer, btn_tablo);
        QWidget::setTabOrder(btn_tablo, btn_tablo_clear);
        QWidget::setTabOrder(btn_tablo_clear, cbox_legend);
        QWidget::setTabOrder(cbox_legend, radioButton_Ls);
        QWidget::setTabOrder(radioButton_Ls, lineEdit);
        QWidget::setTabOrder(lineEdit, lineEdit_2);
        QWidget::setTabOrder(lineEdit_2, cbox_r_zoom);
        QWidget::setTabOrder(cbox_r_zoom, btn_avg);
        QWidget::setTabOrder(btn_avg, btn_export_avg);
        QWidget::setTabOrder(btn_export_avg, doubleSpinBox);
        QWidget::setTabOrder(doubleSpinBox, btn_HighlightGraphs);
        QWidget::setTabOrder(btn_HighlightGraphs, btn_load_plot);
        QWidget::setTabOrder(btn_load_plot, btn_clear_plot);
        QWidget::setTabOrder(btn_clear_plot, btn_start_plot);
        QWidget::setTabOrder(btn_start_plot, btn_save_plot);
        QWidget::setTabOrder(btn_save_plot, cbox_Lines);
        QWidget::setTabOrder(cbox_Lines, combobox_line_color);
        QWidget::setTabOrder(combobox_line_color, ledit_maxValue);
        QWidget::setTabOrder(ledit_maxValue, ledit_minValue);
        QWidget::setTabOrder(ledit_minValue, btn_addValue);
        QWidget::setTabOrder(btn_addValue, btn_clearLine);
        QWidget::setTabOrder(btn_clearLine, btn_zoom_x);
        QWidget::setTabOrder(btn_zoom_x, btn_zoom_y);
        QWidget::setTabOrder(btn_zoom_y, btn_zoomout_x);
        QWidget::setTabOrder(btn_zoomout_x, btn_zoomout_y);

        toolBar->addAction(actionsettings);
        menuBar->addAction(menuSettings->menuAction());

        retranslateUi(MainWindow);

        combobox_line_color->setCurrentIndex(4);
        btn_avg->setDefault(false);
        btn_load_plot->setDefault(false);
        btn_start_plot->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionsettings->setText(QCoreApplication::translate("MainWindow", "settings", nullptr));
        btn_zoomout_y->setText(QCoreApplication::translate("MainWindow", "Zoom out Y", nullptr));
        btn_zoom_x->setText(QCoreApplication::translate("MainWindow", "Zoom X", nullptr));
        btn_zoom_y->setText(QCoreApplication::translate("MainWindow", "Zoom Y", nullptr));
        btn_zoomout_x->setText(QCoreApplication::translate("MainWindow", "Zoom out X", nullptr));
        radioButton_Ls->setText(QCoreApplication::translate("MainWindow", "Ls", nullptr));
        radioButton_Rs->setText(QCoreApplication::translate("MainWindow", "Rs", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Graph View", nullptr));
        label_freq->setText(QCoreApplication::translate("MainWindow", "Frequency", nullptr));
#if QT_CONFIG(whatsthis)
        label_value->setWhatsThis(QCoreApplication::translate("MainWindow", "ya allah", nullptr));
#endif // QT_CONFIG(whatsthis)
        label_value->setText(QCoreApplication::translate("MainWindow", "Value", nullptr));
        cbox_Tracer->setText(QCoreApplication::translate("MainWindow", "Tracer:", nullptr));
        comboBox_tracer->setItemText(0, QCoreApplication::translate("MainWindow", "Crosshair", nullptr));
        comboBox_tracer->setItemText(1, QCoreApplication::translate("MainWindow", "Circle", nullptr));
        comboBox_tracer->setItemText(2, QCoreApplication::translate("MainWindow", "Plus", nullptr));
        comboBox_tracer->setItemText(3, QCoreApplication::translate("MainWindow", "Square", nullptr));
        comboBox_tracer->setItemText(4, QCoreApplication::translate("MainWindow", "None", nullptr));

        cbox_legend->setText(QCoreApplication::translate("MainWindow", "Legends", nullptr));
        btn_tablo->setText(QCoreApplication::translate("MainWindow", "Compare Table", nullptr));
        btn_tablo_clear->setText(QCoreApplication::translate("MainWindow", "Clear Table", nullptr));
        cbox_Lines->setText(QCoreApplication::translate("MainWindow", "Lines:", nullptr));
        btn_clearLine->setText(QCoreApplication::translate("MainWindow", "Clear Lines", nullptr));
        btn_addValue->setText(QCoreApplication::translate("MainWindow", "Add Line", nullptr));
        combobox_line_color->setItemText(0, QCoreApplication::translate("MainWindow", "Red", nullptr));
        combobox_line_color->setItemText(1, QCoreApplication::translate("MainWindow", "Green", nullptr));
        combobox_line_color->setItemText(2, QCoreApplication::translate("MainWindow", "Yellow", nullptr));
        combobox_line_color->setItemText(3, QCoreApplication::translate("MainWindow", "Blue", nullptr));
        combobox_line_color->setItemText(4, QCoreApplication::translate("MainWindow", "Black", nullptr));

        cbox_r_zoom->setText(QCoreApplication::translate("MainWindow", "Rectangle Zoom", nullptr));
        btn_avg->setText(QCoreApplication::translate("MainWindow", "Calculate Average ", nullptr));
        btn_export_avg->setText(QCoreApplication::translate("MainWindow", "Export AVG To CSV", nullptr));
        btn_HighlightGraphs->setText(QCoreApplication::translate("MainWindow", "Highlight", nullptr));
        btn_load_plot->setText(QCoreApplication::translate("MainWindow", "Load CSV Files", nullptr));
        btn_clear_plot->setText(QCoreApplication::translate("MainWindow", "Clear Plot", nullptr));
        btn_start_plot->setText(QCoreApplication::translate("MainWindow", "Default", nullptr));
        btn_save_plot->setText(QCoreApplication::translate("MainWindow", "Export Graph as PNG", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
