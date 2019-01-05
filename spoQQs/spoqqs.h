#ifndef SPOQQS_H
#define SPOQQS_H

#include <hole.h>
#include <nipple.h>
#include <spoke.h>
#include <spokes.h>
#include <flange.h>
#include <hub.h>
#include <rim.h>
#include <pattern.h>
#include <nipple.h>
#include <wheel.h>

#include <dialog_rimhub.h>
#include <dialog_sponip.h>
#include <dialog_results.h>
#include <dialog_graph.h>
#include <dialog_about.h>

#include <QObject>
#include <QDebug>
#include <QtCore>
#include <QMainWindow>
#include <QString>


namespace Ui {
class spoQQs;
}

class spoQQs : public QMainWindow , public wheel::Wheel
{
    Q_OBJECT


private:
    QImage             *wheelAxialImg;
    QImage             *wheelRadialImg;
    QStandardItemModel  *modelOut;
    int                 counter;
    float               rimRotation;

    QString             hubFR;
    QString             hubCogs;
    QString             hubNote;

    QString             rimSize;
    float               rimISO;
    QString             rimNote;

    float               nipplesThreadL;
    float               nipplesThreadR;


public:
    explicit spoQQs(QWidget *parent = 0);
    ~spoQQs();

    QStandardItemModel  *resultsOut(QStandardItemModel* modelS);
    void                traceWheel(void);
    void                setBoxesValues(void);


public slots:
    void    loadDefaults(QString file);
    void    loadNewWheel(QString file);
    void    saveDefaults(QString file);
    void    wheelBuild(bool isFromStart);


private slots:
    void    on_Button_RimHub_clicked();
    void    on_Button_SpoNip_clicked();
    void    on_Button_Results_clicked();
    void    on_Button_Graph_clicked();
    void    on_Button_Defaults_clicked();
    void    on_Button_About_clicked();

    void    on_checkBox_tiltAuto_clicked();
    void    on_doubleSpinBox_flangesTilt_valueChanged(double arg1);

    void    on_spinBox_hubHolesL_valueChanged(int arg1);
    void    on_comboBox_flangeTypeL_currentIndexChanged(int index);
    void    on_spinBox_spokesPerBlockL_valueChanged(int arg1);
    void    on_spinBox_pattL_1_valueChanged(int arg1);
    void    on_spinBox_pattL_2_valueChanged(int arg1);
    void    on_spinBox_pattL_3_valueChanged(int arg1);
    void    on_spinBox_pattL_4_valueChanged(int arg1);
    void    on_spinBox_pattL_5_valueChanged(int arg1);
    void    on_spinBox_pattL_6_valueChanged(int arg1);

    void    on_comboBox_flangeTypeR_currentIndexChanged(int index);
    void    on_checkBox_alternativeLacing_clicked();
    void    on_spinBox_spokesPerBlockR_valueChanged(int arg1);
    void    on_spinBox_pattR_1_valueChanged(int arg1);
    void    on_spinBox_pattR_2_valueChanged(int arg1);
    void    on_spinBox_pattR_3_valueChanged(int arg1);
    void    on_spinBox_pattR_4_valueChanged(int arg1);
    void    on_spinBox_pattR_5_valueChanged(int arg1);
    void    on_spinBox_pattR_6_valueChanged(int arg1);

    void    on_checkBox_isFront_clicked();
    void    on_spinBox_rimHoles_valueChanged(int arg1);
    void    on_checkBox_grouped_clicked();
    void    on_checkBox_groupedAuto_clicked();
    void    on_spinBox_spokesPerGroupMan_valueChanged(int arg1);
    void    on_doubleSpinBox_groupedHolesDistance_valueChanged(double arg1);
    void    on_spinBox_spokesPerGroupShift_valueChanged(int arg1);
    void    on_checkBox_swapped_clicked();
    void    on_doubleSpinBox_rimRotation_valueChanged(double arg1);


signals:
    void    changedParameters (bool isFromStart);


private:
    Ui::spoQQs          *ui;

    Dialog_RimHub       *D_RimHub;
    Dialog_SpoNip       *D_SpoNip;
    Dialog_Results      *D_Results;
    Dialog_Graph        *D_Graph;
    Dialog_About        *D_About;

    void    setMainWindowParameters  (bool front , int holes , int holesL, float rotation  ,
                                      int SpBlockL , int schemeL1 , int schemeL2 , int schemeL3 , int schemeL4 , int schemeL5 , int schemeL6 ,
                                      int SpBlockR , int schemeR1 , int schemeR2 , int schemeR3 , int schemeR4 , int schemeR5 , int schemeR6 ,
                                      bool isTiltAuto , float flangesTilt , float flangesTiltAuto ,
                                      bool isStraightpullL , bool isPairedL , bool isRadialStraightpullL ,
                                      bool isStraightpullR , bool isPairedR , bool isRadialStraightpullR , bool isAlternativeCoupled,
                                      bool isGrouped , bool isGroupedAuto , bool isSwapped , int holesPerGroupMan , int holesPerGroupAuto , int holesPerGroupShift , float groupedHolesDistance);

    bool    eventFilter(QObject *obj, QEvent *event) override;
};

#endif // SPOQQS_H
