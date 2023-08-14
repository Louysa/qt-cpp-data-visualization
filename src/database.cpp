/**
 *@file database.cpp
 *@brief Implementation of database-related functionalities for CSV data visualization
 *
 *This file contains the implementation of functions related to database initialization,
 *opening, closing, table creation, and value retrieval. It includes methods to interact
 *with the database, create a frequency range table, check and set initial values, and
 *open and close the database connection. It also handles potential errors during database
 *interactions and provides status messages to the user interface.
 *
 *The database functions are crucial for managing persistent data storage, storing user-defined
 *frequency range values, and ensuring proper initialization and access to the database for the
 *application's functionality.
 *
 *@note This file should be included along with the MainWindow class implementation to ensure
 *proper functioning of the CSV data visualization application.
 *
 *@author[Dogan Can Oz]
 *@date[8/14/23]
 */
#include "mainwindow.h"
#include "setting.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QDateTime>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

// Settings Icon
void MainWindow::on_actionsettings_triggered()
{
    // Show the settings dialog
    setting rangeDialog(this);
    if (rangeDialog.exec() != QDialog::Accepted)
    {
        return;	// Dialog was canceled, exit the function
    }

    // Get the frequency range values from the dialog
    double minFreqLS = rangeDialog.getMinFrequencyLS() *1000.0;
    double maxFreqLS = rangeDialog.getMaxFrequencyLS() *1000.0;
    double minFreqRS = rangeDialog.getMinFrequencyRS() *1000.0;
    double maxFreqRS = rangeDialog.getMaxFrequencyRS() *1000.0;

    // Update the values in the database
    QSqlQuery query;
    bool success = query.exec(QString("UPDATE frequency_range SET min_freq_ls = %1, max_freq_ls = %2, "
                                      "min_freq_rs = %3, max_freq_rs = %4").arg(minFreqLS).arg(maxFreqLS).arg(minFreqRS).arg(maxFreqRS));
    qDebug() << "Updated Correctly" << minFreqLS << " " << maxFreqLS << " " << minFreqRS << " " << maxFreqRS;
    if (!success)
    {
        qDebug() << "Error updating values in the table!";
        // Handle the error as needed
        return;
    }
}

// InitializeDatabase and Connect/Open
void MainWindow::initializeDatabase()
{
    // Define the path to the database file
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/whilone";

    // Initialize the database connection
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath + "/whl.db");

    qDebug() << dbPath;
    QDir dir(dbPath);
    if (!dir.exists())
    {
        if (dir.mkpath("."))
        {
            qDebug() << "Directory created successfully!";
        }
        else
        {
            qDebug() << "Failed to create directory!";
        }
    }

    openDatabase();

    createFrequencyRangeTable();

    // Check and set initial values if needed
    if (!checkAndSetInitialValues())
    {
        qDebug() << "Error checking and setting initial values!";
        // Handle the error as needed
    }
}

// Create Frequency Range Table
void MainWindow::createFrequencyRangeTable()
{
    QSqlQuery query;

    // Execute SQL statement to create the table
    bool success = query.exec("CREATE TABLE IF NOT EXISTS frequency_range ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "min_freq_ls REAL,"
                              "max_freq_ls REAL,"
                              "min_freq_rs REAL,"
                              "max_freq_rs REAL)");
    if (!success)
    {
        qDebug() << "Error creating table!";
        // Handle the error as needed
    }
}

// Check and Update Value
bool MainWindow::checkAndSetInitialValues()
{
    QSqlQuery query;

    // Execute SQL statement to fetch values from the table
    bool success = query.exec("SELECT *FROM frequency_range");
    if (!success)
    {
        qDebug() << "Error fetching values from the table!";
        // Handle the error as needed
        return false;
    }

    // If there are no rows in the table, prompt the user to set values
    if (!query.next())
    {
        // Show a dialog to set frequency range values
        setting initialSettingDialog(this);
        if (initialSettingDialog.exec() != QDialog::Accepted)
        {
            return false;	// Dialog was canceled, exit the function
        }

        // Get the frequency range values from the dialog
        double minFreqLS = initialSettingDialog.getMinFrequencyLS() *1000.0;
        double maxFreqLS = initialSettingDialog.getMaxFrequencyLS() *1000.0;
        double minFreqRS = initialSettingDialog.getMinFrequencyRS() *1000.0;
        double maxFreqRS = initialSettingDialog.getMaxFrequencyRS() *1000.0;

        // Execute SQL statement to insert values into the table
        success = query.exec(QString("INSERT INTO frequency_range (min_freq_ls, max_freq_ls, min_freq_rs, max_freq_rs) "
                                     "VALUES (%1, %2, %3, %4)").arg(minFreqLS).arg(maxFreqLS).arg(minFreqRS).arg(maxFreqRS));
        qDebug() << "Success";
        if (!success)
        {
            qDebug() << "Error inserting values into the table!";
            // Handle the error as needed
            return false;
        }

        // Store the values in member variables
        minFrequencyLS = minFreqLS;
        maxFrequencyLS = maxFreqLS;
        minFrequencyRS = minFreqRS;
        maxFrequencyRS = maxFreqRS;
        // Return true to indicate successful initialization
        return true;
    }

    // If values are already set, retrieve and store them
    minFrequencyLS = query.value("min_freq_ls").toDouble();
    qDebug() << minFrequencyLS;
    maxFrequencyLS = query.value("max_freq_ls").toDouble();
    qDebug() << maxFrequencyLS;
    minFrequencyRS = query.value("min_freq_rs").toDouble();
    qDebug() << minFrequencyRS;
    maxFrequencyRS = query.value("max_freq_rs").toDouble();
    qDebug() << maxFrequencyRS;

    // Return true to indicate that values are already set in the database
    return true;
}

// Open Database
bool MainWindow::openDatabase()
{
    db.open();

    if (!db.open())
    {
        qDebug() << "Database not open";
        ui->statusbar->showMessage("Database could not open. Please be sure that Database is in correct location.Try to download program again.");
        ui->centralwidget->setEnabled(false);

        return false;
    }

    qDebug() << "Database opened";
    ui->statusbar->showMessage("Database opened succesfully.");

    return true;
}

// Close Database
bool MainWindow::closeDatabase()
{
    db.close();

    return true;
}
