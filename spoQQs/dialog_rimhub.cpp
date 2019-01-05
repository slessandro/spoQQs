#include <dialog_rimhub.h>
#include <ui_dialog_rimhub.h>

#include <QStandardItemModel>
#include <QFile>
#include <QtAlgorithms>
#include <QTextStream>
#include <QCloseEvent>
#include <QDebug>





Dialog_RimHub::Dialog_RimHub(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_RimHub)
{
    ui->setupUi(this);

    ui->doubleSpinBox_ERD->installEventFilter(this);
    ui->doubleSpinBox_OSB->installEventFilter(this);
    ui->doubleSpinBox_Bed->installEventFilter(this);
    ui->doubleSpinBox_ISO->installEventFilter(this);
    ui->doubleSpinBox_WeightRim->installEventFilter(this);
    ui->doubleSpinBox_hL->installEventFilter(this);
    ui->doubleSpinBox_dL->installEventFilter(this);
    ui->doubleSpinBox_wL->installEventFilter(this);
    ui->doubleSpinBox_oL->installEventFilter(this);
    ui->doubleSpinBox_hR->installEventFilter(this);
    ui->doubleSpinBox_dR->installEventFilter(this);
    ui->doubleSpinBox_wR->installEventFilter(this);
    ui->doubleSpinBox_oR->installEventFilter(this);
    ui->doubleSpinBox_OLD->installEventFilter(this);
    ui->doubleSpinBox_weightHub->installEventFilter(this);

    ui->lineEdit_FR->setMaxLength(1);

    toggle_D_RimHub = true;

    d_Position = this->geometry();


    QStandardItemModel *modelRim = new QStandardItemModel;
    QFile fileRim("listrim.csv");
    if (fileRim.open(QIODevice::ReadOnly))
        {
        int lineindex = 0;
        QTextStream in(&fileRim);
        while (!in.atEnd())
            {
            QString fileLine = in.readLine();
            QStringList lineToken = fileLine.split(",", QString::KeepEmptyParts);
            for (int j = 0; j < lineToken.size(); j++)
                {
                QString value = lineToken.at(j);
                QStandardItem *item = new QStandardItem(value);
                if (j != 6 && j != 7) item->setTextAlignment(Qt::AlignCenter);
                modelRim->setItem(lineindex, j, item);
                }
            lineindex++;
            }
        fileRim.close();
        }

    modelRim->setHeaderData(0,Qt::Horizontal, "ERD");
    modelRim->setHeaderData(1,Qt::Horizontal, "OSB");
    modelRim->setHeaderData(2,Qt::Horizontal, "Bed");
    modelRim->setHeaderData(3,Qt::Horizontal, "Weight");
    modelRim->setHeaderData(4,Qt::Horizontal, "Size");
    modelRim->setHeaderData(5,Qt::Horizontal, "ISO");
    modelRim->setHeaderData(6,Qt::Horizontal, "Rim");
    modelRim->setHeaderData(7,Qt::Horizontal, "Note");

    ui->tableView_Rim->setModel(modelRim);

    ui->tableView_Rim->setColumnWidth(0, 60);
    ui->tableView_Rim->setColumnWidth(1, 60);
    ui->tableView_Rim->setColumnWidth(2, 60);
    ui->tableView_Rim->setColumnWidth(3, 60);
    ui->tableView_Rim->setColumnWidth(4, 60);
    ui->tableView_Rim->setColumnWidth(5, 60);
    ui->tableView_Rim->setColumnWidth(6, 550);
    ui->tableView_Rim->setColumnWidth(7, 40);


    QStandardItemModel *modelHub = new QStandardItemModel;
    QFile fileHub("listhub.csv");
    if (fileHub.open(QIODevice::ReadOnly))
        {
        int lineindex = 0;
        QTextStream in(&fileHub);
        while (!in.atEnd())
            {
            QString fileLine = in.readLine();
            QStringList lineToken = fileLine.split(",", QString::KeepEmptyParts);
            for (int j = 0; j < lineToken.size(); j++)
                {
                QString value = lineToken.at(j);
                QStandardItem *item = new QStandardItem(value);
                if (j != 12 && j != 13) item->setTextAlignment(Qt::AlignCenter);
                modelHub->setItem(lineindex, j, item);
                }
            lineindex++;
            }
        fileHub.close();
        }

    modelHub->setHeaderData( 0,Qt::Horizontal, "hL");
    modelHub->setHeaderData( 1,Qt::Horizontal, "oL");
    modelHub->setHeaderData( 2,Qt::Horizontal, "dL");
    modelHub->setHeaderData( 3,Qt::Horizontal, "wL");
    modelHub->setHeaderData( 4,Qt::Horizontal, "hR");
    modelHub->setHeaderData( 5,Qt::Horizontal, "oR");
    modelHub->setHeaderData( 6,Qt::Horizontal, "dR");
    modelHub->setHeaderData( 7,Qt::Horizontal, "wR");
    modelHub->setHeaderData( 8,Qt::Horizontal, "Weight");
    modelHub->setHeaderData( 9,Qt::Horizontal, "F/R");
    modelHub->setHeaderData(10,Qt::Horizontal, "Cogs");
    modelHub->setHeaderData(11,Qt::Horizontal, "OLD");
    modelHub->setHeaderData(12,Qt::Horizontal, "Hub");
    modelHub->setHeaderData(13,Qt::Horizontal, "Note");

    ui->tableView_Hub->setModel(modelHub);

    ui->tableView_Hub->setColumnWidth( 0, 60);
    ui->tableView_Hub->setColumnWidth( 1, 60);
    ui->tableView_Hub->setColumnWidth( 2, 60);
    ui->tableView_Hub->setColumnWidth( 3, 60);
    ui->tableView_Hub->setColumnWidth( 4, 60);
    ui->tableView_Hub->setColumnWidth( 5, 60);
    ui->tableView_Hub->setColumnWidth( 6, 60);
    ui->tableView_Hub->setColumnWidth( 7, 60);
    ui->tableView_Hub->setColumnWidth( 8, 60);
    ui->tableView_Hub->setColumnWidth( 9, 60);
    ui->tableView_Hub->setColumnWidth(10, 60);
    ui->tableView_Hub->setColumnWidth(11, 60);
    ui->tableView_Hub->setColumnWidth(12, 260);
    ui->tableView_Hub->setColumnWidth(13, 40);

    QObject::connect(this,SIGNAL(changedRimHubParameters(bool)),this,SLOT(on_changedRimHubParameters(bool)));
}





Dialog_RimHub::~Dialog_RimHub()
{
    delete ui;
}





void Dialog_RimHub::setRimParameters(float erd , float osb , float bed , float weight , QString label , QString size , float iso , QString note)
{
    ui->doubleSpinBox_ERD->setValue(erd);
    ui->doubleSpinBox_OSB->setValue(osb);
    ui->doubleSpinBox_Bed->setValue(bed);
    ui->doubleSpinBox_WeightRim->setValue(weight);
    ui->lineEdit_rim->setText(label);
    ui->lineEdit_rimSize->setText(size);
    ui->doubleSpinBox_ISO->setValue(iso);
    ui->lineEdit_rimNote->setText(note);
}





QString Dialog_RimHub::getRimLabel(void)
{
    return ui->lineEdit_rim->text();
}





float Dialog_RimHub::getERD_box(void)
{
    return ui->doubleSpinBox_ERD->value();
}





float Dialog_RimHub::getOSB_box(void)
{
    return ui->doubleSpinBox_OSB->value();
}





float Dialog_RimHub::getBed_box(void)
{
    return ui->doubleSpinBox_Bed->value();
}





float Dialog_RimHub::getWeightRim_box(void)
{
    return ui->doubleSpinBox_WeightRim->value();
}





QString Dialog_RimHub::getRimSize(void)
{
    return ui->lineEdit_rimSize->text();
}





float Dialog_RimHub::getISO_box(void)
{
    return ui->doubleSpinBox_ISO->value();
}





QString Dialog_RimHub::getRimNote(void)
{
    return ui->lineEdit_rimNote->text();
}





void Dialog_RimHub::setHubParameters(float hL , float dL , float wL , float oL , float hR , float dR , float wR, float oR , float old , float weight , QString label , QString fr , QString cogs , QString note)
{
    ui->doubleSpinBox_hL->setValue(hL);
    ui->doubleSpinBox_dL->setValue(dL);
    ui->doubleSpinBox_wL->setValue(wL);
    ui->doubleSpinBox_oL->setValue(oL);
    ui->doubleSpinBox_hR->setValue(hR);
    ui->doubleSpinBox_dR->setValue(dR);
    ui->doubleSpinBox_wR->setValue(wR);
    ui->doubleSpinBox_oR->setValue(oR);
    ui->doubleSpinBox_OLD->setValue(old);
    ui->doubleSpinBox_weightHub->setValue(weight);
    ui->lineEdit_hub->setText(label);
    ui->lineEdit_FR->setText(fr);
    ui->lineEdit_cogs->setText(cogs);
    ui->lineEdit_hubNote->setText(note);
}





QString Dialog_RimHub::getHubLabel(void)
{
    return ui->lineEdit_hub->text();
}





float Dialog_RimHub::getHL_box(void)
{
    return ui->doubleSpinBox_hL->value();
}





float Dialog_RimHub::getOL_box(void)
{
    return ui->doubleSpinBox_oL->value();
}





float Dialog_RimHub::getDL_box(void)
{
    return ui->doubleSpinBox_dL->value();
}





float Dialog_RimHub::getWL_box(void)
{
    return ui->doubleSpinBox_wL->value();
}





float Dialog_RimHub::getHR_box(void)
{
    return ui->doubleSpinBox_hR->value();
}





float Dialog_RimHub::getOR_box(void)
{
    return ui->doubleSpinBox_oR->value();
}





float Dialog_RimHub::getDR_box(void)
{
    return ui->doubleSpinBox_dR->value();
}





float Dialog_RimHub::getWR_box(void)
{
    return ui->doubleSpinBox_wR->value();
}





float Dialog_RimHub::getOld_box(void)
{
    return ui->doubleSpinBox_OLD->value();
}





float Dialog_RimHub::getWeightHub_box(void)
{
    return ui->doubleSpinBox_weightHub->value();
}





QString Dialog_RimHub::getFR(void)
{
    return ui->lineEdit_FR->text();
}





QString Dialog_RimHub::getCogs(void)
{
    return ui->lineEdit_cogs->text();
}





QString Dialog_RimHub::getHubNote(void)
{
    return ui->lineEdit_hubNote->text();
}





void Dialog_RimHub::setToggle_D_RimHub()
{
    if (toggle_D_RimHub)
        {
        this->setGeometry(d_Position);
        this->show();
        }
    else
        {
        d_Position = this->geometry();
        this->hide();
        }
    toggle_D_RimHub = !toggle_D_RimHub;
}





void Dialog_RimHub::on_tableView_Rim_clicked(const QModelIndex &index)
{
    QString             textString;
    int                 row;
    QAbstractItemModel* modelTmp;
    QModelIndex         indexTmp;

    QObject::disconnect(this,SIGNAL(changedRimHubParameters(bool)),this,SLOT(on_changedRimHubParameters(bool)));

    row = index.row();
    modelTmp = ui->tableView_Rim->model();

    indexTmp = modelTmp->index(row,0, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->doubleSpinBox_ERD->setValue(textString.toDouble());

    indexTmp = modelTmp->index(row,1, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->doubleSpinBox_OSB->setValue(textString.toDouble());

    indexTmp = modelTmp->index(row,2, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->doubleSpinBox_Bed->setValue(textString.toDouble());

    indexTmp = modelTmp->index(row,3, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->doubleSpinBox_WeightRim->setValue(textString.toDouble());

    indexTmp = modelTmp->index(row,4, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->lineEdit_rimSize->setText(textString);

    indexTmp = modelTmp->index(row,5, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->doubleSpinBox_ISO->setValue(textString.toDouble());

    indexTmp = modelTmp->index(row,6, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->lineEdit_rim->setText(textString);

    indexTmp = modelTmp->index(row,7, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->lineEdit_rimNote->setText(textString);

    QObject::connect(this,SIGNAL(changedRimHubParameters(bool)),this,SLOT(on_changedRimHubParameters(bool)));
    emit changedRimHubParameters (true);
}





void Dialog_RimHub::on_tableView_Hub_clicked(const QModelIndex &index)
{
    QString             textString;
    int                 row;
    QAbstractItemModel* modelTmp;
    QModelIndex         indexTmp;

    QObject::disconnect(this,SIGNAL(changedRimHubParameters(bool)),this,SLOT(on_changedRimHubParameters(bool)));

    row = index.row();
    modelTmp = ui->tableView_Hub->model();

    indexTmp = modelTmp->index(row,0, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->doubleSpinBox_hL->setValue(textString.toDouble());

    indexTmp = modelTmp->index(row,1, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->doubleSpinBox_oL->setValue(textString.toDouble());

    indexTmp = modelTmp->index(row,2, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->doubleSpinBox_dL->setValue(textString.toDouble());

    indexTmp = modelTmp->index(row,3, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->doubleSpinBox_wL->setValue(textString.toDouble());

    indexTmp = modelTmp->index(row,4, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->doubleSpinBox_hR->setValue(textString.toDouble());

    indexTmp = modelTmp->index(row,5, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->doubleSpinBox_oR->setValue(textString.toDouble());

    indexTmp = modelTmp->index(row,6, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->doubleSpinBox_dR->setValue(textString.toDouble());

    indexTmp = modelTmp->index(row,7, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->doubleSpinBox_wR->setValue(textString.toDouble());

    indexTmp = modelTmp->index(row,8, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->doubleSpinBox_weightHub->setValue(textString.toDouble());

    indexTmp = modelTmp->index(row,9, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->lineEdit_FR->setText(textString);

    indexTmp = modelTmp->index(row,10, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->lineEdit_cogs->setText(textString);

    indexTmp = modelTmp->index(row,11, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->doubleSpinBox_OLD->setValue(textString.toDouble());

    indexTmp = modelTmp->index(row,12, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->lineEdit_hub->setText(textString);

    indexTmp = modelTmp->index(row,13, QModelIndex());
    textString= modelTmp->data(indexTmp).toString();
    ui->lineEdit_hubNote->setText(textString);

    QObject::connect(this,SIGNAL(changedRimHubParameters(bool)),this,SLOT(on_changedRimHubParameters(bool)));
    emit changedRimHubParameters (true);
}





void Dialog_RimHub::on_pushButton_rimAdd_clicked()
{
    QStandardItem*          item;
    QStandardItemModel*     modelTmp;
    QList<QStandardItem *>  listItem;

    modelTmp = static_cast<QStandardItemModel*>(ui->tableView_Rim->model());

    item = new QStandardItem(QString::number(ui->doubleSpinBox_ERD->value(), 'f', 2));
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(QString::number(ui->doubleSpinBox_OSB->value(), 'f', 2));
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(QString::number(ui->doubleSpinBox_Bed->value(), 'f', 2));
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(QString::number(ui->doubleSpinBox_WeightRim->value(), 'f', 2));
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(ui->lineEdit_rimSize->text());
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(QString::number(ui->doubleSpinBox_ISO->value(), 'f', 0));
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(ui->lineEdit_rim->text());
    listItem.append(item);

    item = new QStandardItem(ui->lineEdit_rimNote->text());
    listItem.append(item);

    modelTmp->appendRow(listItem);
}





void Dialog_RimHub::on_pushButton_hubAdd_clicked()
{
    QStandardItem*          item;
    QStandardItemModel*     modelTmp;
    QList<QStandardItem *>  listItem;

    modelTmp = static_cast<QStandardItemModel*>(ui->tableView_Hub->model());

    item = new QStandardItem(QString::number(ui->doubleSpinBox_hL->value(), 'f', 2));
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(QString::number(ui->doubleSpinBox_oL->value(), 'f', 2));
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(QString::number(ui->doubleSpinBox_dL->value(), 'f', 2));
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(QString::number(ui->doubleSpinBox_wL->value(), 'f', 2));
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(QString::number(ui->doubleSpinBox_hR->value(), 'f', 2));
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(QString::number(ui->doubleSpinBox_oR->value(), 'f', 2));
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(QString::number(ui->doubleSpinBox_dR->value(), 'f', 2));
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(QString::number(ui->doubleSpinBox_wR->value(), 'f', 2));
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(QString::number(ui->doubleSpinBox_weightHub->value(), 'f', 0));
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(ui->lineEdit_FR->text());
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(ui->lineEdit_cogs->text());
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(QString::number(ui->doubleSpinBox_OLD->value(), 'f', 0));
    item->setTextAlignment(Qt::AlignCenter);
    listItem.append(item);

    item = new QStandardItem(ui->lineEdit_hub->text());
    listItem.append(item);

    item = new QStandardItem(ui->lineEdit_hubNote->text());
    listItem.append(item);

    modelTmp->appendRow(listItem);
}





void Dialog_RimHub::on_pushButton_rimDel_clicked()
{
    QModelIndexList         selection;

    selection = ui->tableView_Rim->selectionModel()->selectedRows();
    qSort(selection.begin() , selection.end() , qGreater<QModelIndex>());
    for(QModelIndexList::Iterator it = selection.begin() ; it != selection.end() ; it++)
        {
        ui->tableView_Rim->model()->removeRow(it->row());
        }
    ui->tableView_Rim->clearSelection();
}





void Dialog_RimHub::on_pushButton_hubDel_clicked()
{
    QModelIndexList         selection;

    selection = ui->tableView_Hub->selectionModel()->selectedRows();
    qSort(selection.begin() , selection.end() , qGreater<QModelIndex>());
    for(QModelIndexList::Iterator it = selection.begin() ; it != selection.end() ; it++)
        {
        ui->tableView_Hub->model()->removeRow(it->row());
        }
    ui->tableView_Hub->clearSelection();
}





void Dialog_RimHub::on_pushButton_rimSave_clicked()
{
    QString textData;
    QString textTmp;
    int     rows;
    int     columns;

    rows = ui->tableView_Rim->model()->rowCount();
    columns = ui->tableView_Rim->model()->columnCount();

    for (int i = 0; i < rows; i++)
        {
        for (int j = 0; j < columns; j++)
            {
            textTmp = ui->tableView_Rim->model()->data(ui->tableView_Rim->model()->index(i,j)).toString();
            textTmp.replace(',','.');
            textData += textTmp;
            textData += ",";
            }
        textData.chop(1);
        textData += "\n";
        }

    QFile csvFile("listrim.csv");
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
        QTextStream out(&csvFile);
        out << textData;
        csvFile.close();
        }
}





void Dialog_RimHub::on_pushButton_hubSave_clicked()
{
    QString textData;
    QString textTmp;
    int     rows;
    int     columns;

    rows = ui->tableView_Hub->model()->rowCount();
    columns = ui->tableView_Hub->model()->columnCount();

    for (int i = 0; i < rows; i++)
        {
        for (int j = 0; j < columns; j++)
            {
            textTmp = ui->tableView_Hub->model()->data(ui->tableView_Hub->model()->index(i,j)).toString();
            textTmp.replace(',','.');
            textData += textTmp;
            textData += ",";
            }
        textData.chop(1);
        textData += "\n";
        }

    QFile csvFile("listhub.csv");
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
        QTextStream out(&csvFile);
        out << textData;
        csvFile.close();
        }
}





void Dialog_RimHub::on_lineEdit_rimSize_returnPressed()
{
    emit changedRimHubParameters (false);
    this->focusNextChild();
}





void Dialog_RimHub::on_lineEdit_rim_returnPressed()
{
    emit changedRimHubParameters (false);
    this->focusNextChild();
}





void Dialog_RimHub::on_lineEdit_rimNote_returnPressed()
{
    emit changedRimHubParameters (false);
    this->focusNextChild();
}





void Dialog_RimHub::on_doubleSpinBox_ERD_valueChanged(double arg1)
{
    emit changedRimHubParameters (true);
    arg1++;
}





void Dialog_RimHub::on_doubleSpinBox_OSB_valueChanged(double arg1)
{
    emit changedRimHubParameters (true);
    arg1++;
}





void Dialog_RimHub::on_doubleSpinBox_Bed_valueChanged(double arg1)
{
    emit changedRimHubParameters (true);
    arg1++;
}





void Dialog_RimHub::on_doubleSpinBox_ISO_valueChanged(double arg1)
{
    emit changedRimHubParameters (true);
    arg1++;
}





void Dialog_RimHub::on_doubleSpinBox_WeightRim_valueChanged(double arg1)
{
    emit changedRimHubParameters (false);
    arg1++;
}





void Dialog_RimHub::on_lineEdit_FR_returnPressed()
{
    if ((ui->lineEdit_FR->text() != "R") && (ui->lineEdit_FR->text() != "F"))
            ui->lineEdit_FR->setText("");
    emit changedRimHubParameters (false);
    this->focusNextChild();
}





void Dialog_RimHub::on_lineEdit_cogs_returnPressed()
{
    emit changedRimHubParameters (false);
    this->focusNextChild();
}





void Dialog_RimHub::on_lineEdit_hub_returnPressed()
{
    emit changedRimHubParameters (false);
    this->focusNextChild();
}





void Dialog_RimHub::on_lineEdit_hubNote_returnPressed()
{
    emit changedRimHubParameters (false);
    this->focusNextChild();
}





void Dialog_RimHub::on_doubleSpinBox_hL_valueChanged(double arg1)
{
    emit changedRimHubParameters (true);
    arg1++;
}





void Dialog_RimHub::on_doubleSpinBox_dL_valueChanged(double arg1)
{
    emit changedRimHubParameters (true);
    arg1++;
}





void Dialog_RimHub::on_doubleSpinBox_wL_valueChanged(double arg1)
{
    emit changedRimHubParameters (true);
    arg1++;
}





void Dialog_RimHub::on_doubleSpinBox_oL_valueChanged(double arg1)
{
    emit changedRimHubParameters (true);
    arg1++;
}





void Dialog_RimHub::on_doubleSpinBox_hR_valueChanged(double arg1)
{
    emit changedRimHubParameters (true);
    arg1++;
}





void Dialog_RimHub::on_doubleSpinBox_dR_valueChanged(double arg1)
{
    emit changedRimHubParameters (true);
    arg1++;
}





void Dialog_RimHub::on_doubleSpinBox_wR_valueChanged(double arg1)
{
    emit changedRimHubParameters (true);
    arg1++;
}





void Dialog_RimHub::on_doubleSpinBox_oR_valueChanged(double arg1)
{
    emit changedRimHubParameters (true);
    arg1++;
}





void Dialog_RimHub::on_doubleSpinBox_OLD_valueChanged(double arg1)
{
    emit changedRimHubParameters (false);
    arg1++;
}





void Dialog_RimHub::on_doubleSpinBox_weightHub_valueChanged(double arg1)
{
    emit changedRimHubParameters (false);
    arg1++;
}





void Dialog_RimHub::on_changedRimHubParameters(bool isFromStart)
{
    emit changedParameters (isFromStart);
}





bool Dialog_RimHub::eventFilter(QObject *obj, QEvent *event)
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





void Dialog_RimHub::closeEvent(QCloseEvent *event)
{
    d_Position = this->geometry();
    toggle_D_RimHub = true;
    event->accept();
}
