#ifndef DIALOG_SPONIP_H
#define DIALOG_SPONIP_H

#include <QDialog>

namespace Ui {
class Dialog_SpoNip;
}

class Dialog_SpoNip : public QDialog
{
    Q_OBJECT


private:
    bool    toggle_D_SpoNip;
    bool    isLeft;
    QRect   d_Position;


public:
    explicit Dialog_SpoNip(QWidget *parent = 0);
    ~Dialog_SpoNip();

    void    setSpokeParametersL(float thread , float length , float weight , float pieces , QString label);
    QString getSpokeLabelL();
    float   getSpokeThreadL_box(void);
    float   getSpokeLenghtL_box(void);
    float   getSpokeWeightL_box(void);
    float   getSpokePiecesL_box(void);

    void    setSpokeParametersR(float thread , float length , float weight , float pieces , QString label);
    QString getSpokeLabelR();
    float   getSpokeThreadR_box(void);
    float   getSpokeLenghtR_box(void);
    float   getSpokeWeightR_box(void);
    float   getSpokePiecesR_box(void);

    void    setNippleParametersL(float thread , float length , float weight , float pieces , QString label);
    QString getNippleLabelL();
    float   getNippleThreadL_box(void);
    float   getNippleLenghtL_box(void);
    float   getNippleWeightL_box(void);
    float   getNipplePiecesL_box(void);

    void    setNippleParametersR(float thread , float length , float weight , float pieces , QString label);
    QString getNippleLabelR();
    float   getNippleThreadR_box(void);
    float   getNippleLenghtR_box(void);
    float   getNippleWeightR_box(void);
    float   getNipplePiecesR_box(void);

    void    setToggle_D_SpoNip();


private slots:
    void    on_tableView_Spo_clicked(const QModelIndex &index);
    void    on_pushButton_spoDel_clicked();
    void    on_pushButton_spoAdd_clicked();
    void    on_pushButton_spoSave_clicked();

    void    on_doubleSpinBox_spokeThreadL_valueChanged(double arg1);
    void    on_doubleSpinBox_spokeLengthL_valueChanged(double arg1);
    void    on_doubleSpinBox_spokeWeightL_valueChanged(double arg1);
    void    on_doubleSpinBox_spokePiecesL_valueChanged(double arg1);
    void    on_lineEdit_spokeL_returnPressed();

    void    on_doubleSpinBox_spokeThreadR_valueChanged(double arg1);
    void    on_doubleSpinBox_spokeLengthR_valueChanged(double arg1);
    void    on_doubleSpinBox_spokeWeightR_valueChanged(double arg1);
    void    on_doubleSpinBox_spokePiecesR_valueChanged(double arg1);
    void    on_lineEdit_spokeR_returnPressed();

    void    on_tableView_Nip_clicked(const QModelIndex &index);
    void    on_pushButton_nipAdd_clicked();
    void    on_pushButton_nipDel_clicked();
    void    on_pushButton_nipSave_clicked();

    void    on_doubleSpinBox_nippleThreadL_valueChanged(double arg1);
    void    on_doubleSpinBox_nippleLengthL_valueChanged(double arg1);
    void    on_doubleSpinBox_nippleWeightL_valueChanged(double arg1);
    void    on_doubleSpinBox_nipplePiecesL_valueChanged(double arg1);
    void    on_lineEdit_nippleL_returnPressed();

    void    on_doubleSpinBox_nippleThreadR_valueChanged(double arg1);
    void    on_doubleSpinBox_nippleLengthR_valueChanged(double arg1);
    void    on_doubleSpinBox_nippleWeightR_valueChanged(double arg1);
    void    on_doubleSpinBox_nipplePiecesR_valueChanged(double arg1);
    void    on_lineEdit_nippleR_returnPressed();

    void    on_groupBox_SpoL_toggled(bool arg1);
    void    on_groupBox_SpoR_toggled(bool arg1);
    void    on_groupBox_NipL_toggled(bool arg1);
    void    on_groupBox_NipR_toggled(bool arg1);

    void    on_changedSpoNipParameters(bool isFromStart);


signals:
    void    changedParameters (bool isFromStart);
    void    changedSpoNipParameters (bool isFromStart);


private:
    Ui::Dialog_SpoNip *ui;

    bool    eventFilter(QObject *obj, QEvent *event) override;


protected:
    void    closeEvent(QCloseEvent *event);
};

#endif // DIALOG_SPONIP_H
