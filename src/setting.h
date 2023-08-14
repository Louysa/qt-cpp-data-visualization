#ifndef SETTING_H
#define SETTING_H

#include "qlineedit.h"
#include <QDialog>

namespace Ui {
class setting;
}

class setting : public QDialog
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr);
    ~setting();

    Ui::setting *ui;

    double getMinFrequencyLS() const;
    double getMaxFrequencyLS() const;    
    double getMinFrequencyRS() const;    
    double getMaxFrequencyRS() const;


    QLineEdit *ledit_minLs;
    QLineEdit *ledit_maxLs;
    QLineEdit *ledit_minRs;
    QLineEdit *ledit_maxRs;

private slots:
    void on_btn_send_clicked();
private:
    double minFrequencyLS;
    double maxFrequencyLS;
    double minFrequencyRS;
    double maxFrequencyRS;


    double newMinFrequencyLS;
    double newMaxFrequencyLS;
    double newMinFrequencyRS;
    double newNaxFrequencyRS;

};

#endif // SETTING_H
