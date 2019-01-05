#include <dialog_sponip.h>
#include <ui_dialog_sponip.h>

#include <QStandardItemModel>
#include <QFile>
#include <QtAlgorithms>
#include <QTextStream>
#include <QCloseEvent>
#include <QDebug>





Dialog_SpoNip::Dialog_SpoNip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_SpoNip)
{
    ui->setupUi(this);

    ui->doubleSpinBox_spokeThreadL->installEventFilter(this);
    ui->doubleSpinBox_spokeLengthL->installEventFilter(this);
    ui->doubleSpinBox_spokeWeightL->installEventFilter(this);
    ui->doubleSpinBox_spokePiecesL->installEventFilter(this);
    ui->doubleSpinBox_spokeThreadR->installEventFilter(this);
    ui->doubleSpinBox_spokeLengthR->installEventFilter(this);
    ui->doubleSpinBox_spokeWeightR->installEventFilter(this);
    ui->doubleSpinBox_spokePiecesR->installEventFilter(this);
    ui->doubleSpinBox_nippleThreadL->installEventFilter(this);
    ui->doubleSpinBox_nippleLengthL->installEventFilter(this);
    ui->doubleSpinBox_nippleWeightL->installEventFilter(this);
    ui->doubleSpinBox_nipplePiecesL->installEventFilter(this);
    ui->doubleSpinBox_nippleThreadR->installEventFilter(this);
    ui->doubleSpinBox_nippleLengthR->installEventFilter(this);
    ui->doubleSpinBox_nippleWeightR->installEventFilter(this);
    ui->doubleSpinBox_nipplePiecesR->installEventFilter(this);

    toggle_D_SpoNip = true;

    isLeft = true;

    ui->groupBox_SpoR->setChecked(false);
    ui->groupBox_NipR->setChecked(false);

    d_Position = this->geometry();


    QStandardItemModel *modelSpoke = new QStandardItemModel;
    QFile fileSpoke("listspoke.csv");
    if (fileSpoke.open(QIODevice::ReadOnly))
        {
        int lineindex = 0;
        QTextStream in(&fileSpoke);
        while (!in.atEnd())
            {
            QString fileLine = in.readLine();
            QStringList lineToken = fileLine.split(",", QString::KeepEmptyParts);
            for (int j = 0; j < lineToken.size(); j++)
                {
                QString value = lineToken.at(j);
                QStandardItem *item = new QStandardItem(value);
                if (j != 4) item->setTextAlignment(Qt::AlignCenter);
                modelSpoke->setItem(lineindex, j, item);
                }
            lineindex++;
            }
        fileSpoke.close();
        }

    modelSpoke->setHeaderData(0,Qt::Horizontal, "Thread");
    modelSpoke->setHeaderData(1,Qt::Horizontal, "Length");
    modelSpoke->setHeaderData(2,Qt::Horizontal, "Weight");
    modelSpoke->setHeaderData(3,Qt::Horizontal, "Pieces");
    modelSpoke->setHeaderData(4,Qt::Horizontal, "Spoke");

    ui->tableView_Spo->setModel(modelSpoke);

    ui->tableView_Spo->setColumnWidth(0, 90);
    ui->tableView_Spo->setColumnWidth(1, 90);
    ui->tableView_Spo->setColumnWidth(2, 90);
    ui->tableView_Spo->setColumnWidth(3, 90);


    QStandardItemModel *modelNipple = new QStandardItemModel;
    QFile fileNipple("listnipple.csv");
    if (fileNipple.open(QIODevice::ReadOnly))
        {
        int lineindex = 0;
        QTextStream in(&fileNipple);
        while (!in.atEnd())
            {
            QString fileLine = in.readLine();
            QStringList lineToken = fileLine.split(",", QString::KeepEmptyParts);
            for (int j = 0; j < lineToken.size(); j++)
                {
                QString value = lineToken.at(j);
                QStandardItem *item = new QStandardItem(value);
                if (j != 4) item->setTextAlignment(Qt::AlignCenter);
                modelNipple->setItem(lineindex, j, item);
                }
            lineindex++;
            }
        fileNipple.close();
        }

    modelNipple->setHeaderData(0,Qt::Horizontal, "Thread");
    modelNipple->setHeaderData(1,Qt::Horizontal, "Length");
    modelNipple->setHeaderData(2,Qt::Horizontal, "Weight");
    modelNipple->setHeaderData(3,Qt::Horizontal, "Pieces");
    modelNipple->setHeaderData(4,Qt::Horizontal, "Nipple");

    ui->tableView_Nip->setModel(modelNipple);

    ui->tableView_Nip->setColumnWidth(0, 90);
    ui->tableView_Nip->setColumnWidth(1, 90);
    ui->tableView_Nip->setColumnWidth(2, 90);
    ui->tableView_Nip->setColumnWidth(3, 90);

    QObject::connect(this,SIGNAL(changedSpoNipParameters(bool)),this,SLOT(on_changedSpoNipParameters(bool)));
}





Dialog_SpoNip::~Dialog_SpoNip()
{
    delete ui;
}





void Dialog_SpoNip::setSpokeParametersL(float thread , float length , float weight , float pieces , QString label)
{
    ui->doubleSpinBox_spokeThreadL->setValue(thread);
    ui->doubleSpinBox_spokeLengthL->setValue(length);
    ui->doubleSpinBox_spokeWeightL->setValue(weight);
    ui->doubleSpinBox_spokePiecesL->setValue(pieces);
    ui->lineEdit_spokeL->setText(label);
}





QString Dialog_SpoNip::getSpokeLabelL(void)
{
    return ui->lineEdit_spokeL->text();
}





float Dialog_SpoNip::getSpokeThreadL_box(void)
{
    return ui->doubleSpinBox_spokeThreadL->value();
}





float Dialog_SpoNip::getSpokeLenghtL_box(void)
{
    return ui->doubleSpinBox_spokeLengthL->value();
}





float Dialog_SpoNip::getSpokeWeightL_box(void)
{
    return ui->doubleSpinBox_spokeWeightL->value();
}





float Dialog_SpoNip::getSpokePiecesL_box(void)
{
    return ui->doubleSpinBox_spokePiecesL->value();
}





void Dialog_SpoNip::setSpokeParametersR(float thread , float length , float weight , float pieces , QString label)
{
    ui->doubleSpinBox_spokeThreadR->setValue(thread);
    ui->doubleSpinBox_spokeLengthR->setValue(length);
    ui->doubleSpinBox_spokeWeightR->setValue(weight);
    ui->doubleSpinBox_spokePiecesR->setValue(pieces);
    ui->lineEdit_spokeR->setText(label);
}





QString Dialog_SpoNip::getSpokeLabelR(void)
{
    return ui->lineEdit_spokeR->text();
}





float Dialog_SpoNip::getSpokeThreadR_box(void)
{
    return ui->doubleSpinBox_spokeThreadR->value();
}





float Dialog_SpoNip::getSpokeLenghtR_box(void)
{
    return ui->doubleSpinBox_spokeLengthR->value();
}





float Dialog_SpoNip::getSpokeWeightR_box(void)
{
    return ui->doubleSpinBox_spokeWeightR->value();
}





float Dialog_SpoNip::getSpokePiecesR_box(void)
{
    return ui->doubleSpinBox_spokePiecesR->value();
}





void Dialog_SpoNip::setNippleParametersL(float thread , float length , float weight , float pieces , QString label)
{
    ui->doubleSpinBox_nippleThreadL->setValue(thread);
    ui->doubleSpinBox_nippleLengthL->setValue(length);
    ui->doubleSpinBox_nippleWeightL->setValue(weight);
    ui->doubleSpinBox_nipplePiecesL->setValue(pieces);
    ui->lineEdit_nippleL->setText(label);
}





QString Dialog_SpoNip::getNippleLabelL(void)
{
    return ui->lineEdit_nippleL->text();
}





float Dialog_SpoNip::getNippleThreadL_box(void)
{
    return ui->doubleSpinBox_nippleThreadL->value();
}





float Dialog_SpoNip::getNippleLenghtL_box(void)
{
    return ui->doubleSpinBox_nippleLengthL->value();
}





float Dialog_SpoNip::getNippleWeightL_box(void)
{
    return ui->doubleSpinBox_nippleWeightL->value();
}





float Dialog_SpoNip::getNipplePiecesL_box(void)
{
    return ui->doubleSpinBox_nipplePiecesL->value();
}





void Dialog_SpoNip::setNippleParametersR(float thread , float length , float weight , float pieces , QString label)
{
    ui->doubleSpinBox_nippleThreadR->setValue(thread);
    ui->doubleSpinBox_nippleLengthR->setValue(length);
    ui->doubleSpinBox_nippleWeightR->setValue(weight);
    ui->doubleSpinBox_nipplePiecesR->setValue(pieces);
    ui->lineEdit_nippleR->setText(label);
}





QString Dialog_SpoNip::getNippleLabelR(void)
{
    return ui->lineEdit_nippleR->text();
}





float Dialog_SpoNip::getNippleThreadR_box(void)
{
    return ui->doubleSpinBox_nippleThreadR->value();
}





float Dialog_SpoNip::getNippleLenghtR_box(void)
{
    return ui->doubleSpinBox_nippleLengthR->value();
}





float Dialog_SpoNip::getNippleWeightR_box(void)
{
    return ui->doubleSpinBox_nippleWeightR->value();
}





float Dialog_SpoNip::getNipplePiecesR_box(void)
{
    return ui->doubleSpinBox_nipplePiecesR->value();
}





void Dialog_SpoNip::setToggle_D_SpoNip()
{
    if (toggle_D_SpoNip)
        {
        this->setGeometry(d_Position);
        this->show();
        }
    else
        {
        d_Position = this->geometry();
        this->hide();
        }
    toggle_D_SpoNip = !toggle_D_SpoNip;
}





void Dialog_SpoNip::on_tableView_Spo_clicked(const QModelIndex &index)
{
    QString             textString;
    int                 row;
    QAbstractItemModel* modelTmp;
    QModelIndex         indexTmp;

    QObject::disconnect(this,SIGNAL(changedSpoNipParameters(bool)),this,SLOT(on_changedSpoNipParameters(bool)));

    row = index.row();
    modelTmp = ui->tableView_Spo->model();

    if (isLeft)
        {
        indexTmp = modelTmp->index(row,0, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->doubleSpinBox_spokeThreadL->setValue(textString.toDouble());

        indexTmp = modelTmp->index(row,1, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->doubleSpinBox_spokeLengthL->setValue(textString.toDouble());

        indexTmp = modelTmp->index(row,2, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->doubleSpinBox_spokeWeightL->setValue(textString.toDouble());

        indexTmp = modelTmp->index(row,3, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->doubleSpinBox_spokePiecesL->setValue(textString.toDouble());

        indexTmp = modelTmp->index(row,4, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->lineEdit_spokeL->setText(textString);
        }
    else
        {
        indexTmp = modelTmp->index(row,0, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->doubleSpinBox_spokeThreadR->setValue(textString.toDouble());

        indexTmp = modelTmp->index(row,1, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->doubleSpinBox_spokeLengthR->setValue(textString.toDouble());

        indexTmp = modelTmp->index(row,2, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->doubleSpinBox_spokeWeightR->setValue(textString.toDouble());

        indexTmp = modelTmp->index(row,3, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->doubleSpinBox_spokePiecesR->setValue(textString.toDouble());

        indexTmp = modelTmp->index(row,4, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->lineEdit_spokeR->setText(textString);
        }

    QObject::connect(this,SIGNAL(changedSpoNipParameters(bool)),this,SLOT(on_changedSpoNipParameters(bool)));
    emit changedSpoNipParameters (true);
}





void Dialog_SpoNip::on_tableView_Nip_clicked(const QModelIndex &index)
{
    QString             textString;
    int                 row;
    QAbstractItemModel* modelTmp;
    QModelIndex         indexTmp;

    QObject::disconnect(this,SIGNAL(changedSpoNipParameters(bool)),this,SLOT(on_changedSpoNipParameters(bool)));

    row = index.row();
    modelTmp = ui->tableView_Nip->model();

    if (isLeft)
        {
        indexTmp = modelTmp->index(row,0, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->doubleSpinBox_nippleThreadL->setValue(textString.toDouble());

        indexTmp = modelTmp->index(row,1, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->doubleSpinBox_nippleLengthL->setValue(textString.toDouble());

        indexTmp = modelTmp->index(row,2, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->doubleSpinBox_nippleWeightL->setValue(textString.toDouble());

        indexTmp = modelTmp->index(row,3, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->doubleSpinBox_nipplePiecesL->setValue(textString.toDouble());

        indexTmp = modelTmp->index(row,4, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->lineEdit_nippleL->setText(textString);
        }
    else
        {
        indexTmp = modelTmp->index(row,0, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->doubleSpinBox_nippleThreadR->setValue(textString.toDouble());

        indexTmp = modelTmp->index(row,1, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->doubleSpinBox_nippleLengthR->setValue(textString.toDouble());

        indexTmp = modelTmp->index(row,2, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->doubleSpinBox_nippleWeightR->setValue(textString.toDouble());

        indexTmp = modelTmp->index(row,3, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->doubleSpinBox_nipplePiecesR->setValue(textString.toDouble());

        indexTmp = modelTmp->index(row,4, QModelIndex());
        textString= modelTmp->data(indexTmp).toString();
        ui->lineEdit_nippleR->setText(textString);
        }

    QObject::connect(this,SIGNAL(changedSpoNipParameters(bool)),this,SLOT(on_changedSpoNipParameters(bool)));
    emit changedSpoNipParameters (true);
}





void Dialog_SpoNip::on_pushButton_spoAdd_clicked()
{
    QStandardItem*          item;
    QStandardItemModel*     modelTmp;
    QList<QStandardItem *>  listItem;

        modelTmp = static_cast<QStandardItemModel*>(ui->tableView_Spo->model());

    if (isLeft)
        {
        item = new QStandardItem(QString::number(ui->doubleSpinBox_spokeThreadL->value(), 'f', 2));
        item->setTextAlignment(Qt::AlignCenter);
        listItem.append(item);

        item = new QStandardItem(QString::number(ui->doubleSpinBox_spokeLengthL->value(), 'f', 2));
        item->setTextAlignment(Qt::AlignCenter);
        listItem.append(item);

        item = new QStandardItem(QString::number(ui->doubleSpinBox_spokeWeightL->value(), 'f', 2));
        item->setTextAlignment(Qt::AlignCenter);
        listItem.append(item);

        item = new QStandardItem(QString::number(ui->doubleSpinBox_spokePiecesL->value(), 'f', 2));
        item->setTextAlignment(Qt::AlignCenter);
        listItem.append(item);

        item = new QStandardItem(ui->lineEdit_spokeL->text());
        listItem.append(item);
        }
    else
        {
        item = new QStandardItem(QString::number(ui->doubleSpinBox_spokeThreadR->value(), 'f', 2));
        item->setTextAlignment(Qt::AlignCenter);
        listItem.append(item);

        item = new QStandardItem(QString::number(ui->doubleSpinBox_spokeLengthR->value(), 'f', 2));
        item->setTextAlignment(Qt::AlignCenter);
        listItem.append(item);

        item = new QStandardItem(QString::number(ui->doubleSpinBox_spokeWeightR->value(), 'f', 2));
        item->setTextAlignment(Qt::AlignCenter);
        listItem.append(item);

        item = new QStandardItem(QString::number(ui->doubleSpinBox_spokePiecesR->value(), 'f', 2));
        item->setTextAlignment(Qt::AlignCenter);
        listItem.append(item);

        item = new QStandardItem(ui->lineEdit_spokeR->text());
        listItem.append(item);
        }

    modelTmp->appendRow(listItem);
}





void Dialog_SpoNip::on_pushButton_nipAdd_clicked()
{
    QStandardItem*          item;
    QStandardItemModel*     modelTmp;
    QList<QStandardItem *>  listItem;

        modelTmp = static_cast<QStandardItemModel*>(ui->tableView_Nip->model());

    if (isLeft)
        {
        item = new QStandardItem(QString::number(ui->doubleSpinBox_nippleThreadL->value(), 'f', 2));
        item->setTextAlignment(Qt::AlignCenter);
        listItem.append(item);

        item = new QStandardItem(QString::number(ui->doubleSpinBox_nippleLengthL->value(), 'f', 2));
        item->setTextAlignment(Qt::AlignCenter);
        listItem.append(item);

        item = new QStandardItem(QString::number(ui->doubleSpinBox_nippleWeightL->value(), 'f', 2));
        item->setTextAlignment(Qt::AlignCenter);
        listItem.append(item);

        item = new QStandardItem(QString::number(ui->doubleSpinBox_nipplePiecesL->value(), 'f', 2));
        item->setTextAlignment(Qt::AlignCenter);
        listItem.append(item);

        item = new QStandardItem(ui->lineEdit_nippleL->text());
        listItem.append(item);
        }
    else
        {
        item = new QStandardItem(QString::number(ui->doubleSpinBox_nippleThreadR->value(), 'f', 2));
        item->setTextAlignment(Qt::AlignCenter);
        listItem.append(item);

        item = new QStandardItem(QString::number(ui->doubleSpinBox_nippleLengthR->value(), 'f', 2));
        item->setTextAlignment(Qt::AlignCenter);
        listItem.append(item);

        item = new QStandardItem(QString::number(ui->doubleSpinBox_nippleWeightR->value(), 'f', 2));
        item->setTextAlignment(Qt::AlignCenter);
        listItem.append(item);

        item = new QStandardItem(QString::number(ui->doubleSpinBox_nipplePiecesR->value(), 'f', 2));
        item->setTextAlignment(Qt::AlignCenter);
        listItem.append(item);

        item = new QStandardItem(ui->lineEdit_nippleR->text());
        listItem.append(item);
        }

    modelTmp->appendRow(listItem);
}





void Dialog_SpoNip::on_pushButton_spoDel_clicked()
{
    QModelIndexList         selection;

    selection = ui->tableView_Spo->selectionModel()->selectedRows();
    qSort(selection.begin() , selection.end() , qGreater<QModelIndex>());
    for(QModelIndexList::Iterator it = selection.begin() ; it != selection.end() ; it++)
        {
        ui->tableView_Spo->model()->removeRow(it->row());
        }
    ui->tableView_Spo->clearSelection();
}





void Dialog_SpoNip::on_pushButton_nipDel_clicked()
{
    QModelIndexList         selection;

    selection = ui->tableView_Nip->selectionModel()->selectedRows();
    qSort(selection.begin() , selection.end() , qGreater<QModelIndex>());
    for(QModelIndexList::Iterator it = selection.begin() ; it != selection.end() ; it++)
        {
        ui->tableView_Nip->model()->removeRow(it->row());
        }
    ui->tableView_Nip->clearSelection();
}





void Dialog_SpoNip::on_pushButton_spoSave_clicked()
{
    QString textData;
    QString textTmp;
    int     rows;
    int     columns;

    rows = ui->tableView_Spo->model()->rowCount();
    columns = ui->tableView_Spo->model()->columnCount();

    for (int i = 0; i < rows; i++)
        {
        for (int j = 0; j < columns; j++)
            {
            textTmp = ui->tableView_Spo->model()->data(ui->tableView_Spo->model()->index(i,j)).toString();
            textTmp.replace(',','.');
            textData += textTmp;
            textData += ",";
            }
        textData.chop(1);
        textData += "\n";
        }

    QFile csvFile("listspoke.csv");
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
        QTextStream out(&csvFile);
        out << textData;
        csvFile.close();
        }
}





void Dialog_SpoNip::on_pushButton_nipSave_clicked()
{
    QString textData;
    QString textTmp;
    int     rows;
    int     columns;

    rows = ui->tableView_Nip->model()->rowCount();
    columns = ui->tableView_Nip->model()->columnCount();

    for (int i = 0; i < rows; i++)
        {
        for (int j = 0; j < columns; j++)
            {
            textTmp = ui->tableView_Nip->model()->data(ui->tableView_Nip->model()->index(i,j)).toString();
            textTmp.replace(',','.');
            textData += textTmp;
            textData += ",";
            }
        textData.chop(1);
        textData += "\n";
        }

    QFile csvFile("listnipple.csv");
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
        QTextStream out(&csvFile);
        out << textData;
        csvFile.close();
        }
}





void Dialog_SpoNip::on_doubleSpinBox_spokeThreadL_valueChanged(double arg1)
{
    emit changedSpoNipParameters (false);
    arg1++;
}





void Dialog_SpoNip::on_doubleSpinBox_spokeLengthL_valueChanged(double arg1)
{
    emit changedSpoNipParameters (false);
    arg1++;
}





void Dialog_SpoNip::on_doubleSpinBox_spokeWeightL_valueChanged(double arg1)
{
    emit changedSpoNipParameters (false);
    arg1++;
}





void Dialog_SpoNip::on_doubleSpinBox_spokePiecesL_valueChanged(double arg1)
{
    emit changedSpoNipParameters (false);
    arg1++;
}





void Dialog_SpoNip::on_lineEdit_spokeL_returnPressed()
{
    emit changedSpoNipParameters (false);
    this->focusNextChild();
}





void Dialog_SpoNip::on_doubleSpinBox_spokeThreadR_valueChanged(double arg1)
{
    emit changedSpoNipParameters (false);
    arg1++;
}





void Dialog_SpoNip::on_doubleSpinBox_spokeLengthR_valueChanged(double arg1)
{
    emit changedSpoNipParameters (false);
    arg1++;
}





void Dialog_SpoNip::on_doubleSpinBox_spokeWeightR_valueChanged(double arg1)
{
    emit changedSpoNipParameters (false);
    arg1++;
}





void Dialog_SpoNip::on_doubleSpinBox_spokePiecesR_valueChanged(double arg1)
{
    emit changedSpoNipParameters (false);
    arg1++;
}




void Dialog_SpoNip::on_lineEdit_spokeR_returnPressed()
{
    emit changedSpoNipParameters (false);
    this->focusNextChild();
}





void Dialog_SpoNip::on_doubleSpinBox_nippleThreadL_valueChanged(double arg1)
{
    emit changedSpoNipParameters (false);
    arg1++;
}





void Dialog_SpoNip::on_doubleSpinBox_nippleLengthL_valueChanged(double arg1)
{
    emit changedSpoNipParameters (false);
    arg1++;
}





void Dialog_SpoNip::on_doubleSpinBox_nippleWeightL_valueChanged(double arg1)
{
    emit changedSpoNipParameters (false);
    arg1++;
}





void Dialog_SpoNip::on_doubleSpinBox_nipplePiecesL_valueChanged(double arg1)
{
    emit changedSpoNipParameters (false);
    arg1++;
}





void Dialog_SpoNip::on_lineEdit_nippleL_returnPressed()
{
    emit changedSpoNipParameters (false);
    this->focusNextChild();
}





void Dialog_SpoNip::on_doubleSpinBox_nippleThreadR_valueChanged(double arg1)
{
    emit changedSpoNipParameters (false);
    arg1++;
}





void Dialog_SpoNip::on_doubleSpinBox_nippleLengthR_valueChanged(double arg1)
{
    emit changedSpoNipParameters (false);
    arg1++;
}





void Dialog_SpoNip::on_doubleSpinBox_nippleWeightR_valueChanged(double arg1)
{
    emit changedSpoNipParameters (false);
    arg1++;
}





void Dialog_SpoNip::on_doubleSpinBox_nipplePiecesR_valueChanged(double arg1)
{
    emit changedSpoNipParameters (false);
    arg1++;
}





void Dialog_SpoNip::on_lineEdit_nippleR_returnPressed()
{
    emit changedSpoNipParameters (false);
    this->focusNextChild();
}





void Dialog_SpoNip::on_groupBox_SpoL_toggled(bool arg1)
{
    if (arg1)
        {
        isLeft = true;
        ui->groupBox_SpoR->setChecked(false);
        ui->groupBox_NipL->setChecked(true);
        ui->groupBox_NipR->setChecked(false);
        }
    else
        {
        isLeft = false;
        ui->groupBox_SpoR->setChecked(true);
        ui->groupBox_NipL->setChecked(false);
        ui->groupBox_NipR->setChecked(true);
        }
}





void Dialog_SpoNip::on_groupBox_SpoR_toggled(bool arg1)
{
    if (arg1)
        {
        isLeft = false;
        ui->groupBox_SpoL->setChecked(false);
        ui->groupBox_NipL->setChecked(false);
        ui->groupBox_NipR->setChecked(true);
        }
    else
        {
        isLeft = true;
        ui->groupBox_SpoL->setChecked(true);
        ui->groupBox_NipL->setChecked(true);
        ui->groupBox_NipR->setChecked(false);
        }
}





void Dialog_SpoNip::on_groupBox_NipL_toggled(bool arg1)
{
    if (arg1)
        {
        isLeft = true;
        ui->groupBox_SpoL->setChecked(true);
        ui->groupBox_SpoR->setChecked(false);
        ui->groupBox_NipR->setChecked(false);
        }
    else
        {
        isLeft = false;
        ui->groupBox_SpoL->setChecked(false);
        ui->groupBox_SpoR->setChecked(true);
        ui->groupBox_NipR->setChecked(true);
        }
}





void Dialog_SpoNip::on_groupBox_NipR_toggled(bool arg1)
{
    if (arg1)
        {
        isLeft = false;
        ui->groupBox_SpoL->setChecked(false);
        ui->groupBox_SpoR->setChecked(true);
        ui->groupBox_NipL->setChecked(false);
        }
    else
        {
        isLeft = true;
        ui->groupBox_SpoL->setChecked(true);
        ui->groupBox_SpoR->setChecked(false);
        ui->groupBox_NipL->setChecked(true);
    }
}





void Dialog_SpoNip::on_changedSpoNipParameters(bool isFromStart)
{
    emit changedParameters (isFromStart);
}





bool Dialog_SpoNip::eventFilter(QObject *obj, QEvent *event)
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





void Dialog_SpoNip::closeEvent(QCloseEvent *event)
{
    d_Position = this->geometry();
    toggle_D_SpoNip = true;
    event->accept();
}
