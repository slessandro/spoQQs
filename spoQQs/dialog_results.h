#ifndef DIALOG_RESULTS_H
#define DIALOG_RESULTS_H

#include <QStandardItemModel>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QDialog>
#include <QTextDocument>

namespace Ui {
class Dialog_Results;
}

class Dialog_Results : public QDialog
{
    Q_OBJECT


private:
    bool            toggle_D_Results;
    float           density;
    float           resolutionPrint;
    float           resolutionScale;
    QRect           d_Position;

    QPrinter        *printer;
    QTextDocument   doc;
    QImage          *imageAxial;
    QImage          *imageRadial;

    QString         labelHub;
    QString         labelRim;
    QString         labelSpL;
    QString         labelSpR;
    QString         labelNiL;
    QString         labelNiR;


public:
    explicit Dialog_Results(QWidget *parent = 0);
    ~Dialog_Results();

    void    setResultsParameters (float thickness , float load , float young , float specificVolume , bool isAlternatingL , bool isAlternatingR , bool isHOutL , bool isHOutR , bool isSPullL , bool isSPullR, float meanAngleL, float meanAngleR, float meanForceL, float meanForceR, float meanElongationL, float meanElongationR, float weightHub, float weightRim, float weightSpokes, float weightNipples);
    float   getThickess_box();
    float   getLoad_box();
    float   getYoung_box();
    float   getSpecificVolume();
    int     getHeadsL();
    int     getHeadsR();

    void    setTable(QStandardItemModel* model);
    void    setDocLabels(QString hublabel,QString rimlabel,QString spokeslabelL,QString spokeslabelR,QString nippleslabelL,QString nippleslabelR);
    void    setDocImg(QImage *imgAxial, QImage *imgRadial);
    void    setToggle_D_Results();


signals:
    void    changedParameters (bool isFromStart);
    void    imageRequest(void);
    void    loadWheel (QString file);
    void    saveWheel (QString file);


private:
    Ui::Dialog_Results *ui;

    bool    eventFilter(QObject *obj, QEvent *event) override;


protected:
    void    closeEvent(QCloseEvent *event);

public slots:
    void    PreviewPaintRequested(QPrinter*printerP);


private slots:
    void    on_doubleSpinBox_flangeThickness_valueChanged(double arg1);
    void    on_doubleSpinBox_load_valueChanged(double arg1);
    void    on_doubleSpinBox_young_valueChanged(double arg1);
    void    on_doubleSpinBox_density_valueChanged(double arg1);
    void    on_comboBox_spokeHeadsL_currentIndexChanged(int index);
    void    on_comboBox_spokeHeadsR_currentIndexChanged(int index);
    void    on_Button_loadWheel_clicked();
    void    on_Button_saveWheel_clicked();
    void    on_Button_Print_clicked();
};

#endif // DIALOG_RESULTS_H

