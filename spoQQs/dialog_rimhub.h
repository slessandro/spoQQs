#ifndef DIALOG_RIMHUB_H
#define DIALOG_RIMHUB_H

#include <QDialog>

namespace Ui {
class Dialog_RimHub;
}

class Dialog_RimHub : public QDialog
{
    Q_OBJECT


private:
    bool    toggle_D_RimHub;
    QRect   d_Position;


public:
    explicit Dialog_RimHub(QWidget *parent = 0);
    ~Dialog_RimHub();

    void    setRimParameters (float erd , float osb , float bed, float weight , QString label, QString size, float iso, QString note);
    QString getRimLabel();
    float   getERD_box(void);
    float   getOSB_box(void);
    float   getBed_box(void);
    float   getWeightRim_box(void);
    QString getRimSize();
    float   getISO_box();
    QString getRimNote();

    void    setHubParameters(float hL , float dL , float wL , float oL ,
                             float hR , float dR , float wR , float oR ,
                             float old, float weight, QString label, QString fr, QString cogs, QString note);
    QString getHubLabel();
    float   getHL_box();
    float   getOL_box();
    float   getDL_box();
    float   getWL_box();
    float   getHR_box();
    float   getOR_box();
    float   getDR_box();
    float   getWR_box();
    float   getOld_box();
    float   getWeightHub_box();
    QString getFR();
    QString getCogs();
    QString getHubNote();

    void    setToggle_D_RimHub();


private slots:
    void    on_tableView_Rim_clicked(const QModelIndex &index);
    void    on_pushButton_rimAdd_clicked();
    void    on_pushButton_rimDel_clicked();
    void    on_pushButton_rimSave_clicked();

    void    on_lineEdit_rimSize_returnPressed();
    void    on_lineEdit_rim_returnPressed();
    void    on_lineEdit_rimNote_returnPressed();
    void    on_doubleSpinBox_ERD_valueChanged(double arg1);
    void    on_doubleSpinBox_OSB_valueChanged(double arg1);
    void    on_doubleSpinBox_Bed_valueChanged(double arg1);
    void    on_doubleSpinBox_ISO_valueChanged(double arg1);
    void    on_doubleSpinBox_WeightRim_valueChanged(double arg1);

    void    on_tableView_Hub_clicked(const QModelIndex &index);
    void    on_pushButton_hubAdd_clicked();
    void    on_pushButton_hubDel_clicked();
    void    on_pushButton_hubSave_clicked();

    void    on_lineEdit_FR_returnPressed();
    void    on_lineEdit_cogs_returnPressed();
    void    on_lineEdit_hub_returnPressed();
    void    on_lineEdit_hubNote_returnPressed();
    void    on_doubleSpinBox_hL_valueChanged(double arg1);
    void    on_doubleSpinBox_dL_valueChanged(double arg1);
    void    on_doubleSpinBox_wL_valueChanged(double arg1);
    void    on_doubleSpinBox_oL_valueChanged(double arg1);
    void    on_doubleSpinBox_hR_valueChanged(double arg1);
    void    on_doubleSpinBox_dR_valueChanged(double arg1);
    void    on_doubleSpinBox_wR_valueChanged(double arg1);
    void    on_doubleSpinBox_oR_valueChanged(double arg1);
    void    on_doubleSpinBox_OLD_valueChanged(double arg1);
    void    on_doubleSpinBox_weightHub_valueChanged(double arg1);

    void    on_changedRimHubParameters(bool isFromStart);


signals:
    void    changedParameters (bool isFromStart);
    void    changedRimHubParameters (bool isFromStart);


private:
    Ui::Dialog_RimHub *ui;

    bool    eventFilter(QObject *obj, QEvent *event) override;

protected:
    void    closeEvent(QCloseEvent *event);
};

#endif // DIALOG_RIMHUB_H
