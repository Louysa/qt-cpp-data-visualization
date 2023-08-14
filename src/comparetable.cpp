/**
 *@file comparetable.cpp
 *@brief Implementation of functions for comparing recorded data points and displaying comparison results
 *
 *This file contains the implementation of functions related to comparing recorded data points and
 *displaying the comparison results in a table. It includes methods for comparing data points at a
 *target frequency, calculating distance ratios, and updating the comparison table with the results.
 *These functions are crucial for analyzing and presenting the differences between data points.
 *
 *@note This file should be included along with the MainWindow class implementation to ensure
 *proper functioning of the comparison functionality in the data visualization application.
 *
 *@author[Dogan Can Oz]
 *@date[8/14/23]
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setting.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

// Compare Values in same Frequency
void MainWindow::compareFrequency(double targetFrequency)
{
    // Find the data point index in the average graph's data
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
        qDebug() << "Average graph not found!";
        return;	// Handle the case where the average graph is not found
    }

    int averageGraphDataPointIndex = findNearestDataPoint(ui->Plot->graph(averageGraphIndex)->data(), targetFrequency);

    if (averageGraphDataPointIndex == -1)
        return;

    // Get the y value of the average graph at the target frequency
    double averageGraphY = ui->Plot->graph(averageGraphIndex)->data()->at(averageGraphDataPointIndex)->value;

    // Find the maximum difference among all graph points at the target frequency
    double maxDifference = 0.0;
    for (int i = 0; i < ui->Plot->graphCount(); ++i)
    {
        QCPGraph *graph = ui->Plot->graph(i);
        if (graph && graph->visible())
        {
            int dataPointIndex = findNearestDataPoint(graph->data(), targetFrequency);
            if (dataPointIndex == -1)
                continue;

            double graphY = graph->data()->at(dataPointIndex)->value;
            double difference = std::abs(graphY - averageGraphY);

            if (difference > maxDifference)
            {
                maxDifference = difference;
            }
        }
    }

    // Calculate distance ratio and distances for each graph's point
    for (int i = 0; i < ui->Plot->graphCount(); ++i)
    {
        QCPGraph *graph = ui->Plot->graph(i);
        if (graph && graph->visible())
        {
            int dataPointIndex = findNearestDataPoint(graph->data(), targetFrequency);
            if (dataPointIndex == -1)
                continue;

            double graphY = graph->data()->at(dataPointIndex)->value;
            double distanceToAverage = std::abs(graphY - averageGraphY);
            double distanceRatio = (maxDifference > 0.0) ? distanceToAverage / maxDifference : 0.0;

            // Get the current time

            // Add the recorded point to the list
            recordedPoints.append(RecordedPoint(graph->data()->at(dataPointIndex)->key, graphY, graph->name(), distanceRatio, distanceToAverage));
        }
    }

    // Update the table widget with the new recorded points
    updateRecordedPointsTable();
}

// Update Recorded Points for Compare
void MainWindow::updateRecordedPointsTable()
{
    tableWidget = new QTableWidget(this);
    bool useLsData = ui->radioButton_Ls->isChecked();

    // Clear the existing table
    tableWidget->clearContents();
    tableWidget->setRowCount(0);

    // Populate the table with recorded points' data
    for (int i = 0; i < recordedPoints.size(); ++i)
    {
        double x = recordedPoints[i].x;
        double y = recordedPoints[i].y;
        double distanceRatio = recordedPoints[i].distanceRatio;	// Get the distance ratio for this recorded point
        double totalDistanceToAverage = recordedPoints[i].totalDistanceToAverage;	// Get the total distance to average for this recorded point

        QString graphName = recordedPoints[i].graphName;

        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(convertFrequency(x)));
        tableWidget->setItem(row, 1, new QTableWidgetItem(useLsData ? convertLsValue(y) : convertRsValue(y)));
        tableWidget->setItem(row, 2, new QTableWidgetItem(useLsData ? convertFrequency(maxFrequencyLS) : convertFrequency(maxFrequencyRS)));
        tableWidget->setItem(row, 3, new QTableWidgetItem(useLsData ? convertFrequency(minFrequencyLS) : convertFrequency(minFrequencyRS)));
        tableWidget->setItem(row, 4, new QTableWidgetItem(graphName));
        tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(distanceRatio *100) + "%"));	// Add Distance Ratio column
        tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(totalDistanceToAverage)));	// Add Total Distance To Average column
    }
}

// Button -> Clear Table
void MainWindow::on_btn_tablo_clear_clicked()	//Clear Table Data
{
    recordedPoints.clear();

}

// Button -> Compare Table
void MainWindow::on_btn_tablo_clicked()	//Create and exec table
{
    if (avg == false)
    {
        QMessageBox::warning(this, "Warning", "Please Calculate Average First");
        return;
    }

    if (recordedPoints.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please Compare Points First");
        return;
    }

    bool useLsData = ui->radioButton_Ls->isChecked();

    // Getting values witH QUERY
    QSqlQuery query;
    bool success = query.exec("SELECT min_freq_ls, max_freq_ls, min_freq_rs, max_freq_rs FROM frequency_range");
    if (success && query.next())
    {
        double minFreqLS = query.value("min_freq_ls").toDouble();
        double maxFreqLS = query.value("max_freq_ls").toDouble();
        double minFreqRS = query.value("min_freq_rs").toDouble();
        double maxFreqRS = query.value("max_freq_rs").toDouble();

        setting rangeDialog(this);

        QDialog *pointDialog = new QDialog(this);
        pointDialog->setWindowTitle("Recorded Points");
        pointDialog->setFixedSize(1450, 800);

        QVBoxLayout *layout = new QVBoxLayout(pointDialog);

        QTableWidget *tableWidget = new QTableWidget(pointDialog);
        tableWidget->setColumnCount(7);	// Add an extra column for the time
        tableWidget->setHorizontalHeaderLabels(QStringList() << "Frequency" << "Rs/Ls Value" << "MAX" << "MIN" << "Graphic Name" << "Distance Ratio" << "Total Distance To Average");

        // Adjust column widths
        tableWidget->setColumnWidth(0, 200);	// Frequency column
        tableWidget->setColumnWidth(1, 200);	// Rs/Ls Value column
        tableWidget->setColumnWidth(2, 200);	// Max
        tableWidget->setColumnWidth(3, 200);	// Min
        tableWidget->setColumnWidth(4, 200);	// Graph Name
        tableWidget->setColumnWidth(5, 200);	// Distance Ratio
        tableWidget->setColumnWidth(6, 200);	// Total Difference

        // Populate the table with recorded points' data
        for (int i = 0; i < recordedPoints.size(); ++i)
        {
            double x = recordedPoints[i].x;
            double y = recordedPoints[i].y;
            double distanceRatio = recordedPoints[i].distanceRatio;	// Get the distance ratio for this recorded point
            double totalDistanceToAverage = recordedPoints[i].totalDistanceToAverage;

            QString graphName = recordedPoints[i].graphName;

            int row = tableWidget->rowCount();
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(convertFrequency(x)));
            tableWidget->setItem(row, 1, new QTableWidgetItem(useLsData ? convertLsValue(y) : convertRsValue(y)));
            tableWidget->setItem(row, 2, new QTableWidgetItem(useLsData ? convertFrequency(maxFreqLS) : convertFrequency(maxFreqRS)));
            tableWidget->setItem(row, 3, new QTableWidgetItem(useLsData ? convertFrequency(minFreqLS) : convertFrequency(minFreqRS)));
            tableWidget->setItem(row, 4, new QTableWidgetItem(graphName));
            tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(distanceRatio *100) + "%"));	// Add Distance Ratio column
            tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(totalDistanceToAverage)));	// Add Total Distance To Average column
        }

        layout->addWidget(tableWidget);

        pointDialog->setLayout(layout);
        pointDialog->exec();
    }
}

// Convert Frequency
QString MainWindow::convertFrequency(double rawFrequency)
{
    // Assuming rawFrequency is in Hertz (Hz)
    // Convert to kilohertz (kHz) for display
    double convertedFrequency = rawFrequency;

    if (convertedFrequency >= 0 && convertedFrequency < 1000)
    {
        return QString::number(convertedFrequency, 'f', 2) + " Hz";
    }
    else if (convertedFrequency >= 1000 && convertedFrequency < 1000000)
    {
        return QString::number(convertedFrequency / 1000, 'f', 2) + " kHz";
    }
    else if (convertedFrequency >= 100000)
    {
        return QString::number(convertedFrequency / 1000000, 'f', 2) + " MHz";
    }
    else return QString::number(0, 'f', 2) + " Hz";
}

// Convert LSValue
QString MainWindow::convertLsValue(double rawValue)
{
    // Assuming rawValue is in henries
    // Convert to millihenries (mH) for display
    double convertedValue = rawValue *1000.0;

    // Format the value with appropriate precision and unit
    return QString::number(convertedValue, 'f', 2) + " mH";
}

// Convert RSValue
QString MainWindow::convertRsValue(double rawValue)
{
    // Assuming rawValue is in ohms
    // No conversion needed, just format the value
    if (rawValue < 0 && rawValue)
    {
        return QString::number(rawValue *1000, 'f', 2) + " mΩ";
    }
    else if (rawValue >= 0 && rawValue < 1000)
        return QString::number(rawValue, 'f', 2) + " Ω";
               else if (rawValue >= 1000 && rawValue < 1000000)
        {
            return QString::number(rawValue / 1000, 'f', 2) + " kΩ";
        }
    else if (rawValue >= 1000000)
    {
        return QString::number(rawValue / 1000000, 'f', 4) + " MΩ";
    }
    else
    {
        return QString::number(0, 'f', 2) + " Ω";
    }
}
