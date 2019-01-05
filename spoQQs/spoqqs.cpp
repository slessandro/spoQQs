#include <spoqqs.h>
#include <ui_spoqqs.h>

#include <QDebug>





spoQQs::spoQQs(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::spoQQs)
{
    ui->setupUi(this);

    ui->spinBox_rimHoles->installEventFilter(this);
    ui->spinBox_spokesPerGroupMan->installEventFilter(this);
    ui->doubleSpinBox_groupedHolesDistance->installEventFilter(this);
    ui->spinBox_spokesPerGroupShift->installEventFilter(this);
    ui->doubleSpinBox_rimRotation->installEventFilter(this);
    ui->doubleSpinBox_flangesTilt->installEventFilter(this);
    ui->spinBox_hubHolesL->installEventFilter(this);
    ui->spinBox_spokesPerBlockL->installEventFilter(this);
    ui->spinBox_pattL_1->installEventFilter(this);
    ui->spinBox_pattL_2->installEventFilter(this);
    ui->spinBox_pattL_3->installEventFilter(this);
    ui->spinBox_pattL_4->installEventFilter(this);
    ui->spinBox_pattL_5->installEventFilter(this);
    ui->spinBox_pattL_6->installEventFilter(this);
    ui->spinBox_spokesPerBlockR->installEventFilter(this);
    ui->spinBox_pattR_1->installEventFilter(this);
    ui->spinBox_pattR_2->installEventFilter(this);
    ui->spinBox_pattR_3->installEventFilter(this);
    ui->spinBox_pattR_4->installEventFilter(this);
    ui->spinBox_pattR_5->installEventFilter(this);
    ui->spinBox_pattR_6->installEventFilter(this);

    D_RimHub = new Dialog_RimHub(this);
    D_SpoNip = new Dialog_SpoNip(this);
    D_Results = new Dialog_Results(this);
    D_Graph = new Dialog_Graph(this);
    D_About = new Dialog_About(this);

    modelOut = new QStandardItemModel;
    counter = 0;
    rimRotation = 0.0;

    wheelAxialImg  = D_Graph->getWheelAxial();
    wheelRadialImg = D_Graph->getWheelRadial();
    D_Results->setDocImg(wheelAxialImg,wheelRadialImg);

    input_ = "spoQQs.defaults";
    loadDefaults(QString::fromStdString(input_));
    assessWheel(true,0.0);
    calcMeanValues();
    setBoxesValues();
    D_Results->setTable(resultsOut(modelOut));
    traceWheel();
    D_Results->setDocLabels(QString::fromStdString(hub.label),QString::fromStdString(rim.label),
                            QString::fromStdString(spokes.labelL),QString::fromStdString(spokes.labelR),
                            QString::fromStdString(nipples.labelL),QString::fromStdString(nipples.labelR));

    counter++;
    qDebug() << "counter " << counter;

    QObject::connect(this    , SIGNAL(changedParameters(bool)),this,SLOT(wheelBuild(bool)));
    QObject::connect(D_RimHub, SIGNAL(changedParameters(bool)),this,SLOT(wheelBuild(bool)));
    QObject::connect(D_SpoNip, SIGNAL(changedParameters(bool)),this,SLOT(wheelBuild(bool)));
    QObject::connect(D_Results,SIGNAL(changedParameters(bool)),this,SLOT(wheelBuild(bool)));
    QObject::connect(D_Results,SIGNAL(imageRequest(void)),D_Graph,SLOT(imageCalculate(void)));
    QObject::connect(D_Results,SIGNAL(loadWheel(QString)),this,SLOT(loadNewWheel(QString)));
    QObject::connect(D_Results,SIGNAL(saveWheel(QString)),this,SLOT(saveDefaults(QString)));
}





spoQQs::~spoQQs()
{
    delete ui;
}





void spoQQs::on_Button_RimHub_clicked()
{
    D_RimHub->setToggle_D_RimHub();
}





void spoQQs::on_Button_SpoNip_clicked()
{
    D_SpoNip->setToggle_D_SpoNip();
}





void spoQQs::on_Button_Results_clicked()
{
    D_Results->setToggle_D_Results();
}





void spoQQs::on_Button_Graph_clicked()
{
    D_Graph->setToggle_D_Graph();
}





void spoQQs::on_Button_Defaults_clicked()
{
    saveDefaults(QString::fromStdString(input_));
}





void spoQQs::on_Button_About_clicked()
{
    D_About->setToggle_D_About();
}





void spoQQs::wheelBuild(bool isFromStart)
{
    float   pi = 3.1415927;


    isFront                   = ui->checkBox_isFront->isChecked();
    hub.isFront               = isFront;
    rim.isFront               = isFront;
    iHoles                    = ui->spinBox_rimHoles->value();
    iHolesL                   = ui->spinBox_hubHolesL->value();

    rimRotation               = ui->doubleSpinBox_rimRotation->value()*(pi/180.0);

    blockL                    = ui->spinBox_spokesPerBlockL->value();
    schemeL[0]                = ui->spinBox_pattL_1->value();
    schemeL[1]                = ui->spinBox_pattL_2->value();
    schemeL[2]                = ui->spinBox_pattL_3->value();
    schemeL[3]                = ui->spinBox_pattL_4->value();
    schemeL[4]                = ui->spinBox_pattL_5->value();
    schemeL[5]                = ui->spinBox_pattL_6->value();

    blockR                    = ui->spinBox_spokesPerBlockR->value();
    schemeR[0]                = ui->spinBox_pattR_1->value();
    schemeR[1]                = ui->spinBox_pattR_2->value();
    schemeR[2]                = ui->spinBox_pattR_3->value();
    schemeR[3]                = ui->spinBox_pattR_4->value();
    schemeR[4]                = ui->spinBox_pattR_5->value();
    schemeR[5]                = ui->spinBox_pattR_6->value();

    hub.isTiltAuto            = ui->checkBox_tiltAuto->isChecked();
    hub.flangesTilt           = ui->doubleSpinBox_flangesTilt->value()*(pi/180.0);
    switch (ui->comboBox_flangeTypeL->currentIndex())
        {
        case (0):
            {
            hub.isStraightpullL         = false;
            hub.isRadialStraightpullL   = false;
            hub.isPairedL               = false;
            }
        break;
        case (1):
            {
            hub.isStraightpullL         = true;
            hub.isRadialStraightpullL   = false;
            hub.isPairedL               = false;
            }
        break;
        case (2):
            {
            hub.isStraightpullL         = true;
            hub.isRadialStraightpullL   = true;
            hub.isPairedL               = false;
            }
        break;
        case (3):
            {
            hub.isStraightpullL         = false;
            hub.isRadialStraightpullL   = false;
            hub.isPairedL               = true;
            }
        break;
        }
    switch (ui->comboBox_flangeTypeR->currentIndex())
        {
        case (0):
            {
            hub.isStraightpullR         = false;
            hub.isRadialStraightpullR   = false;
            hub.isPairedR               = false;
            }
        break;
        case (1):
            {
            hub.isStraightpullR         = true;
            hub.isRadialStraightpullR   = false;
            hub.isPairedR               = false;
            }
        break;
        case (2):
            {
            hub.isStraightpullR         = true;
            hub.isRadialStraightpullR   = true;
            hub.isPairedR               = false;
            }
        break;
        case (3):
            {
            hub.isStraightpullR         = false;
            hub.isRadialStraightpullR   = false;
            hub.isPairedR               = true;
            }
        break;
        }
    hub.isAlternativeCoupled  = ui->checkBox_alternativeLacing->isChecked();

    rim.isGrouped             = ui->checkBox_grouped->isChecked();
    rim.isGroupedAuto         = ui->checkBox_groupedAuto->isChecked();
    rim.isSwapped             = ui->checkBox_swapped->isChecked();
    rim.holesPerGroupMan      = ui->spinBox_spokesPerGroupMan->value();
    rim.holesPerGroupShift    = ui->spinBox_spokesPerGroupShift->value();
    rim.groupedHolesDistance  = ui->doubleSpinBox_groupedHolesDistance->value();

    rim.label                 = D_RimHub->getRimLabel().toStdString();
    rim.erd                   = D_RimHub->getERD_box();
    rim.osb                   = D_RimHub->getOSB_box();
    rim.spokeBedDistance      = D_RimHub->getBed_box();
    rim.weight                = D_RimHub->getWeightRim_box();
    rimSize                   = D_RimHub->getRimSize();
    rimISO                    = D_RimHub->getISO_box();
    rimNote                   = D_RimHub->getRimNote();
                             
    hub.label                 = D_RimHub->getHubLabel().toStdString();
    hub.holesDiameterL        = D_RimHub->getHL_box();
    hub.flangeDiameterL       = D_RimHub->getDL_box();
    hub.widthL                = D_RimHub->getWL_box();
    hub.holesOffsetL          = D_RimHub->getOL_box();
    hub.holesDiameterR        = D_RimHub->getHR_box();
    hub.flangeDiameterR       = D_RimHub->getDR_box();
    hub.widthR                = D_RimHub->getWR_box();
    hub.holesOffsetR          = D_RimHub->getOR_box();
    hub.old                   = D_RimHub->getOld_box();
    hub.weight                = D_RimHub->getWeightHub_box();
    hubFR                     = D_RimHub->getFR();
    hubCogs                   = D_RimHub->getCogs();
    hubNote                   = D_RimHub->getHubNote();
                             
    spokes.threadDiameterL    = D_SpoNip->getSpokeThreadL_box();
    spokes.packLengthL        = D_SpoNip->getSpokeLenghtL_box();
    spokes.packWeightL        = D_SpoNip->getSpokeWeightL_box();
    spokes.packPcsL           = D_SpoNip->getSpokePiecesL_box();
    spokes.labelL             = D_SpoNip->getSpokeLabelL().toStdString();
                             
    spokes.threadDiameterR    = D_SpoNip->getSpokeThreadR_box();
    spokes.packLengthR        = D_SpoNip->getSpokeLenghtR_box();
    spokes.packWeightR        = D_SpoNip->getSpokeWeightR_box();
    spokes.packPcsR           = D_SpoNip->getSpokePiecesR_box();
    spokes.labelR             = D_SpoNip->getSpokeLabelR().toStdString();
                             
    nipplesThreadL            = D_SpoNip->getNippleThreadL_box();
    nipples.packLengthL       = D_SpoNip->getNippleLenghtL_box();
    nipples.packWeightL       = D_SpoNip->getNippleWeightL_box();
    nipples.packPcsL          = D_SpoNip->getNipplePiecesL_box();
    nipples.labelL            = D_SpoNip->getNippleLabelL().toStdString();
                             
    nipplesThreadR            = D_SpoNip->getNippleThreadR_box();
    nipples.packLengthR       = D_SpoNip->getNippleLenghtR_box();
    nipples.packWeightR       = D_SpoNip->getNippleWeightR_box();
    nipples.packPcsR          = D_SpoNip->getNipplePiecesR_box();
    nipples.labelR            = D_SpoNip->getNippleLabelR().toStdString();

    hub.flangeThickness       = D_Results->getThickess_box();
    spokes.forceNominal       = D_Results->getLoad_box();
    spokes.youngModulus       = D_Results->getYoung_box();
    spokes.specificVolume     = D_Results->getSpecificVolume();
    switch (D_Results->getHeadsL())
        {
        case (0):
            {
            hub.isHeadsAlternatingL = true;
            hub.isHeadsoutL         = false;
            }
        break;
        case (1):
            {
            hub.isHeadsAlternatingL = false;
            hub.isHeadsoutL         = true;
            }
        break;
        case (2):
            {
            hub.isHeadsAlternatingL = false;
            hub.isHeadsoutL         = false;
            }
        break;
        }
    switch (D_Results->getHeadsR())
        {
        case (0):
            {
            hub.isHeadsAlternatingR = true;
            hub.isHeadsoutR         = false;
            }
        break;
        case (1):
            {
            hub.isHeadsAlternatingR = false;
            hub.isHeadsoutR         = true;
            }
        break;
        case (2):
            {
            hub.isHeadsAlternatingR = false;
            hub.isHeadsoutR         = false;
            }
        break;
        }

    assessWheel(isFromStart,rimRotation);
    calcMeanValues();
    setBoxesValues();
    resultsOut(modelOut);
    traceWheel();
    D_Results->setDocLabels(QString::fromStdString(hub.label),QString::fromStdString(rim.label),
                            QString::fromStdString(spokes.labelL),QString::fromStdString(spokes.labelR),
                            QString::fromStdString(nipples.labelL),QString::fromStdString(nipples.labelR));

    counter++;
    qDebug() << "counter " << counter;
}





void spoQQs::setBoxesValues(void)
{
    setMainWindowParameters        (isFront,
                                    iHoles,
                                    iHolesL,
                                    rimRotation,
                                    blockL,
                                    schemeL[0],
                                    schemeL[1],
                                    schemeL[2],
                                    schemeL[3],
                                    schemeL[4],
                                    schemeL[5],
                                    blockR,
                                    schemeR[0],
                                    schemeR[1],
                                    schemeR[2],
                                    schemeR[3],
                                    schemeR[4],
                                    schemeR[5],
                                    hub.isTiltAuto,
                                    hub.flangesTilt,
                                    hub.flangesTiltAuto,
                                    hub.isStraightpullL,
                                    hub.isPairedL,
                                    hub.isRadialStraightpullL,
                                    hub.isStraightpullR,
                                    hub.isPairedR,
                                    hub.isRadialStraightpullR,
                                    hub.isAlternativeCoupled,
                                    rim.isGrouped,
                                    rim.isGroupedAuto,
                                    rim.isSwapped,
                                    rim.holesPerGroupMan,
                                    rim.holesPerGroupAuto,
                                    rim.holesPerGroupShift,
                                    rim.groupedHolesDistance);
    D_RimHub->setRimParameters     (rim.erd,
                                    rim.osb,
                                    rim.spokeBedDistance,
                                    rim.weight,
                                    QString::fromStdString(rim.label),
                                    rimSize,
                                    rimISO,
                                    rimNote);
    D_RimHub->setHubParameters     (hub.holesDiameterL,
                                    hub.flangeDiameterL,
                                    hub.widthL,
                                    hub.holesOffsetL,
                                    hub.holesDiameterR,
                                    hub.flangeDiameterR,
                                    hub.widthR,
                                    hub.holesOffsetR,
                                    hub.old,
                                    hub.weight,
                                    QString::fromStdString(hub.label),
                                    hubFR,
                                    hubCogs,
                                    hubNote);
    D_SpoNip->setSpokeParametersL  (spokes.threadDiameterL,
                                    spokes.packLengthL,
                                    spokes.packWeightL,
                                    spokes.packPcsL,
                                    QString::fromStdString(spokes.labelL));
    D_SpoNip->setSpokeParametersR  (spokes.threadDiameterR,
                                    spokes.packLengthR,
                                    spokes.packWeightR,
                                    spokes.packPcsR,
                                    QString::fromStdString(spokes.labelR));
    D_SpoNip->setNippleParametersL (nipplesThreadL,
                                    nipples.packLengthL,
                                    nipples.packWeightL,
                                    nipples.packPcsL,
                                    QString::fromStdString(nipples.labelL));
    D_SpoNip->setNippleParametersR (nipplesThreadR,
                                    nipples.packLengthR,
                                    nipples.packWeightR,
                                    nipples.packPcsR,
                                    QString::fromStdString(nipples.labelR));
    D_Results->setResultsParameters(hub.flangeThickness,
                                    spokes.forceNominal,
                                    spokes.youngModulus,
                                    spokes.specificVolume,
                                    hub.isHeadsAlternatingL,
                                    hub.isHeadsAlternatingR,
                                    hub.isHeadsoutL,
                                    hub.isHeadsoutR,
                                    hub.isStraightpullL,
                                    hub.isStraightpullR,
                                    meanAngleL_,
                                    meanAngleR_,
                                    meanForceL_,
                                    meanForceR_,
                                    meanElongationL_,
                                    meanElongationR_,
                                    hub.weight,
                                    rim.weight,
                                    weightSpokes_,
                                    weightNipples_);
}





void spoQQs::loadDefaults(QString file)
{

    QStringList defaultData;

    defaultData.clear();
    QFile filedefaults(file);
    if (filedefaults.open(QIODevice::ReadOnly))
        {
        int lineindex = 0;
        QTextStream in(&filedefaults);
        while (!in.atEnd())
            {
            QString fileLine = in.readLine();
            QStringList lineToken = fileLine.split(",", QString::KeepEmptyParts);
            for (int j = 0; j < lineToken.size(); j++)
                {
                defaultData << lineToken.at(j);
                }
            lineindex++;
            }
        filedefaults.close();
        }

    if (defaultData.size() != 94) return;

    isFront                   = defaultData.at(0).toFloat();
    iHoles                    = defaultData.at(1).toFloat();
    iHolesL                   = defaultData.at(2).toFloat();
    iHolesR                   = defaultData.at(3).toFloat();

    blockL                    = defaultData.at(4).toFloat();
    schemeL[0]                = defaultData.at(5).toFloat();
    schemeL[1]                = defaultData.at(6).toFloat();
    schemeL[2]                = defaultData.at(7).toFloat();
    schemeL[3]                = defaultData.at(8).toFloat();
    schemeL[4]                = defaultData.at(9).toFloat();
    schemeL[5]                = defaultData.at(10).toFloat();
    schemeL[6]                = defaultData.at(11).toFloat();
    schemeL[7]                = defaultData.at(12).toFloat();
    schemeL[8]                = defaultData.at(13).toFloat();
    schemeL[9]                = defaultData.at(14).toFloat();

    blockR                    = defaultData.at(15).toFloat();
    schemeR[0]                = defaultData.at(16).toFloat();
    schemeR[1]                = defaultData.at(17).toFloat();
    schemeR[2]                = defaultData.at(18).toFloat();
    schemeR[3]                = defaultData.at(19).toFloat();
    schemeR[4]                = defaultData.at(20).toFloat();
    schemeR[5]                = defaultData.at(21).toFloat();
    schemeR[6]                = defaultData.at(22).toFloat();
    schemeR[7]                = defaultData.at(23).toFloat();
    schemeR[8]                = defaultData.at(24).toFloat();
    schemeR[9]                = defaultData.at(25).toFloat();


    hub.label                 = defaultData.at(26).toStdString();
    hub.isTiltAuto            = defaultData.at(27).toFloat();
    hub.flangesTilt           = defaultData.at(28).toFloat();
    hub.flangesTiltAuto       = defaultData.at(29).toFloat();

    hub.widthL                = defaultData.at(30).toFloat();
    hub.flangeDiameterL       = defaultData.at(31).toFloat();
    hub.holesDiameterL        = defaultData.at(32).toFloat();
    hub.holesOffsetL          = defaultData.at(33).toFloat();
    hub.isStraightpullL       = defaultData.at(34).toFloat();
    hub.isPairedL             = defaultData.at(35).toFloat();
    hub.isRadialStraightpullL = defaultData.at(36).toFloat();
    hub.isAlternativeCoupled  = defaultData.at(37).toFloat();
    hub.isHeadsAlternatingL   = defaultData.at(38).toFloat();
    hub.isHeadsoutL           = defaultData.at(39).toFloat();

    hub.widthR                = defaultData.at(40).toFloat();
    hub.flangeDiameterR       = defaultData.at(41).toFloat();
    hub.holesDiameterR        = defaultData.at(42).toFloat();
    hub.holesOffsetR          = defaultData.at(43).toFloat();
    hub.isStraightpullR       = defaultData.at(44).toFloat();
    hub.isPairedR             = defaultData.at(45).toFloat();
    hub.isRadialStraightpullR = defaultData.at(46).toFloat();
    hub.isAlternativeCoupled  = defaultData.at(47).toFloat();
    hub.isHeadsAlternatingR   = defaultData.at(48).toFloat();
    hub.isHeadsoutR           = defaultData.at(49).toFloat();

    hub.flangeThickness       = defaultData.at(50).toFloat();
    hub.old                   = defaultData.at(51).toFloat();
    hub.weight                = defaultData.at(52).toFloat();
    hubFR                     = defaultData.at(53);
    hubCogs                   = defaultData.at(54);
    hubNote                   = defaultData.at(55);


    rim.label                 = defaultData.at(56).toStdString();
    rim.isGrouped             = defaultData.at(57).toFloat();
    rim.isGroupedAuto         = defaultData.at(58).toFloat();
    rim.isSwapped             = defaultData.at(59).toFloat();
    rim.holesPerGroupMan      = defaultData.at(60).toFloat();
    rim.holesPerGroupAuto     = defaultData.at(61).toFloat();
    rim.holesPerGroupShift    = defaultData.at(62).toFloat();
    rim.erd                   = defaultData.at(63).toFloat();
    rim.osb                   = defaultData.at(64).toFloat();
    rim.groupedHolesDistance  = defaultData.at(65).toFloat();
    rim.spokeBedDistance      = defaultData.at(66).toFloat();
    rim.weight                = defaultData.at(67).toFloat();
    rimSize                   = defaultData.at(68);
    rimISO                    = defaultData.at(69).toFloat();
    rimNote                   = defaultData.at(70);


    spokes.youngModulus       = defaultData.at(71).toFloat();
    spokes.specificVolume     = defaultData.at(72).toFloat();
    spokes.forceNominal       = defaultData.at(73).toFloat();

    spokes.labelL             = defaultData.at(74).toStdString();
    spokes.threadDiameterL    = defaultData.at(75).toFloat();
    spokes.packWeightL        = defaultData.at(76).toFloat();
    spokes.packLengthL        = defaultData.at(77).toFloat();
    spokes.packPcsL           = defaultData.at(78).toFloat();

    spokes.labelR             = defaultData.at(79).toStdString();
    spokes.threadDiameterR    = defaultData.at(80).toFloat();
    spokes.packWeightR        = defaultData.at(81).toFloat();
    spokes.packLengthR        = defaultData.at(82).toFloat();
    spokes.packPcsR           = defaultData.at(83).toFloat();


    nipples.labelL            = defaultData.at(84).toStdString();
    nipplesThreadL            = defaultData.at(85).toFloat();
    nipples.packWeightL       = defaultData.at(86).toFloat();
    nipples.packLengthL       = defaultData.at(87).toFloat();
    nipples.packPcsL          = defaultData.at(88).toFloat();

    nipples.labelR            = defaultData.at(89).toStdString();
    nipplesThreadR            = defaultData.at(90).toFloat();
    nipples.packWeightR       = defaultData.at(91).toFloat();
    nipples.packLengthR       = defaultData.at(92).toFloat();
    nipples.packPcsR          = defaultData.at(93).toFloat();
}





void spoQQs::loadNewWheel(QString file)
{
    QObject::disconnect(this    , SIGNAL(changedParameters(bool)),this,SLOT(wheelBuild(bool)));
    QObject::disconnect(D_RimHub, SIGNAL(changedParameters(bool)),this,SLOT(wheelBuild(bool)));
    QObject::disconnect(D_SpoNip, SIGNAL(changedParameters(bool)),this,SLOT(wheelBuild(bool)));
    QObject::disconnect(D_Results,SIGNAL(changedParameters(bool)),this,SLOT(wheelBuild(bool)));

    loadDefaults(file);
    assessWheel(true,0.0);
    calcMeanValues();
    setBoxesValues();
    resultsOut(modelOut);
    traceWheel();
    D_Results->setDocLabels(QString::fromStdString(hub.label),QString::fromStdString(rim.label),
                            QString::fromStdString(spokes.labelL),QString::fromStdString(spokes.labelR),
                            QString::fromStdString(nipples.labelL),QString::fromStdString(nipples.labelR));
    D_Graph->fitGraph();

    QObject::connect(this    , SIGNAL(changedParameters(bool)),this,SLOT(wheelBuild(bool)));
    QObject::connect(D_RimHub, SIGNAL(changedParameters(bool)),this,SLOT(wheelBuild(bool)));
    QObject::connect(D_SpoNip, SIGNAL(changedParameters(bool)),this,SLOT(wheelBuild(bool)));
    QObject::connect(D_Results,SIGNAL(changedParameters(bool)),this,SLOT(wheelBuild(bool)));

    counter++;
    qDebug() << "counter " << counter;

}





void spoQQs::saveDefaults(QString file)
{
    QFile csvFile(file);
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
        QTextStream out(&csvFile);
        out
        << isFront                                << ","
        << iHoles                                 << ","
        << iHolesL                                << ","
        << iHolesR                                << "\n"
                                                  
        << blockL                                 << ","
        << schemeL[0]                             << ","
        << schemeL[1]                             << ","
        << schemeL[2]                             << ","
        << schemeL[3]                             << ","
        << schemeL[4]                             << ","
        << schemeL[5]                             << ","
        << schemeL[6]                             << ","
        << schemeL[7]                             << ","
        << schemeL[8]                             << ","
        << schemeL[9]                             << "\n"
                                                  
        << blockR                                 << ","
        << schemeR[0]                             << ","
        << schemeR[1]                             << ","
        << schemeR[2]                             << ","
        << schemeR[3]                             << ","
        << schemeR[4]                             << ","
        << schemeR[5]                             << ","
        << schemeR[6]                             << ","
        << schemeR[7]                             << ","
        << schemeR[8]                             << ","
        << schemeR[9]                             << "\n"
        
        
        
        << QString::fromStdString(hub.label)      << ","
        << hub.isTiltAuto                         << ","
        << hub.flangesTilt                        << ","
        << hub.flangesTiltAuto                    << "\n"
                                                  
        << hub.widthL                             << ","
        << hub.flangeDiameterL                    << ","
        << hub.holesDiameterL                     << ","
        << hub.holesOffsetL                       << ","
        << hub.isStraightpullL                    << ","
        << hub.isPairedL                          << ","
        << hub.isRadialStraightpullL              << ","
        << hub.isAlternativeCoupled               << ","
        << hub.isHeadsAlternatingL                << ","
        << hub.isHeadsoutL                        << "\n"
                                                  
        << hub.widthR                             << ","
        << hub.flangeDiameterR                    << ","
        << hub.holesDiameterR                     << ","
        << hub.holesOffsetR                       << ","
        << hub.isStraightpullR                    << ","
        << hub.isPairedR                          << ","
        << hub.isRadialStraightpullR              << ","
        << hub.isAlternativeCoupled               << ","
        << hub.isHeadsAlternatingR                << ","
        << hub.isHeadsoutR                        << "\n"
                                                  
        << hub.flangeThickness                    << ","
        << hub.old                                << ","
        << hub.weight                             << ","
        << hubFR                                  << ","
        << hubCogs                                << ","
        << hubNote                                << "\n"
        
        
        
        << QString::fromStdString(rim.label)      << ","
        << rim.isGrouped                          << ","
        << rim.isGroupedAuto                      << ","
        << rim.isSwapped                          << ","
        << rim.holesPerGroupMan                   << ","
        << rim.holesPerGroupAuto                  << ","
        << rim.holesPerGroupShift                 << ","
        << rim.erd                                << ","
        << rim.osb                                << ","
        << rim.groupedHolesDistance               << ","
        << rim.spokeBedDistance                   << ","
        << rim.weight                             << ","
        << rimSize                                << ","
        << rimISO                                 << ","
        << rimNote                                << "\n"
        
        
        
        << spokes.youngModulus                    << ","
        << spokes.specificVolume                  << ","
        << spokes.forceNominal                    << "\n"
        
        << QString::fromStdString(spokes.labelL)  << ","
        << spokes.threadDiameterL                 << ","
        << spokes.packWeightL                     << ","
        << spokes.packLengthL                     << ","
        << spokes.packPcsL                        << "\n"
        
        << QString::fromStdString(spokes.labelR)  << ","
        << spokes.threadDiameterR                 << ","
        << spokes.packWeightR                     << ","
        << spokes.packLengthR                     << ","
        << spokes.packPcsR                        << "\n"
        
        
        
        << QString::fromStdString(nipples.labelL) << ","
        << nipplesThreadL                         << ","
        << nipples.packWeightL                    << ","
        << nipples.packLengthL                    << ","
        << nipples.packPcsL                       << "\n"
                                                 
        << QString::fromStdString(nipples.labelR) << ","
        << nipplesThreadR                         << ","
        << nipples.packWeightR                    << ","
        << nipples.packLengthR                    << ","
        << nipples.packPcsR                       << "\n";
        csvFile.close();
        }
}





QStandardItemModel *spoQQs::resultsOut(QStandardItemModel *modelS)
{
    float                   pi = 3.1415927;
    float                   cent;
    QString                 lr;
    QStandardItem*          item;
    QList<QStandardItem *>  listItem;


    modelS->removeRows(0, modelS->rowCount());

    for (int i = 0 ; i < iHoles ; i++ )
        {
        (spokes.getSpoke(i).flange) ? lr = "R" : lr = "L";

        listItem.clear();

        item = new QStandardItem();
        item->setData(spokes.getSpoke(i).nHub, Qt::DisplayRole);
        listItem.append(item);

        item = new QStandardItem(lr);
        listItem.append(item);

        item = new QStandardItem();
        cent = round(spokes.getSpoke(i).angleHub*(180.0/pi)*100.0)/100.0;
        item->setData(cent, Qt::DisplayRole);
        listItem.append(item);

        item = new QStandardItem();
        item->setData(spokes.getSpoke(i).nRim, Qt::DisplayRole);
        listItem.append(item);

        item = new QStandardItem();
        cent = round(spokes.getSpoke(i).angleRim*(180.0/pi)*100.0)/100.0;
        item->setData(cent, Qt::DisplayRole);
        listItem.append(item);

        item = new QStandardItem();
        cent = round(spokes.getSpoke(i).getRealXcross()*100.0)/100.0;
        item->setData(cent, Qt::DisplayRole);
        listItem.append(item);

        item = new QStandardItem();
        cent = round(spokes.getSpoke(i).getLength()*100.0)/100.0;
        item->setData(cent, Qt::DisplayRole);
        listItem.append(item);

        item = new QStandardItem();
        cent = round(spokes.getSpoke(i).getBracingAngle()*100.0)/100.0;
        item->setData(cent, Qt::DisplayRole);
        listItem.append(item);

        item = new QStandardItem();
        cent = round(spokes.getSpoke(i).getRatio()*100.0)/100.0;
        item->setData(cent, Qt::DisplayRole);
        listItem.append(item);

        item = new QStandardItem();
        cent = round(spokes.getSpoke(i).getElongation()*100.0)/100.0;
        item->setData(cent, Qt::DisplayRole);
        listItem.append(item);

        modelS->appendRow(listItem);
        }

    modelS->setHeaderData(0,Qt::Horizontal, "Hub Hole");
    modelS->setHeaderData(1,Qt::Horizontal, "L/R");
    modelS->setHeaderData(2,Qt::Horizontal, "Angle");
    modelS->setHeaderData(3,Qt::Horizontal, "Rim Hole");
    modelS->setHeaderData(4,Qt::Horizontal, "Angle");
    modelS->setHeaderData(5,Qt::Horizontal, "Real Cross");
    modelS->setHeaderData(6,Qt::Horizontal, "Length");
    modelS->setHeaderData(7,Qt::Horizontal, "Bracing");
    modelS->setHeaderData(8,Qt::Horizontal, "Tension Ratio");
    modelS->setHeaderData(9,Qt::Horizontal, "Elongation");

    return modelS;
}





void spoQQs::traceWheel()
{
    wheel::Spoke    spoke;
    float           zLeft = 0;
    float           zRight = 0;

    D_Graph->clearGraph();

    for (int i = 0 ; i < iHoles ; i++ )
        {
        spoke = spokes.getSpoke(i);
        D_Graph->traceSpoke(spoke.flange,spoke.nHub,spoke.xHub,spoke.yHub,spoke.xRim,spoke.yRim,spoke.radialOffset,hub.isStraightpullL,hub.isStraightpullR);
        if ((spoke.flange == 0) && (spoke.nHub == 0))
            zLeft  = spoke.zDisplacement;
        if ((spoke.flange == 1) && (spoke.nHub == 0))
            zRight = spoke.zDisplacement;
        }

    D_Graph->traceHubRim(hub.flangeDiameterL,hub.flangeDiameterR,hub.widthL,hub.widthR,hub.old,rim.erd,zLeft,zRight);
}





void spoQQs::setMainWindowParameters  (bool front , int holes , int holesL , float rotation ,
                                       int SpBlockL , int schemeL1 , int schemeL2 , int schemeL3 , int schemeL4 , int schemeL5 , int schemeL6 ,
                                       int SpBlockR , int schemeR1 , int schemeR2 , int schemeR3 , int schemeR4 , int schemeR5 , int schemeR6 ,
                                       bool isTiltAuto , float flangesTilt , float flangesTiltAuto ,
                                       bool isStraightpullL , bool isPairedL , bool isRadialStraightpullL ,
                                       bool isStraightpullR , bool isPairedR , bool isRadialStraightpullR , bool isAlternativeCoupled ,
                                       bool isGrouped , bool isGroupedAuto , bool isSwapped , int holesPerGroupMan , int holesPerGroupAuto , int holesPerGroupShift , float groupedHolesDistance)
{
    float   pi = 3.1415927;
    int     index;
    int     holesR;

    hub.isFront = front;
    rim.isFront = front;
    holesR = holes - holesL;

    if (!isGrouped || (!isGroupedAuto && (holesPerGroupMan == 1)))
        ui->doubleSpinBox_rimHoleAngle->setValue(360.0/holes);
    else
        ui->doubleSpinBox_rimHoleAngle->setValue(180.0*rim.getGroupedHolesAngle()/pi);

    if (isRadialStraightpullL || (!isPairedL && !isStraightpullL))
        ui->doubleSpinBox_flangeAngleL->setValue(360.0/holesL);
    else
        ui->doubleSpinBox_flangeAngleL->setValue(asin(double(2.0*hub.holesOffsetL/hub.flangeDiameterL))*360.0/pi);

    if (isRadialStraightpullR || (!isPairedR && !isStraightpullR))
        ui->doubleSpinBox_flangeAngleR->setValue(360.0/holesR);
    else
        ui->doubleSpinBox_flangeAngleR->setValue(asin(double(2.0*hub.holesOffsetR/hub.flangeDiameterR))*360.0/pi);

    ui->checkBox_isFront->setChecked(front);
    ui->spinBox_rimHoles->setValue(holes);
    ui->spinBox_hubHolesL->setValue(holesL);
    ui->spinBox_hubHolesR->setValue(holesR);
    ui->doubleSpinBox_rimRotation->setValue(rotation*180.0/pi);

    ui->spinBox_spokesPerBlockL->setValue(SpBlockL);
    if (patternL.check())
        ui->spinBox_spokesPerBlockL->setStyleSheet("background-color: lightGreen");
    else
        ui->spinBox_spokesPerBlockL->setStyleSheet("background-color: red");
    ui->spinBox_pattL_1->setValue(schemeL1);
    ui->spinBox_pattL_2->setValue(schemeL2);
    ui->spinBox_pattL_3->setValue(schemeL3);
    ui->spinBox_pattL_4->setValue(schemeL4);
    ui->spinBox_pattL_5->setValue(schemeL5);
    ui->spinBox_pattL_6->setValue(schemeL6);
    switch (SpBlockL)
        {
        case (1):
            {
            ui->spinBox_pattL_1->setEnabled(true);
            ui->spinBox_pattL_2->setEnabled(false);
            ui->spinBox_pattL_3->setEnabled(false);
            ui->spinBox_pattL_4->setEnabled(false);
            ui->spinBox_pattL_5->setEnabled(false);
            ui->spinBox_pattL_6->setEnabled(false);
            }
        break;
        case (2):
            {
            ui->spinBox_pattL_1->setEnabled(true);
            ui->spinBox_pattL_2->setEnabled(true);
            ui->spinBox_pattL_3->setEnabled(false);
            ui->spinBox_pattL_4->setEnabled(false);
            ui->spinBox_pattL_5->setEnabled(false);
            ui->spinBox_pattL_6->setEnabled(false);
            }
        break;
        case (3):
            {
            ui->spinBox_pattL_1->setEnabled(true);
            ui->spinBox_pattL_2->setEnabled(true);
            ui->spinBox_pattL_3->setEnabled(true);
            ui->spinBox_pattL_4->setEnabled(false);
            ui->spinBox_pattL_5->setEnabled(false);
            ui->spinBox_pattL_6->setEnabled(false);
            }
        break;
        case (4):
            {
            ui->spinBox_pattL_1->setEnabled(true);
            ui->spinBox_pattL_2->setEnabled(true);
            ui->spinBox_pattL_3->setEnabled(true);
            ui->spinBox_pattL_4->setEnabled(true);
            ui->spinBox_pattL_5->setEnabled(false);
            ui->spinBox_pattL_6->setEnabled(false);
            }
        break;
        case (5):
            {
            ui->spinBox_pattL_1->setEnabled(true);
            ui->spinBox_pattL_2->setEnabled(true);
            ui->spinBox_pattL_3->setEnabled(true);
            ui->spinBox_pattL_4->setEnabled(true);
            ui->spinBox_pattL_5->setEnabled(true);
            ui->spinBox_pattL_6->setEnabled(false);
            }
        break;
        case (6):
            {
            ui->spinBox_pattL_1->setEnabled(true);
            ui->spinBox_pattL_2->setEnabled(true);
            ui->spinBox_pattL_3->setEnabled(true);
            ui->spinBox_pattL_4->setEnabled(true);
            ui->spinBox_pattL_5->setEnabled(true);
            ui->spinBox_pattL_6->setEnabled(true);
            }
        break;
        }
    if (hub.isRadialStraightpullL)
        {
        ui->spinBox_spokesPerBlockL->setEnabled(false);
        ui->spinBox_pattL_1->setEnabled(false);
        ui->spinBox_pattL_2->setEnabled(false);
        ui->spinBox_pattL_3->setEnabled(false);
        ui->spinBox_pattL_4->setEnabled(false);
        ui->spinBox_pattL_5->setEnabled(false);
        ui->spinBox_pattL_6->setEnabled(false);
        }
    else
        ui->spinBox_spokesPerBlockL->setEnabled(true);
    ui->spinBox_spokesPerBlockR->setValue(SpBlockR);
    if (patternR.check())
        ui->spinBox_spokesPerBlockR->setStyleSheet("background-color: lightGreen");
    else
        ui->spinBox_spokesPerBlockR->setStyleSheet("background-color: red");
    ui->spinBox_pattR_1->setValue(schemeR1);
    ui->spinBox_pattR_2->setValue(schemeR2);
    ui->spinBox_pattR_3->setValue(schemeR3);
    ui->spinBox_pattR_4->setValue(schemeR4);
    ui->spinBox_pattR_5->setValue(schemeR5);
    ui->spinBox_pattR_6->setValue(schemeR6);
    switch (SpBlockR)
        {
        case (1):
            {
            ui->spinBox_pattR_1->setEnabled(true);
            ui->spinBox_pattR_2->setEnabled(false);
            ui->spinBox_pattR_3->setEnabled(false);
            ui->spinBox_pattR_4->setEnabled(false);
            ui->spinBox_pattR_5->setEnabled(false);
            ui->spinBox_pattR_6->setEnabled(false);
            }
        break;
        case (2):
            {
            ui->spinBox_pattR_1->setEnabled(true);
            ui->spinBox_pattR_2->setEnabled(true);
            ui->spinBox_pattR_3->setEnabled(false);
            ui->spinBox_pattR_4->setEnabled(false);
            ui->spinBox_pattR_5->setEnabled(false);
            ui->spinBox_pattR_6->setEnabled(false);
            }
        break;
        case (3):
            {
            ui->spinBox_pattR_1->setEnabled(true);
            ui->spinBox_pattR_2->setEnabled(true);
            ui->spinBox_pattR_3->setEnabled(true);
            ui->spinBox_pattR_4->setEnabled(false);
            ui->spinBox_pattR_5->setEnabled(false);
            ui->spinBox_pattR_6->setEnabled(false);
            }
        break;
        case (4):
            {
            ui->spinBox_pattR_1->setEnabled(true);
            ui->spinBox_pattR_2->setEnabled(true);
            ui->spinBox_pattR_3->setEnabled(true);
            ui->spinBox_pattR_4->setEnabled(true);
            ui->spinBox_pattR_5->setEnabled(false);
            ui->spinBox_pattR_6->setEnabled(false);
            }
        break;
        case (5):
            {
            ui->spinBox_pattR_1->setEnabled(true);
            ui->spinBox_pattR_2->setEnabled(true);
            ui->spinBox_pattR_3->setEnabled(true);
            ui->spinBox_pattR_4->setEnabled(true);
            ui->spinBox_pattR_5->setEnabled(true);
            ui->spinBox_pattR_6->setEnabled(false);
            }
        break;
        case (6):
            {
            ui->spinBox_pattR_1->setEnabled(true);
            ui->spinBox_pattR_2->setEnabled(true);
            ui->spinBox_pattR_3->setEnabled(true);
            ui->spinBox_pattR_4->setEnabled(true);
            ui->spinBox_pattR_5->setEnabled(true);
            ui->spinBox_pattR_6->setEnabled(true);
            }
        break;
        }
    if (hub.isRadialStraightpullR)
        {
        ui->spinBox_spokesPerBlockR->setEnabled(false);
        ui->spinBox_pattR_1->setEnabled(false);
        ui->spinBox_pattR_2->setEnabled(false);
        ui->spinBox_pattR_3->setEnabled(false);
        ui->spinBox_pattR_4->setEnabled(false);
        ui->spinBox_pattR_5->setEnabled(false);
        ui->spinBox_pattR_6->setEnabled(false);
        }
    else
        ui->spinBox_spokesPerBlockR->setEnabled(true);
    ui->checkBox_tiltAuto->setChecked(isTiltAuto);
    ui->doubleSpinBox_flangesTilt->setValue(flangesTilt*180.0/pi);
    ui->doubleSpinBox_flangesTilt->setDisabled(isTiltAuto);
    ui->doubleSpinBox_flangesTiltAuto->setValue(flangesTiltAuto*180.0/pi);
    ui->doubleSpinBox_flangesTiltAuto->setEnabled(isTiltAuto);

    index = 0;
    if (isRadialStraightpullL)
        index = 2;
    else if (isStraightpullL)
        index = 1;
    else if (isPairedL)
        index = 3;
    ui->comboBox_flangeTypeL->setCurrentIndex(index);

    index = 0;
    if (isRadialStraightpullR)
        index = 2;
    else if (isStraightpullR)
        index = 1;
    else if (isPairedR)
        index = 3;
    ui->comboBox_flangeTypeR->setCurrentIndex(index);

    ui->checkBox_alternativeLacing->setChecked(isAlternativeCoupled);

    ui->checkBox_grouped->setChecked(isGrouped);
    ui->Box_Grouped->setEnabled(isGrouped);
    ui->checkBox_groupedAuto->setChecked(isGroupedAuto);
    ui->checkBox_swapped->setChecked(isSwapped);
    ui->spinBox_spokesPerGroupMan->setValue(holesPerGroupMan);
    ui->spinBox_spokesPerGroupMan->setDisabled(isGroupedAuto);
    ui->spinBox_spokesPerGroupAuto->setValue(holesPerGroupAuto);
    ui->spinBox_spokesPerGroupAuto->setEnabled(isGroupedAuto);
    ui->spinBox_spokesPerGroupShift->setValue(holesPerGroupShift);
    ui->doubleSpinBox_groupedHolesDistance->setValue(groupedHolesDistance);
}





void spoQQs::on_checkBox_isFront_clicked()
{
    emit changedParameters(false);
}





void spoQQs::on_spinBox_rimHoles_valueChanged(int arg1)
{
    emit changedParameters(true);
    arg1++;
}





void spoQQs::on_checkBox_grouped_clicked()
{
    emit changedParameters(true);
}





void spoQQs::on_checkBox_groupedAuto_clicked()
{
    emit changedParameters(true);
}





void spoQQs::on_spinBox_spokesPerGroupMan_valueChanged(int arg1)
{
    emit changedParameters(true);
    arg1++;
}





void spoQQs::on_doubleSpinBox_groupedHolesDistance_valueChanged(double arg1)
{
    emit changedParameters(true);
    arg1++;
}





void spoQQs::on_spinBox_spokesPerGroupShift_valueChanged(int arg1)
{
    emit changedParameters(true);
    arg1++;
}





void spoQQs::on_checkBox_swapped_clicked()
{
    emit changedParameters(false);
}





void spoQQs::on_doubleSpinBox_rimRotation_valueChanged(double arg1)
{
    emit changedParameters(false);
    arg1++;
}





void spoQQs::on_checkBox_tiltAuto_clicked()
{
    emit changedParameters(true);
}





void spoQQs::on_doubleSpinBox_flangesTilt_valueChanged(double arg1)
{
    emit changedParameters(true);
    arg1++;
}





void spoQQs::on_spinBox_hubHolesL_valueChanged(int arg1)
{
    emit changedParameters(true);
    arg1++;
}





void spoQQs::on_comboBox_flangeTypeL_currentIndexChanged(int index)
{
    emit changedParameters(true);
    index++;
}





void spoQQs::on_spinBox_spokesPerBlockL_valueChanged(int arg1)
{
    emit changedParameters(false);
    arg1++;
}





void spoQQs::on_spinBox_pattL_1_valueChanged(int arg1)
{
    emit changedParameters(false);
    arg1++;
}





void spoQQs::on_spinBox_pattL_2_valueChanged(int arg1)
{
    emit changedParameters(false);
    arg1++;
}





void spoQQs::on_spinBox_pattL_3_valueChanged(int arg1)
{
    emit changedParameters(false);
    arg1++;
}





void spoQQs::on_spinBox_pattL_4_valueChanged(int arg1)
{
    emit changedParameters(false);
    arg1++;
}





void spoQQs::on_spinBox_pattL_5_valueChanged(int arg1)
{
    emit changedParameters(false);
    arg1++;
}





void spoQQs::on_spinBox_pattL_6_valueChanged(int arg1)
{
    emit changedParameters(false);
    arg1++;
}





void spoQQs::on_comboBox_flangeTypeR_currentIndexChanged(int index)
{
    emit changedParameters(true);
    index++;

}





void spoQQs::on_checkBox_alternativeLacing_clicked()
{
    emit changedParameters(true);
}





void spoQQs::on_spinBox_spokesPerBlockR_valueChanged(int arg1)
{
    emit changedParameters(false);
    arg1++;
}





void spoQQs::on_spinBox_pattR_1_valueChanged(int arg1)
{
    emit changedParameters(false);
    arg1++;
}





void spoQQs::on_spinBox_pattR_2_valueChanged(int arg1)
{
    emit changedParameters(false);
    arg1++;
}





void spoQQs::on_spinBox_pattR_3_valueChanged(int arg1)
{
    emit changedParameters(false);
    arg1++;
}





void spoQQs::on_spinBox_pattR_4_valueChanged(int arg1)
{
    emit changedParameters(false);
    arg1++;
}





void spoQQs::on_spinBox_pattR_5_valueChanged(int arg1)
{
    emit changedParameters(false);
    arg1++;
}





void spoQQs::on_spinBox_pattR_6_valueChanged(int arg1)
{
    emit changedParameters(false);
    arg1++;
}





bool spoQQs::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type()==QEvent::KeyPress)
        {
        QKeyEvent* key = static_cast <QKeyEvent*> (event);
        if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) )
            {
            focusNextChild();
            return true;
            }
        else
            {
            return QObject::eventFilter(obj, event);
            }
        }
    else
        {
        return QObject::eventFilter(obj, event);
        }
}
