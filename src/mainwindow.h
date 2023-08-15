#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qsqldatabase.h"
#include <QMainWindow>
#include <QTimer>
#include <qcustomplot.h>
#include <QStandardPaths>
#include <QDir>
#include <QImage>
#include <QApplication>
#include <QFont>
#include <QMenu>
#include <QAction>
#include <QCursor>
#include <QContextMenuEvent>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// For Compare Table
struct RecordedPoint
{
    double x;
    double y;
    QString graphName;
    double distanceRatio; // Add this member
    double totalDistanceToAverage; // Add this member

    RecordedPoint(double x, double y, const QString &graphName,
                  double distanceRatio = 0.0, double totalDistanceToAverage = 0.0)
        : x(x), y(y), graphName(graphName),
        distanceRatio(distanceRatio), totalDistanceToAverage(totalDistanceToAverage)
    {
    }
};

// For LS
struct CSVInfo {
    // For Ls
    QColor color;
    QString fileName;
    QVector<double> frequencies;
    QVector<double> lsValues;
    QVector<double> rsValues;
    QVector<double> frequenciesRs;
    QVector<double> frequenciesLs;
    QVector<double> values;
    bool visible;
    double averageLs;
    double averageRs;
};
// For RS
struct CSVInfo2 {
    // For Rs
    QColor color;
    QString fileName;
    QVector<double> frequencies;
    QVector<double> lsValues;
    QVector<double> rsValues;
    QVector<double> frequenciesRs;
    QVector<double> frequenciesLs;
    QVector<double> values;
    bool visible;
    double averageLs;
    double averageRs;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // CSV's
    QVector<CSVInfo> loadedCSV;
    QVector<CSVInfo2> loadedCSVRS;
    QVector<CSVInfo> loadedCSVLS;
    QStringList fileNames;

    //Tracer
    QCPItemTracer* phaseTracer = nullptr;

    // Plot Image
    QImage image;

    // Graph Color list
    QVector<QColor> graphColors;

    // RS-LS Graphs
    QVector<double> averageLSValues;
    QVector<double> averageRSValues;
    QCPGraph *averageGraphLs = nullptr; // Average graph for Ls data
    QCPGraph *averageGraphRs = nullptr; // Average graph for Rs data
    QAction* averageGraphActionLs;
    QAction* averageGraphActionRs;

    // Right-click Menu
    QMenu* graphMenu;
    QCPGraph* selectedGraph = nullptr;


    // Plot Setup
    void setupPlot();

    // Highlight Spinbox
    double thresholdRatio;
    double lastThresholdPercentage = 0.0;

    // Compare Table
    QTableWidget *tableWidget;

    //avg status
    bool avg;

    // Distance Ratio
    bool distanceRatiosCalculated = false;
    double maxDistanceRatio;
    double lastXValue = 0.0;
    double lastYValue = 0.0;
    QList<RecordedPoint> recordedPoints;
    double distanceRatio; // Distance Ratio for specific point
    QVector<double> distanceRatios;
    QVector<double> ratios;

    // Max-Min
    double minFrequencyLS;
    double maxFrequencyLS;
    double minFrequencyRS;
    double maxFrequencyRS;

    // Table Dialog
    QDialog *pointDialog = nullptr;

    //Database
    QSqlDatabase db;

    // Clear Everything
    void clearEverything();

    // Straight MAX-MIN Lines
    QCPItemStraightLine *lineMin;
    QCPItemStraightLine *lineMax;

    // Max-Min Range
    double maxRange;
    double minRange;

    // Lines
    int linecount=0;
    QList<QCPItemStraightLine*> lines;
    QPen linePen;

    // Selected Graph Functions
    QList<QCPGraph*> selectedGraphs;
    void handleGraphSelection();


    // Graph Color Function
    QList<QColor> generateColorPalette(int count);

    // Average Graph
    QVector<double> calculateAverageValues(bool useLsData, bool onlyVisibleGraphs);
    void addAverageGraph(const QVector<double>& averageValues, bool useLsData);

    // Converting
    QString convertLsValue(double rawValue);
    QString convertRsValue(double rawValue);
    QString convertFrequency(double rawFrequency);


    // Graphs
    void calculateDistanceRatios();

    // Line Edit
    void updateLineEdits(QString fre, QString value);

    // Point Table
    void updateRecordedPointsTable();

    //Datababse
    bool openDatabase();
    bool closeDatabase();
    void initializeDatabase();
    void createFrequencyRangeTable();
    bool checkAndSetInitialValues();




private slots:

    // LineEdit Graphname
    void updateGraphName();
    // Buttons
    void on_btn_start_plot_clicked();
    void on_btn_save_plot_clicked();
    void on_btn_clear_plot_clicked();
    void on_btn_load_plot_clicked();
    void on_btn_HighlightGraphs_clicked();
    void on_btn_avg_clicked();
    void on_btn_tablo_clicked();
    void on_btn_tablo_clear_clicked();
    void on_btn_export_avg_clicked();
    void on_btn_zoom_x_clicked();
    void on_btn_zoom_y_clicked();
    void on_btn_zoomout_x_clicked();
    void on_btn_zoomout_y_clicked();
    void on_btn_addValue_clicked();
    void on_btn_clearLine_clicked();


    // Tracer Functions
    void createChartTracer();
    int findNearestDataPoint(const QSharedPointer<QCPGraphDataContainer> data, double xValue);

    // Checkboxes
    void on_cbox_Tracer_clicked(bool checked);


    //Radio Buttons
    void on_radioButton_Rs_clicked();
    void on_radioButton_Ls_clicked();

    // Adding checkboxes for every graph in GRAPHMENU
    void onGraphVisibilityChanged(bool checked);


    //Point Table
    void compareFrequency(double targetFrequency);


    //Settings
    void on_actionsettings_triggered();


    // Close Event
    void closeEvent(QCloseEvent *event);

    // Tracer Show Point Value
    void on_tracerShowPointValue(QMouseEvent *event);

    // Legend Checkbox
    void on_cbox_legend_toggled(bool checked);

    // Plot Resize
    void onPlotDoubleClick(QMouseEvent *);

    // Right-click Menu
    void contextMenuRequest(const QPoint& pos);

    // ComboBoxes
    void on_comboBox_tracer_currentTextChanged();
    void on_combobox_line_color_currentIndexChanged(int index);

    // CheckBoxes
    void on_cbox_r_zoom_clicked(bool checked);
    void on_cbox_Lines_clicked(bool checked);

    // Graph Visibility
    void hideSelectedGraph();
    void hideUnselectedGraphs();


};
#endif // MAINWINDOW_H
