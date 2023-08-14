/**
 *@file csvFunctions.cpp
 *@brief Implementation of CSV file loading and exporting functionalities for data visualization
 *
 *This file contains the implementation of functions related to loading and exporting CSV files
 *for data visualization. It includes methods for loading CSV files, extracting data, creating
 *average graphs, and exporting average graph data as CSV files. These functions are crucial for
 *loading raw data, processing and visualizing it, and exporting processed data for further analysis.
 *
 *@note This file should be included along with the MainWindow class implementation to ensure
 *proper functioning of the CSV data visualization application.
 *
 *@author[Dogan Can Oz]
 *@date[8/14/23]
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

// Button -> Load CSV
void MainWindow::on_btn_load_plot_clicked()
{
    clearEverything();

    if (!checkAndSetInitialValues())
    {
        // Show a message asking the user to set values from the settings tab first
        QMessageBox::information(this, "Info", "Please set frequency range values in the settings tab.");
        return;
    }

    QStringList fileNames = QFileDialog::getOpenFileNames(this, "Select CSV Files", "", "CSV Files (*.csv)");
    qDebug() << "Dosya isimleri" << fileNames;
    for (const QString &fileName: fileNames)
    {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in (&file);

            // Skip the first row (header: "FREQUENCY,Ls,Rs")
            in .readLine();

            QVector<double> lsValues;
            QVector<double> rsValues;
            QVector<double> frequenciesRs;
            QVector<double> frequenciesLs;

            while (! in .atEnd())
            {
                QString line = in .readLine();
                QStringList data = line.split(",");

                if (data.size() >= 3)
                {
                    // Read the FREQUENCY, Ls, and Rs values
                    bool ok;
                    double frequency = data[0].toDouble(&ok);
                    double frequencyLs = data[0].toDouble(&ok);
                    double frequencyRs = data[0].toDouble(&ok);
                    double lsValue = data[1].toDouble(&ok);
                    double rsValue = data[2].toDouble(&ok);

                    if (ok)
                    {
                        if (frequency >= minFrequencyLS && frequency <= maxFrequencyLS)
                        {
                            frequenciesLs.append(frequencyLs);
                            lsValues.append(lsValue);
                            // rsValues.append(rsValue);

                            qDebug() << "Appended this LS VALUE: " << frequencyLs << " " << lsValue;
                        }

                        if (frequency >= minFrequencyRS && frequency <= maxFrequencyRS)
                        {
                            frequenciesRs.append(frequencyRs);
                            rsValues.append(rsValue);
                            // rsValues.append(rsValue);

                            qDebug() << "Appended this RS VALUE: " << frequencyRs << " " << rsValue;
                        }
                    }
                    else
                    {
                        QMessageBox::warning(this, "Warning", "CSV Files should be in this format: FREQUENCY,LS,RS.");

                        qDebug() << "Error reading values in line: " << line;
                        return;
                    }
                }
                else
                {
                    QMessageBox::warning(this, "Warning", "CSV Files should be in this format: FREQUENCY,LS,RS.");

                    qDebug() << "Invalid line format: " << line;
                    return;
                }
            }

            qDebug() << "Reading is done.";

            file.close();

            // Add data to the plot as a new CSVInfo entry  LS
            CSVInfo fileInfo;
            fileInfo.fileName = QFileInfo(fileName).baseName();
            fileInfo.frequenciesLs = frequenciesLs;
            fileInfo.lsValues = lsValues;
            // fileInfo.rsValues = rsValues;
            fileInfo.visible = true;	// Set visible to true initially

            qDebug() << "Append this file: " << fileInfo.fileName;
            loadedCSVLS.append(fileInfo);

            // Add data to the plot as a new CSVInfo2 entry for RS
            CSVInfo2 fileInfo2RS;
            fileInfo2RS.fileName = QFileInfo(fileName).baseName();
            fileInfo2RS.frequenciesRs = frequenciesRs;
            fileInfo2RS.rsValues = rsValues;
            fileInfo2RS.visible = true;

            qDebug() << "Append this file: " << fileInfo2RS.fileName;
            loadedCSVRS.append(fileInfo2RS);
        }
        else
        {
            QMessageBox::warning(this, "Warning", "Failed to open the file.");
            return;
            qDebug() << "Failed to open the file: " << fileName;
        }
    }

    // Update the plot based on the selected mode (LS or RS)
    if (ui->radioButton_Ls->isChecked())
    {
        on_radioButton_Ls_clicked();
    }
    else if (ui->radioButton_Rs->isChecked())
    {
        on_radioButton_Rs_clicked();
    }
}

// Button -> Export AVG as CSV
void MainWindow::on_btn_export_avg_clicked()
{
    if (loadedCSVRS.isEmpty() && loadedCSVLS.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "No CSV data loaded. Load CSV files first.");
        return;
    }

    int averageGraphIndex = -1;
    for (int i = 0; i < ui->Plot->graphCount(); ++i)
    {
        QCPGraph *graph = ui->Plot->graph(i);
        if (graph && (graph->name() == "Average LS" || graph->name() == "Average RS"))
        {
            averageGraphIndex = i;
            break;
        }
    }

    if (averageGraphIndex == -1)
    {
        QMessageBox::warning(this, "Warning", "There is no Average Graph. Calculate Average Graph first.");
        return;	// Handle the case where the average graph is not found
    }

    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString csvDataFolderPath = desktopPath + "/CSV DATA";
    QString currentTimeFolderName = QTime::currentTime().toString("hh_mm_ss") + "-AVG";
    QString avgGraphFolderPath = csvDataFolderPath + "/" + currentTimeFolderName;

    // Create the "CSV DATA" folder if it doesn't exist
    QDir csvDataDir(csvDataFolderPath);
    if (!csvDataDir.exists())
    {
        csvDataDir.mkpath(".");
    }

    // Create the subfolder for the current average graph
    QDir avgGraphDir(avgGraphFolderPath);
    if (!avgGraphDir.exists())
    {
        avgGraphDir.mkpath(".");
    }

    QVector<double> averageValues = calculateAverageValues(ui->radioButton_Ls->isChecked(), true);

    // Set the default file name for the saving window
    QString defaultFileName = "average_data.csv";

    // Set the initial directory for the file save dialog
    QString defaultSavePath = avgGraphFolderPath + "/" + defaultFileName;

    // Show the file save dialog inside the subfolder for the average graph
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Average Graph Data"), defaultSavePath, tr("CSV Files (*.csv);;All Files (*)"));

    // Show the file save dialog inside the subfolder for the average graph
    // QString filePath = avgGraphFolderPath + "/average_data.csv";

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);

        // Write CSV header
        bool useLsData = ui->radioButton_Ls->isChecked();
        bool useRsData = ui->radioButton_Rs->isChecked();

        stream << "FREQUENCY,Ls,Rs\n";

        // Write average graph data
        if (useLsData)
        {
            for (int i = 0; i < loadedCSVLS[0].frequenciesLs.size(); ++i)
            {
                stream << loadedCSVLS[0].frequenciesLs[i] << "," << averageValues[i] << ",0";
                stream << "\n";
            }
        }
        else if (useRsData)
        {
            for (int i = 0; i < loadedCSVRS[0].frequenciesRs.size(); ++i)
            {
                stream << loadedCSVRS[0].frequenciesRs[i] << ",0," << averageValues[i];	// Set LS column to zeros
                stream << "\n";
            }
        }

        file.close();
        qDebug() << "Average graph data exported to: " << filePath;

        // Write README file
        QFile readmeFile(avgGraphFolderPath + "/README.txt");
        if (readmeFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream readmeStream(&readmeFile);
            readmeStream << "Average Graph Data\n";
            readmeStream << "Using the following Core for calculation:\n";
            if (useLsData)
            {
                for (int i = 0; i < loadedCSVLS.size(); ++i)
                {
                    if (loadedCSVLS[i].visible)
                    {
                        readmeStream << "CORE:  " << (loadedCSVLS[i].fileName) << "\n";
                    }
                }
            }
            else
            {
                for (int i = 0; i < loadedCSVRS.size(); ++i)
                {
                    if (loadedCSVRS[i].visible)
                    {
                        readmeStream << "CORE: " << (loadedCSVRS[i].fileName) << "\n";
                    }
                }
            }

            readmeFile.close();
            qDebug() << "README file created: " << readmeFile.fileName();
        }
        else
        {
            qDebug() << "Failed to create README file: " << readmeFile.fileName();
        }
    }
    else
    {
        qDebug() << "Failed to open file for writing: " << filePath;
    }
}
