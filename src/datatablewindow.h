// DataTableWindow.h
#ifndef DATATABLEWINDOW_H
#define DATATABLEWINDOW_H

#include <QDialog>

namespace Ui {
class DataTableWindow;
}

class DataTableWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DataTableWindow(QWidget *parent = nullptr);
    ~DataTableWindow();

private:
    Ui::DataTableWindow *ui;
};

#endif // DATATABLEWINDOW_H
