/**
 *@file setting.cpp
 *@brief Implementation of settings dialog for frequency range configuration
 *
 *This file contains the implementation of the settings dialog for configuring frequency ranges
 *for LS (Left Speaker) and RS (Right Speaker). It includes methods for initializing the dialog,
 *retrieving values from the database, handling user input, and validating frequency range changes.
 *The dialog allows users to set minimum and maximum frequency values for both LS and RS, and the
 *changes are saved after validation.
 *
 *@note This file should be included along with the setting class implementation to ensure
 *proper functioning of the frequency range configuration in the data visualization application.
 *
 *@author[Dogan Can Oz]
 *@date[8/14/23]
 */
#include "setting.h"
#include "ui_setting.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

setting::setting(QWidget *parent):
    QDialog(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);

    // Connecting Send Button
    connect(ui->btn_send, &QPushButton::clicked, this, &setting::on_btn_send_clicked);

    // Setting LineEdits
    QSqlQuery query;
    bool success = query.exec("SELECT min_freq_ls, max_freq_ls, min_freq_rs, max_freq_rs FROM frequency_range");
    if (success && query.next())
    {
        double minFreqLS = query.value("min_freq_ls").toDouble();
        double maxFreqLS = query.value("max_freq_ls").toDouble();
        double minFreqRS = query.value("min_freq_rs").toDouble();
        double maxFreqRS = query.value("max_freq_rs").toDouble();

        // Set the retrieved values in the line edits
        ui->ledit_maxLs->setText(QString::number(maxFreqLS / 1000));
        ui->ledit_minLs->setText(QString::number(minFreqLS / 1000));
        ui->ledit_maxRs->setText(QString::number(maxFreqRS / 1000));
        ui->ledit_minRs->setText(QString::number(minFreqRS / 1000));
    }
}

setting::~setting()
{
    delete ui;
}

void setting::on_btn_send_clicked()
{
    // Get the values from LineEdits
    double newMinFrequencyLS = ui->ledit_minLs->text().toDouble();
    double newMaxFrequencyLS = ui->ledit_maxLs->text().toDouble();
    double newMinFrequencyRS = ui->ledit_minRs->text().toDouble();
    double newMaxFrequencyRS = ui->ledit_maxRs->text().toDouble();

    // Validate the values
    if (newMaxFrequencyLS <= newMinFrequencyLS || newMaxFrequencyRS <= newMinFrequencyRS)
    {
        // Show an error message indicating that the maximum value is smaller than or equal to the minimum value
        QMessageBox::critical(this, "Error", "Maximum frequency cannot be smaller than or equal to the minimum frequency.");
        return;
    }

    // If all validations pass, update the values
    minFrequencyLS = newMinFrequencyLS;
    maxFrequencyLS = newMaxFrequencyLS;
    minFrequencyRS = newMinFrequencyRS;
    maxFrequencyRS = newMaxFrequencyRS;

    accept();
}

double setting::getMinFrequencyLS() const
{
    return minFrequencyLS;
}

double setting::getMaxFrequencyLS() const
{
    return maxFrequencyLS;
}

double setting::getMinFrequencyRS() const
{
    return minFrequencyRS;
}

double setting::getMaxFrequencyRS() const
{
    return maxFrequencyRS;
}
