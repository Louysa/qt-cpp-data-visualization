#include "mainwindow.h"

void MainWindow::settingGraph{

// X axis
ui->Plot->xAxis->setLabel("ZAMAN");
ui->Plot->xAxis->setLabelFont(QFont("Calibri", 16));
ui->Plot->xAxis->setLabelColor(QColor(Qt::black));
ui->Plot->xAxis->setTickLabelFont(QFont(QFont().family(),8));

// Y axis
ui->Plot->yAxis->setLabel("VERİ");
ui->Plot->yAxis->setLabelColor(QColor(Qt::black));
ui->Plot->yAxis->setLabelFont(QFont("Calibri", 16));
ui->Plot->yAxis->setTickLabelFont(QFont(QFont().family(),8));


// Plot
ui->Plot->setBackground (QColor (170, 170, 170, 255));
setFixedSize(1190,590);
};
