/**
 *@file mainwindow.cpp
 *@brief Implementation of the main application window
 *
 *This file contains the implementation of the main application window class, including its constructor,
 *destructor, and various slot functions. The main window sets up the user interface, handles user interactions,
 *and manages database connections.
 *
 *@author[Dogan Can Oz]
 *@date[8/14/23]
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QDateTime>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set initial size to full-screen
    this->setWindowState(Qt::WindowFullScreen);

    // Configure resizable window flags
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    // Setuping Plot
    setupPlot();

    // Double click
    connect(ui->Plot, &QCustomPlot::mouseDoubleClick, this, &MainWindow::onPlotDoubleClick);
    // Connect the custom contextMenuRequest to the customContextMenuRequested signal.
    connect(ui->Plot, &QCustomPlot::customContextMenuRequested, this, &MainWindow::contextMenuRequest);
    // Connect the checkbox signal to the slot
    connect(ui->cbox_legend, &QCheckBox::clicked, this, &MainWindow::on_cbox_legend_toggled);

    // Connect the selectionChanged signal to the updateGraphName slot
    connect(ui->Plot, &QCustomPlot::selectionChangedByUser, this, &MainWindow::updateGraphName);

    // Initialize the database connection
    initializeDatabase();
    avg = false;

    //Select Graph
    connect(ui->Plot, &QCustomPlot::selectionChangedByUser, this, &MainWindow::handleGraphSelection);

}

MainWindow::~MainWindow()
{
    closeDatabase();
    delete ui;
}

// Closing Event
void MainWindow::closeEvent(QCloseEvent *event)
{
    // Ask the user if they're sure they want to close
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Exit", "Are you sure you want to exit?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        closeDatabase();	// Close the database before exiting
        event->accept();	// Allow the program to exit
    }
    else
    {
        event->ignore();	// Ignore the close event and keep the program running
    }
}
