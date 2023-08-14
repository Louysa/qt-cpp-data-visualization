/**
 *@file graphFunctions.cpp
 *@brief Implementation of functions for managing graph interactions and visualization
 *
 *This file contains the implementation of various functions for managing graph interactions,
 *visualization, and user interactions in the data visualization application. It includes methods
 *for adding average graphs, hiding/showing selected graphs, managing tracers, zooming functionality,
 *and more. These functions are essential for providing a rich and interactive experience to the users
 *while analyzing and exploring data graphs.
 *
 *@note This file should be included along with the MainWindow class implementation to ensure
 *proper functioning of the graph-related functionality in the data visualization application.
 *
 *@author[Dogan Can Oz]
 *@date[8/14/23]
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

// Setup Plot
void MainWindow::setupPlot()
{
    // X axis
    ui->Plot->xAxis->setLabel("FREQUENCY");
    ui->Plot->xAxis->setLabelFont(QFont("Calibri", 16));
    ui->Plot->xAxis->setLabelColor(QColor(Qt::black));
    ui->Plot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));

    // Y axis
    ui->Plot->yAxis->setLabel("DATA");
    ui->Plot->yAxis->setLabelColor(QColor(Qt::black));
    ui->Plot->yAxis->setLabelFont(QFont("Calibri", 16));
    ui->Plot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));

    // Setting Window Size
    //setFixedSize(1548,824);

    //Setting Lines
    lines = QList<QCPItemStraightLine*> ();

    // Tracer combo Box
    ui->comboBox_tracer->setCurrentIndex(4);

    // Plot BackgroundColor
    ui->Plot->setBackground(QColor(155, 164, 181));

    // Interactions
    ui->Plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectItems | QCP::iMultiSelect);
    ui->Plot->setMouseTracking(true);
    // Hold Ctrl to select multiple graphs
    ui->Plot->setMultiSelectModifier(Qt::ControlModifier);

    ui->radioButton_Ls->setChecked(true);
    ui->Plot->legend->setVisible(true);
    ui->cbox_Tracer->setChecked(false);

    on_radioButton_Ls_clicked();

    ui->Plot->setContextMenuPolicy(Qt::CustomContextMenu);
    // Set visible every Graphs
    for (int i = 0; i < ui->Plot->graphCount(); ++i)
    {
        QCPGraph *graph = ui->Plot->graph(i);
        if (graph)
        {
            graph->setVisible(true);
        }
    }
}

// Clear Everything
void MainWindow::clearEverything()
{
    // Clear the data from every graph
    for (int x = 0; x < ui->Plot->graphCount(); x++)
    {
        ui->Plot->graph(x)->data()->clear();
    }

    loadedCSVLS.resize(0);
    loadedCSVRS.resize(0);

    ui->Plot->legend->clearItems();

    // Clear Graphs
    ui->Plot->clearGraphs();

    // Reset the x-axis range to start from 0
    ui->Plot->replot();

    recordedPoints.clear();

    for (QCPItemStraightLine *line: lines)
    {
        delete line;
    }

    lines.clear();

    ui->Plot->replot();

    avg = false;
}

// Right Click Context Menu
void MainWindow::contextMenuRequest(const QPoint &pos)
{
    // Create the context menu
    graphMenu = new QMenu(this);
    graphMenu->setAttribute(Qt::WA_DeleteOnClose);

    // Add actions for each legend item and create checkboxes for them
    for (int i = 0; i < ui->Plot->graphCount(); ++i)
    {
        QCPGraph *graph = ui->Plot->graph(i);
        if (graph)
        {
            // Create a checkable action for each graph
            QAction *graphAction = new QAction(graph->name(), graphMenu);
            graphAction->setCheckable(true);
            graphAction->setChecked(graph->visible());
            graphMenu->addAction(graphAction);	// Add the action to the menu

            // Connect the action toggled signal to a custom slot
            connect(graphAction, &QAction::toggled, this, &MainWindow::onGraphVisibilityChanged);
            graphAction->setData(QVariant::fromValue(graph));
        }
    }

    //Create a "Only Show Selected Graph" action
    QAction *showSelectedAction = new QAction("Show Only Selected Graphs", graphMenu);
    graphMenu->addAction(showSelectedAction);
    connect(showSelectedAction, &QAction::triggered, this, &MainWindow::hideUnselectedGraphs);

    // Create a "Hide Selected Graph" action
    QAction *hideSelectedAction = new QAction("Hide Selected Graphs", graphMenu);
    graphMenu->addAction(hideSelectedAction);
    connect(hideSelectedAction, &QAction::triggered, this, &MainWindow::hideSelectedGraph);

    // Create a "Compare" action for each graph
    QAction *compareAction = new QAction("Compare", graphMenu);
    graphMenu->addAction(compareAction);
    connect(compareAction, &QAction::triggered, this, [=]()
            {
                double xValue = ui->Plot->xAxis->pixelToCoord(pos.x());	// Get cursor's x coordinate
                compareFrequency(xValue);
            });

    // Show the context menu at the mouse position
    graphMenu->popup(ui->Plot->mapToGlobal(pos));
}

// Creating Tracer
void MainWindow::createChartTracer()
{
    // add the phase tracer (red circle) which sticks to the graph data:
    this->phaseTracer = new QCPItemTracer(ui->Plot);
    this->phaseTracer->setInterpolating(false);

    if (ui->comboBox_tracer->currentIndex() == 0)
        this->phaseTracer->setStyle(QCPItemTracer::tsCrosshair);
    else if (ui->comboBox_tracer->currentIndex() == 1)
        this->phaseTracer->setStyle(QCPItemTracer::tsCircle);
    else if (ui->comboBox_tracer->currentIndex() == 2)
        this->phaseTracer->setStyle(QCPItemTracer::tsPlus);
    else if (ui->comboBox_tracer->currentIndex() == 3)
        this->phaseTracer->setStyle(QCPItemTracer::tsSquare);
    else
        this->phaseTracer->setStyle(QCPItemTracer::tsNone);

    this->phaseTracer->setPen(QPen(Qt::red));
    this->phaseTracer->setBrush(Qt::red);
    this->phaseTracer->setSize(8);

}

// Tracer find NearestDataPoint
int MainWindow::findNearestDataPoint(QSharedPointer<QCPGraphDataContainer> data, double xValue)
{
    if (!data || data->size() == 0)

    return -1;

    int lowerIndex = 0;
    int upperIndex = data->size() - 1;

    // Binary search for the nearest data point
    while (lowerIndex <= upperIndex)
    {
        int middleIndex = (lowerIndex + upperIndex) / 2;
        double middleX = data->at(middleIndex)->key;

        if (xValue < middleX)
        {
            upperIndex = middleIndex - 1;
        }
        else if (xValue > middleX)
        {
            lowerIndex = middleIndex + 1;
        }
        else
        {
            // Exact match, return the index
            return middleIndex;
        }
    }

    // The data point was not found, return the index of the nearest data point
    if (upperIndex < 0)
        return 0;
    else if (lowerIndex >= data->size())
        return data->size() - 1;
    else
    {
        // Check which data point is closer and return its index
        double lowerX = data->at(upperIndex)->key;
        double upperX = data->at(lowerIndex)->key;
        return std::abs(xValue - lowerX)<std::abs(xValue - upperX) ? upperIndex : lowerIndex;
    }
}

// Hide/Show Tracer CheckBox
void MainWindow::on_cbox_Tracer_clicked(bool checked)	//tracer
{
    if (checked)
    {
        createChartTracer();

        // Connect the mouseMove signal to the on_tracerShowPointValue slot
        connect(ui->Plot, &QCustomPlot::mouseMove, this, &MainWindow::on_tracerShowPointValue);
    }
    else
    {
        // Disconnect the mouseMove signal from the on_tracerShowPointValue slot
        disconnect(ui->Plot, &QCustomPlot::mouseMove, this, &MainWindow::on_tracerShowPointValue);

        delete phaseTracer;
        phaseTracer = nullptr;
    }
}

// Rescaling Plot with Double Click
void MainWindow::onPlotDoubleClick(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        ui->Plot->rescaleAxes(true);
        ui->Plot->yAxis->scaleRange(1.20);
    }

    ui->Plot->replot();
}

// Checking Average Graph for Visible Graphs
void MainWindow::onGraphVisibilityChanged(bool checked)
{
    QAction *graphAction = qobject_cast<QAction*> (sender());
    if (graphAction)
    {
        // Check if the graph action corresponds to the average graph
        bool isAverageGraph = graphAction == averageGraphActionLs || graphAction == averageGraphActionRs;

        if (isAverageGraph)
        {
            // Update the visibility of the average graph
            bool useLsData = ui->radioButton_Ls->isChecked();
            QVector<double> averageValues = calculateAverageValues(useLsData, true);	// or false, depending on your needs

            if (graphAction == averageGraphActionLs)
            {
                addAverageGraph(averageValues, useLsData);
            }
            else if (graphAction == averageGraphActionRs)
            {
                addAverageGraph(averageValues, useLsData);
            }
        }
        else
        {
            // For other regular graphs, update their visibility
            QCPGraph *graph = graphAction->data().value<QCPGraph*> ();
            if (graph)
            {
                graph->setVisible(checked);

                if (checked == false)
                {
                    graph->removeFromLegend();
                }
                else
                {
                    graph->addToLegend();
                }

                qDebug() << "Graph visibility changed: " << graph->name() << " -> " << (checked ? "Visible" : "Hidden");
            }
        }

        bool useLSData = ui->radioButton_Ls->isChecked();

        if (useLSData)
        {
            for (int i = 0; i < loadedCSVLS.size(); ++i)
            {
                QCPGraph *graph = ui->Plot->graph(i);
                if (graph)
                {
                    loadedCSVLS[i].visible = graph->visible();
                }
            }

            ui->Plot->replot();
        }
        else
        {
            for (int i = 0; i < loadedCSVRS.size(); ++i)
            {
                QCPGraph *graph = ui->Plot->graph(i);
                if (graph)
                {
                    loadedCSVRS[i].visible = graph->visible();
                }
            }

            ui->Plot->replot();
        }
    }
}

// Calculating DistanceRatio
void MainWindow::calculateDistanceRatios()
{
    qDebug() << "Calculating distance ratios...";
    bool distanceRatiosCalculated = false;

    double maxDistanceRatio = 0.0;
    distanceRatios.clear();

    bool useLsData = ui->radioButton_Ls->isChecked();
    qDebug() << "Using" << (useLsData ? "LS" : "RS") << "data for calculations.";

    // Calculate the average values based on the selected mode (LS or RS)

    QVector<double> averageValues = calculateAverageValues(useLsData, true);

    // Calculate the average graph if it is not available already
    if (averageValues.isEmpty())
    {
        qDebug() << "Calculating average graph...";

        bool useLsData = ui->radioButton_Ls->isChecked();

        QVector<double> averageValues = calculateAverageValues(useLsData, true);

        // or false, depending on your needs
        qDebug() << "Average values:" << averageValues;

        // Add the new average graph
        addAverageGraph(averageValues, useLsData);
    }

    // If distance ratios not calculated, then calculate
    if (!distanceRatiosCalculated)
    {
        if (useLsData)
        {
            qDebug() << " YOU ARE IN";

            for (const CSVInfo &fileInfo: loadedCSVLS)
            {
                if (!fileInfo.visible)
                {
                    continue;
                }

                const QVector<double> &data = useLsData ? fileInfo.lsValues : fileInfo.rsValues;

                double sumDifference = 0.0;
                int visibleDataPoints = 0;

                for (int j = 0; j < data.size(); ++j)
                {
                    if (fileInfo.visible)
                    {
                        double difference = std::abs(data[j] - averageValues[j]);
                        sumDifference += difference;
                        ++visibleDataPoints;
                    }
                }

                double averageDifference = (visibleDataPoints > 0) ? sumDifference / visibleDataPoints : 0.0;

                // Calculate the distance ratio as a proportion of the average difference
                double ratioArray = averageDifference;
                if (ratioArray > maxDistanceRatio)
                {
                    maxDistanceRatio = ratioArray;
                }
            }

            for (const CSVInfo &fileInfo: loadedCSVLS)
            {
                if (!fileInfo.visible)
                {
                    distanceRatio = 101.10;
                    distanceRatios.push_back(distanceRatio);

                    qDebug() << "-------------------------------";
                    qDebug() << "Graph:" << fileInfo.fileName;
                    qDebug() << "Not included ";
                    qDebug() << "Distance Ratio:" << distanceRatio;
                    qDebug() << "-------------------------------";

                    continue;
                }

                const QVector<double> &data = useLsData ? fileInfo.lsValues : fileInfo.rsValues;

                double sumDifference = 0.0;
                int visibleDataPoints = 0;

                for (int j = 0; j < data.size(); ++j)
                {
                    if (fileInfo.visible)
                    {
                        double difference = std::abs(data[j] - averageValues[j]);
                        sumDifference += difference;
                        ++visibleDataPoints;
                    }
                }

                double averageDifference = (visibleDataPoints > 0) ? sumDifference / visibleDataPoints : 0.0;

                // Calculate the distance ratio as a proportion of the maximum difference
                double distanceRatio = averageDifference / maxDistanceRatio;

                distanceRatios.push_back(distanceRatio);

                qDebug() << "-------------------------------";
                qDebug() << "Graph:" << fileInfo.fileName;
                qDebug() << "Visible Data Points:" << visibleDataPoints;
                qDebug() << "Sum Difference:" << sumDifference;
                qDebug() << "Average Difference:" << averageDifference;
                qDebug() << "Distance Ratio:" << distanceRatio;
                qDebug() << "-------------------------------";
            }

            qDebug() << "Max Distance Ratio:" << maxDistanceRatio;
            qDebug() << "-------------------------------";
        }
        else
        {
            qDebug() << " YOU ARE IN";
            for (const CSVInfo2 &fileInfo2RS: loadedCSVRS)
            {
                if (!fileInfo2RS.visible)
                {
                    continue;
                }

                const QVector<double> &data = useLsData ? fileInfo2RS.lsValues : fileInfo2RS.rsValues;

                double sumDifference = 0.0;
                int visibleDataPoints = 0;

                for (int j = 0; j < data.size(); ++j)
                {
                    if (fileInfo2RS.visible)
                    {
                        double difference = std::abs(data[j] - averageValues[j]);
                        sumDifference += difference;
                        ++visibleDataPoints;
                    }
                }

                double averageDifference = (visibleDataPoints > 0) ? sumDifference / visibleDataPoints : 0.0;

                // Calculate the distance ratio as a proportion of the average difference
                double ratioArray = averageDifference;
                if (ratioArray > maxDistanceRatio)
                {
                    maxDistanceRatio = ratioArray;
                }
            }

            for (const CSVInfo2 &fileInfo2RS: loadedCSVRS)
            {
                if (!fileInfo2RS.visible)
                {
                    distanceRatio = 101.10;
                    distanceRatios.push_back(distanceRatio);

                    qDebug() << "-------------------------------";
                    qDebug() << "Graph:" << fileInfo2RS.fileName;
                    qDebug() << "Not included ";
                    qDebug() << "Distance Ratio:" << distanceRatio;
                    qDebug() << "-------------------------------";

                    continue;
                }

                const QVector<double> &data = useLsData ? fileInfo2RS.lsValues : fileInfo2RS.rsValues;

                double sumDifference = 0.0;
                int visibleDataPoints = 0;

                for (int j = 0; j < data.size(); ++j)
                {
                    if (fileInfo2RS.visible)
                    {
                        double difference = std::abs(data[j] - averageValues[j]);
                        sumDifference += difference;
                        ++visibleDataPoints;
                    }
                }

                double averageDifference = (visibleDataPoints > 0) ? sumDifference / visibleDataPoints : 0.0;

                // Calculate the distance ratio as a proportion of the maximum difference
                double distanceRatio = averageDifference / maxDistanceRatio;

                distanceRatios.push_back(distanceRatio);

                qDebug() << "-------------------------------";
                qDebug() << "Graph:" << fileInfo2RS.fileName;
                qDebug() << "Visible Data Points:" << visibleDataPoints;
                qDebug() << "Sum Difference:" << sumDifference;
                qDebug() << "Average Difference:" << averageDifference;
                qDebug() << "Distance Ratio:" << distanceRatio;
                qDebug() << "-------------------------------";
            }

            qDebug() << "Max Distance Ratio:" << maxDistanceRatio;
            qDebug() << "-------------------------------";
        }
    }

    // Replot the graph
    ui->Plot->replot();

}

// Button -> Highlight Button
void MainWindow::on_btn_HighlightGraphs_clicked()
{
    // If empty -> return
    if (loadedCSVRS.isEmpty() && loadedCSVLS.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "No CSV data loaded. Load CSV files first.");
        return;
    }

    if (avg == false)
    {
        QMessageBox::warning(this, "Warning", "Please Calculate Average Graph first.");
        return;
    }

    // If there are no AverageGraph -> return
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

    // Get the threshold percentage from the spin box
    double thresholdPercentage = ui->doubleSpinBox->value() / 100;

    qDebug() << "your percentege " << thresholdPercentage;

    if (ui->radioButton_Ls->isChecked())
    {
        // For LS
        for (int i = 0; i < loadedCSVLS.size(); ++i)
        {
            CSVInfo &fileInfo = loadedCSVLS[i];

            // Determine if the graph should be visible or hidden based on the threshold value
            bool isVisible = (distanceRatios[i] <= thresholdPercentage);
            fileInfo.visible = isVisible;

            QCPGraph *graph = ui->Plot->graph(i);
            if (graph)
            {
                graph->setVisible(isVisible);
                if (!isVisible)
                {
                    graph->removeFromLegend();
                }
                else
                {
                    graph->addToLegend();
                }
            }

            qDebug() << "Graph" << i + 1 << (isVisible ? "Visible" : "Hidden");
        }
    }
    else
    {
        // For RS
        for (int i = 0; i < loadedCSVRS.size(); ++i)
        {
            CSVInfo2 &fileInfo2RS = loadedCSVRS[i];

            // Determine if the graph should be visible or hidden based on the threshold value
            bool isVisible = (distanceRatios[i] <= thresholdPercentage);
            fileInfo2RS.visible = isVisible;

            QCPGraph *graph = ui->Plot->graph(i);
            if (graph)
            {
                graph->setVisible(isVisible);
                if (!isVisible)
                {
                    graph->removeFromLegend();
                }
                else
                {
                    graph->addToLegend();
                }
            }

            qDebug() << "Graph" << i + 1 << (isVisible ? "Visible" : "Hidden");
        }
    }

    // Replot the graph
    ui->Plot->replot();
}

// Tracer Showing Value
void MainWindow::on_tracerShowPointValue(QMouseEvent *event)	// Tracer Showing Value
{
    if (ui->cbox_Tracer->isChecked() && ui->Plot->graphCount() > 0)
    {
        if (ui->Plot->graphCount() < 1)
            return;

        // Get selected graph (in my case selected means the plot is selected from the legend)
        QCPGraph *graph = nullptr;
        for (auto i = 0; i < ui->Plot->graphCount(); ++i)
        {
            if (ui->Plot->graph(i)->selected())
            {
                graph = ui->Plot->graph(i);
                break;
            }
        }

        if (graph == nullptr)
            return;

        // Setup the item tracer
        this->phaseTracer->setGraph(graph);
        this->phaseTracer->setGraphKey(ui->Plot->xAxis->pixelToCoord(event->pos().x()));
        ui->Plot->replot();
        bool useLsData = ui->radioButton_Ls->isChecked();

        // **********Get the values from the item tracer's coords***********
        QPointF temp = this->phaseTracer->position->coords();

        updateLineEdits(convertFrequency(temp.x()), useLsData ? convertLsValue(temp.y()) : convertRsValue(temp.y()));

        QToolTip::showText(event->globalPosition().toPoint(),
                           tr("<h4>%1</h4>"
                              "<table>"
                              "<tr>"
                              "<td>FREQUENCY: %2</td>"
                              "<td> , </td>"
                              "<td>VALUE: %3</td>"
                              "</tr>"
                              "</table>").arg(graph->name())
                               .arg(convertFrequency(temp.x()))
                               .arg(useLsData ? convertLsValue(temp.y()) : convertRsValue(temp.y())));
    }
    else
    {
        // If the checkbox is not checked or no graphs are present, hide the tooltip
        QToolTip::hideText();
    }
}

// Generating Random RGB Values
QList<QColor> MainWindow::generateColorPalette(int count)
{
    QList<QColor> resultPalette;
    QSet<QRgb> usedColors;	// Keep track of used RGB values

    for (int i = 0; i < count; ++i)
    {
        int red, green, blue;
        QRgb rgb;

        // Generate unique color (excluding black)
        do { 	red = rand() % 256;
            green = rand() % 256;
            blue = rand() % 256;

            rgb = qRgb(red, green, blue);
        } while (usedColors.contains(rgb) || (qRed(rgb) < 10 && qGreen(rgb) < 10 && qBlue(rgb) < 10));	// Check if the RGB value is already used or if it's close to black

        usedColors.insert(rgb);	// Mark RGB value as used
        resultPalette.append(QColor(rgb));
    }

    return resultPalette;
}

// Button -> Clear
void MainWindow::on_btn_clear_plot_clicked()
{
    clearEverything();

}

// Button -> Export Graph as PNG
void MainWindow::on_btn_save_plot_clicked()	// Export Graph PNG
{
    if (loadedCSVRS.isEmpty() && loadedCSVLS.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "No CSV data loaded. Load CSV files first.");
        return;
    }

    // Prompt the user to choose the save location
    QString filePath = QFileDialog::getSaveFileName(this, "Save Screenshot", QDir::homePath(), "PNG Images (*.png)");

    if (!filePath.isEmpty())
    {
        // Get a pixmap of the entire plot area
        QPixmap pixmap = ui->Plot->toPixmap();

        // Save the pixmap as an image file
        pixmap.save(filePath);
    }
}

// Button -> Default
void MainWindow::on_btn_start_plot_clicked()
{
    if (loadedCSVRS.isEmpty() && loadedCSVLS.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "No CSV data loaded. Load CSV files first.");
        return;
    }

    if (ui->radioButton_Ls->isChecked())
    {
        on_radioButton_Ls_clicked();
    }
    else if (ui->radioButton_Rs->isChecked())
    {
        on_radioButton_Rs_clicked();
    }
}

// Button -> Calculate Average Graph
void MainWindow::on_btn_avg_clicked()
{
    if (loadedCSVRS.isEmpty() && loadedCSVLS.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "No CSV data loaded. Load CSV files first.");
        return;
        avg = false;
    }

    QVector<double> averageRSValues = calculateAverageValues(false, true);
    qDebug() << "Calculated Average RS ";
    QVector<double> averageLSValues = calculateAverageValues(true, true);
    qDebug() << "Calculated Average LS ";
    avg = true;

    if (ui->radioButton_Ls->isChecked())
    {
        // Add the new average graph
        addAverageGraph(averageLSValues, true);
    }
    else
    {
        addAverageGraph(averageRSValues, false);
    }

    calculateDistanceRatios();

}

// LS - View
void MainWindow::on_radioButton_Ls_clicked()
{
    // Define the number of graphs
    int graphCount = loadedCSVLS.size();
    qDebug() << graphCount;

    // Generate a color palette with the desired number of colors
    QList<QColor> graphColors = generateColorPalette(graphCount);
    qDebug() << "Color Palette generated.";

    // Clear the previous data from the graph
    ui->Plot->clearGraphs();

    // Add Ls data to the plot as a new graph
    for (int i = 0; i < loadedCSVLS.size(); ++i)
    {
        CSVInfo &fileInfo = loadedCSVLS[i];
        fileInfo.visible = true;

        if (fileInfo.visible)
        {
            ui->Plot->addGraph();
            qDebug() << "Added LS Graph succesfully";
            ui->Plot->graph(i)->setPen(QPen(graphColors[i]));	// Set the pen color for Ls graph
            ui->Plot->graph(i)->setData(fileInfo.frequenciesLs, fileInfo.lsValues);
            ui->Plot->graph(i)->setName(fileInfo.fileName);
            // Add scatter style for the data points
            QCPScatterStyle scatterStyle;
            scatterStyle.setShape(QCPScatterStyle::ssCircle);	// Circle shape
            scatterStyle.setPen(QPen(Qt::black));	// Black outline
            scatterStyle.setBrush(QBrush(graphColors[i]));	// Blue interior with 100 transparency
            scatterStyle.setSize(8);

            ui->Plot->graph(i)->setScatterStyle(scatterStyle);
        }
    }

    // Set labels for x and y axes
    ui->Plot->xAxis->setLabel("FREQUENCY");
    ui->Plot->yAxis->setLabel("Ls");

    // Rescale and replot the graph
    ui->Plot->rescaleAxes();
    ui->Plot->replot();
}

// RS - View
void MainWindow::on_radioButton_Rs_clicked()
{
    // Define the number of graphs
    int graphCount = loadedCSVRS.size();

    // Generate a color palette with the desired number of colors
    QList<QColor> graphColors = generateColorPalette(graphCount);

    // Clear the previous data from the graph
    ui->Plot->clearGraphs();

    // Add Rs data to the plot as a new graph
    for (int i = 0; i < loadedCSVRS.size(); ++i)
    {
        CSVInfo2 &fileInfo = loadedCSVRS[i];
        fileInfo.visible = true;
        if (fileInfo.visible)
        {
            ui->Plot->addGraph();
            qDebug() << "Added RS Graph succesfully";
            ui->Plot->graph(i)->setPen(QPen(graphColors[i]));	// Set the pen color for Rs graph
            ui->Plot->graph(i)->setData(fileInfo.frequenciesRs, fileInfo.rsValues);
            ui->Plot->graph(i)->setName(fileInfo.fileName);
            QCPScatterStyle scatterStyle;
            scatterStyle.setShape(QCPScatterStyle::ssCircle);	// Circle shape
            scatterStyle.setPen(QPen(Qt::black));	// Black outline
            scatterStyle.setBrush(QBrush(graphColors[i]));	// Red interior with 100 transparency
            scatterStyle.setSize(8);
            ui->Plot->graph(i)->setScatterStyle(scatterStyle);
        }
    }

    // Set labels for x and y axes
    ui->Plot->xAxis->setLabel("FREQUENCY");
    ui->Plot->yAxis->setLabel("Rs");

    // Rescale and replot the graph
    ui->Plot->rescaleAxes();
    ui->Plot->replot();

}

// Calculating Average Values
QVector<double> MainWindow::calculateAverageValues(bool useLsData, bool onlyVisibleGraphs)
{
    QVector<double> averageValues;
    int numFiles = 0;

    // Initialize the averageValues vector with zeros
    if (useLsData)
    {
        if (!loadedCSVLS.isEmpty())
        {
            for (int i = 0; i < loadedCSVLS[0].frequenciesLs.size(); ++i)
            {
                averageValues.append(0.0);
            }

            if (onlyVisibleGraphs)
            {
                // Calculate the sum of values for each frequency only for visible graphs
                for (const CSVInfo &fileInfo: loadedCSVLS)
                {
                    if (fileInfo.visible)
                    {
                        const QVector<double> &data = fileInfo.lsValues;
                        for (int i = 0; i < data.size(); ++i)
                        {
                            averageValues[i] += data[i];
                        }

                        numFiles++;
                    }
                }
            }
            else
            {
                // Calculate the sum of values for each frequency for all graphs
                for (const CSVInfo &fileInfo: loadedCSVLS)
                {
                    const QVector<double> &data = fileInfo.lsValues;
                    for (int i = 0; i < data.size(); ++i)
                    {
                        averageValues[i] += data[i];
                    }

                    numFiles++;
                }
            }
        }

        // Calculate the average values by dividing the sum by the number of files
        if (numFiles > 0)
        {
            for (int i = 0; i < averageValues.size(); ++i)
            {
                averageValues[i] /= numFiles;
            }
        }

        // Add debug statements to print which graphs are being used for calculation
        qDebug() << "Calculating average values using " << (useLsData ? "LS" : "RS") << " data:";
        for (int i = 0; i < loadedCSVLS.size(); ++i)
        {
            if (loadedCSVLS[i].visible)
            {
                qDebug() << "Graph " << (i + 1) << " is used in calculation.";
            }
        }

        return averageValues;
    }
    else
    {
        if (!loadedCSVRS.isEmpty())
        {
            for (int i = 0; i < loadedCSVRS[0].frequenciesRs.size(); ++i)
            {
                averageValues.append(0.0);
            }

            if (onlyVisibleGraphs)
            {
                // Calculate the sum of values for each frequency only for visible graphs
                for (const CSVInfo2 &fileInfo2RS: loadedCSVRS)
                {
                    if (fileInfo2RS.visible)
                    {
                        const QVector<double> &data = fileInfo2RS.rsValues;
                        for (int i = 0; i < data.size(); ++i)
                        {
                            averageValues[i] += data[i];
                        }

                        numFiles++;
                    }
                }
            }
            else
            {
                // Calculate the sum of values for each frequency for all graphs
                for (const CSVInfo2 &fileInfo2RS: loadedCSVRS)
                {
                    const QVector<double> &data = fileInfo2RS.rsValues;
                    for (int i = 0; i < data.size(); ++i)
                    {
                        averageValues[i] += data[i];
                    }

                    numFiles++;
                }
            }
        }

        // Calculate the average values by dividing the sum by the number of files
        if (numFiles > 0)
        {
            for (int i = 0; i < averageValues.size(); ++i)
            {
                averageValues[i] /= numFiles;
            }
        }

        // Add debug statements to print which graphs are being used for calculation
        qDebug() << "Calculating average values using " << (useLsData ? "LS" : "RS") << " data:";
        for (int i = 0; i < loadedCSVRS.size(); ++i)
        {
            if (loadedCSVRS[i].visible)
            {
                qDebug() << "Graph " << (i + 1) << " is used in calculation.";
            }
        }

        return averageValues;
    }
}

// Creating and Adding Average Graph
void MainWindow::addAverageGraph(const QVector<double> &averageValues, bool useLsData)
{
    // First, remove the previous average graph (if exists)
    for (int i = 0; i < ui->Plot->graphCount(); ++i)
    {
        QCPGraph *graph = ui->Plot->graph(i);
        if (graph->name() == "Average LS" || graph->name() == "Average RS")
        {
            ui->Plot->removeGraph(graph);
            break;	// Assuming there's only one average graph, so we break the loop after removing it.
        }
    }

    // Add the average data to the plot as a new graph
    QCPGraph *averageGraph = ui->Plot->addGraph();

    // Set the pen color for the average graph
    averageGraph->setPen(QPen(Qt::black));

    // Set the data for the average graph
    if (useLsData)
    {
        averageGraph->setData(loadedCSVLS[0].frequenciesLs, averageValues);
        averageGraph->setName("Average LS");
        averageGraphLs = averageGraph;
    }
    else
    {
        averageGraph->setData(loadedCSVRS[0].frequenciesRs, averageValues);
        averageGraph->setName("Average RS");
        averageGraphRs = averageGraph;
    }

    // Set the scatter style for the data points of the average graph
    QCPScatterStyle scatterStyle;
    scatterStyle.setShape(QCPScatterStyle::ssCircle);	// Circle shape
    scatterStyle.setPen(QPen(Qt::black));	// Black outline
    scatterStyle.setBrush(QBrush(Qt::black));	// Blue or red interior with 100% transparency
    scatterStyle.setSize(8);
    averageGraph->setScatterStyle(scatterStyle);

    // Set labels for x and y axes
    ui->Plot->xAxis->setLabel("FREQUENCY");
    ui->Plot->yAxis->setLabel(useLsData ? "LS Average" : "RS Average");

    // Rescale and replot the graph
    ui->Plot->rescaleAxes();
    ui->Plot->replot();
}

// Hide Selected Graphs
void MainWindow::hideSelectedGraph()
{

    // Iterate through all graphs and hide selected ones
    for (auto i = 0; i < ui->Plot->graphCount(); ++i)
    {
        QCPGraph *graph = ui->Plot->graph(i);
        if (graph->selected())
        {
            // Hide the selected graph
            graph->setVisible(false);
            graph->removeFromLegend();


            // Update the visibility flag in the corresponding CSVInfo
            if (ui->radioButton_Ls->isChecked())
            {
                if (i < loadedCSVLS.size())
                {
                    loadedCSVLS[i].visible = false;
                }
            }
            else
            {
                if (i < loadedCSVRS.size())
                {
                    loadedCSVRS[i].visible = false;
                }
            }
        }


    }

    ui->Plot->replot();	// Update the plot
}



// Show Only Selected Graphs
void MainWindow::hideUnselectedGraphs()
{


    for (int i = 0; i < ui->Plot->graphCount(); ++i)
    {
        QCPGraph *graph = ui->Plot->graph(i);
        if (graph && !graph->selected())
        {
            graph->setVisible(false);
            graph->removeFromLegend();


            // Update the visibility flag in the corresponding CSVInfo
            if (ui->radioButton_Ls->isChecked())
            {
                if (i < loadedCSVLS.size())
                {
                    loadedCSVLS[i].visible = false;
                }
            }
            else
            {
                if (i < loadedCSVRS.size())
                {
                    loadedCSVRS[i].visible = false;
                }
            }
        }

    }

    ui->Plot->replot();	// Update the plot
}

// Tracer Style Update
void MainWindow::on_comboBox_tracer_currentTextChanged()
{
    if (ui->cbox_Tracer->isChecked())
    {
        // Check if a tracer is already active
        if (phaseTracer == nullptr)
        {
            // Create a new tracer
            createChartTracer();
            connect(ui->Plot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(on_tracerShowPointValue(QMouseEvent*)));
        }

        createChartTracer();

        ui->Plot->replot();
    }
    else
    {
        // Hide or remove the current tracer
        if (phaseTracer != nullptr)
        {
            // You can hide the tracer by disabling its interactivity
            phaseTracer->setInterpolating(false);

            // Call replot to update the chart with the hidden tracer
            ui->Plot->replot();
        }
    }
}

// Button -> ZoomIn X
void MainWindow::on_btn_zoom_x_clicked()
{
    double factor = 0.8;	// Zoom factor
    double lower = ui->Plot->xAxis->range().lower;
    double upper = ui->Plot->xAxis->range().upper;

    double newLower = lower + (upper - lower) *(1 - factor) / 2;
    double newUpper = upper - (upper - lower) *(1 - factor) / 2;

    ui->Plot->xAxis->setRange(newLower, newUpper);
    ui->Plot->replot();
}

// Button -> ZoomIn Y
void MainWindow::on_btn_zoom_y_clicked()
{
    double factor = 0.8;	// Zoom factor
    double lower = ui->Plot->yAxis->range().lower;
    double upper = ui->Plot->yAxis->range().upper;

    double newLower = lower + (upper - lower) *(1 - factor) / 2;
    double newUpper = upper - (upper - lower) *(1 - factor) / 2;

    ui->Plot->yAxis->setRange(newLower, newUpper);
    ui->Plot->replot();
}

// Rectangle Zoom CheckBox
void MainWindow::on_cbox_r_zoom_clicked(bool checked)
{
    if (checked)
    {
        // Enable rectangle zooming
        ui->Plot->setInteractions(QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectItems);
        ui->Plot->setSelectionRectMode(QCP::srmZoom);
        QCPSelectionRect *selectionRect = ui->Plot->selectionRect();
        selectionRect->setBrush(QBrush(Qt::blue, Qt::Dense4Pattern));
        selectionRect->setPen(QPen(Qt::blue));
    }
    else
    {
        // Enable range dragging and disable rectangle zooming
        ui->Plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectItems);
        ui->Plot->setSelectionRectMode(QCP::srmNone);
    }
}

// Button -> ZoomOut X
void MainWindow::on_btn_zoomout_x_clicked()
{
    double factor = 1.25;	// Zoom factor
    QCPRange xRange = ui->Plot->xAxis->range();

    double newLower = xRange.center() - (xRange.size() *factor) / 2;
    double newUpper = xRange.center() + (xRange.size() *factor) / 2;

    ui->Plot->xAxis->setRange(newLower, newUpper);
    ui->Plot->replot();
}

// Button -> ZoomOut Y
void MainWindow::on_btn_zoomout_y_clicked()
{
    double factor = 1.25;	// Zoom factor
    QCPRange yRange = ui->Plot->yAxis->range();

    double newLower = yRange.center() - (yRange.size() *factor) / 2;
    double newUpper = yRange.center() + (yRange.size() *factor) / 2;

    ui->Plot->yAxis->setRange(newLower, newUpper);
    ui->Plot->replot();
}

// Button -> Add Line
void MainWindow::on_btn_addValue_clicked()
{
    if (ui->cbox_Lines->isChecked())
    {
        double rsMin = ui->ledit_minValue->text().toDouble();
        double rsMax = ui->ledit_maxValue->text().toDouble();

        QCPItemStraightLine *lineMin = new QCPItemStraightLine(ui->Plot);
        lineMin->point1->setCoords(0, rsMin);
        lineMin->point2->setCoords(1, rsMin);

        QCPItemStraightLine *lineMax = new QCPItemStraightLine(ui->Plot);
        lineMax->point1->setCoords(0, rsMax);
        lineMax->point2->setCoords(1, rsMax);

        // QPen linePen(Qt::green);	// Change the color as needed
        lineMin->setPen(linePen);
        lineMax->setPen(linePen);

        lines.append(lineMin);
        lines.append(lineMax);

        ui->Plot->replot();
    }
    else
    {
        QMessageBox::warning(this, "Carefull", "You should opent the Lines first.");
        return;
    }
}

// Hide/Show Lines CheckBox
void MainWindow::on_cbox_Lines_clicked(bool checked)
{
    if (checked)
    {
        for (QCPItemStraightLine *line: lines)
        {
            line->setVisible(true);
        }

        ui->Plot->replot();
    }
    else
    {
        for (QCPItemStraightLine *line: lines)
        {
            line->setVisible(false);
        }

        ui->Plot->replot();
    }
}

// Clear Line Button
void MainWindow::on_btn_clearLine_clicked()
{
    for (QCPItemStraightLine *line: lines)
    {
        delete line;
    }

    lines.clear();

    ui->Plot->replot();
}

// Updating Line Colors
void MainWindow::on_combobox_line_color_currentIndexChanged(int index)
{
    if (index == 0)
        linePen = QPen(Qt::red);
    else if (index == 1)
        linePen = QPen(Qt::green);
    else if (index == 2)
        linePen = QPen(Qt::yellow);
    else if (index == 3)
        linePen = QPen(Qt::blue);
    else
        linePen = QPen(Qt::black);

}

// Selecting Graph and Adding them into a list
void MainWindow::handleGraphSelection()
{
    selectedGraphs.clear();

    for (int i = 0; i < ui->Plot->graphCount(); ++i)
    {
        QCPGraph *graph = ui->Plot->graph(i);
        if (graph->selected())
        {
            selectedGraphs.append(graph);
        }
    }
}

// Updating Frequency and VALUE LineEdit
void MainWindow::updateLineEdits(QString fre, QString value)
{
    ui->lineEdit->setText(fre);
    ui->lineEdit_2->setText(value);

}

// Update Graph Name in LineEdit
void MainWindow::updateGraphName()
{
    // Get selected graph
    QCPGraph *graph = nullptr;
    for (auto i = 0; i < ui->Plot->graphCount(); ++i)
    {
        if (ui->Plot->graph(i)->selected())
        {
            graph = ui->Plot->graph(i);
            break;
        }
    }

    if (graph == nullptr)
    {
        return;
    }

    ui->lineEdit_3->setText(graph->name());

}

// Show/Hide Legends
void MainWindow::on_cbox_legend_toggled(bool checked)	// Hide/Show Legends
{
    // Loop through the legends and set their visibility based on the checkbox state
    for (int i = 0; i < ui->Plot->legend->itemCount(); ++i)
    {
        ui->Plot->legend->item(i)->setVisible(checked);
    }

    ui->Plot->legend->setVisible(checked);

    // Replot the plot
    ui->Plot->replot();
}
