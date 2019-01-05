#include <dialog_results.h>
#include <ui_dialog_results.h>

#include <QStandardItemModel>
#include <QCloseEvent>
#include <QDebug>
#include <QFileDialog>
#include <QTextCursor>
#include <QTextTableCell>
#include <QMessageBox>





Dialog_Results::Dialog_Results(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Results)
{
    ui->setupUi(this);

    ui->doubleSpinBox_flangeThickness->installEventFilter(this);
    ui->doubleSpinBox_load->installEventFilter(this);
    ui->doubleSpinBox_young->installEventFilter(this);
    ui->doubleSpinBox_density->installEventFilter(this);

    d_Position = this->geometry();
    toggle_D_Results = true;

    resolutionPrint = 600;
    resolutionScale = (resolutionPrint/96.0);

    printer = new QPrinter;
    printer->setResolution(resolutionPrint);
    printer->setPaperSize(QPrinter::A4);
    printer->setOrientation(QPrinter::Portrait);
    printer->setPageMargins(15,15,15,15,QPrinter::Millimeter);
    printer->setOutputFormat(QPrinter::PdfFormat);

    QFont textFont6N("Noto Sans",6*resolutionScale,QFont::Normal);
    QTextOption option;
    option.setWrapMode(QTextOption::NoWrap);
    doc.setDefaultTextOption(option);
    doc.setDefaultFont(textFont6N);
}





Dialog_Results::~Dialog_Results()
{
    delete ui;
}





void Dialog_Results::setResultsParameters(float thickness, float load, float young, float specificVolume,
                                          bool isAlternatingL, bool isAlternatingR, bool isHOutL, bool isHOutR, bool isSPullL, bool isSPullR,
                                          float meanAngleL, float meanAngleR, float meanForceL, float meanForceR, float meanElongationL, float meanElongationR,
                                          float weightHub, float weightRim, float weightSpokes,float  weightNipples)
{
    int index;

    density = 1000000.0/specificVolume;

    index = 0;
    if (isAlternatingL || isSPullL)
        index = 0;
    else if (isHOutL)
        index = 1;
    else
        index = 2;
    ui->comboBox_spokeHeadsL->setCurrentIndex(index);

    index = 0;
    if (isAlternatingR || isSPullR)
        index = 0;
    else if (isHOutR)
        index = 1;
    else
        index = 2;
    ui->comboBox_spokeHeadsR->setCurrentIndex(index);

    ui->doubleSpinBox_flangeThickness->setValue(thickness);
    ui->doubleSpinBox_load->setValue(load);
    ui->doubleSpinBox_young->setValue(young);
    ui->doubleSpinBox_density->setValue(density);

    ui->doubleSpinBox_meanAngleL->setValue(meanAngleL);
    ui->doubleSpinBox_meanAngleR->setValue(meanAngleR);;
    ui->doubleSpinBox_meanLoadL->setValue(meanForceL);;
    ui->doubleSpinBox_meanLoadR->setValue(meanForceR);;
    ui->spinBox_rimWeight->setValue(weightRim);;
    ui->spinBox_hubWeight->setValue(weightHub);;
    ui->spinBox_spokesWeight->setValue(weightSpokes);;
    ui->spinBox_nipplesWeight->setValue(weightNipples);;
    ui->spinBox_totalWeight->setValue(weightRim+weightHub+weightSpokes+weightNipples);;
    ui->doubleSpinBox_meanElonL->setValue(meanElongationL);;
    ui->doubleSpinBox_meanElonR->setValue(meanElongationR);;
}





float Dialog_Results::getThickess_box()
{
    return ui->doubleSpinBox_flangeThickness->value();
}





float Dialog_Results::getLoad_box()
{
    return ui->doubleSpinBox_load->value();
}





float Dialog_Results::getYoung_box()
{
    return ui->doubleSpinBox_young->value();
}





float Dialog_Results::getSpecificVolume()
{
    return 1000000.0/(density);
}





int Dialog_Results::getHeadsL()
{
    return ui->comboBox_spokeHeadsL->currentIndex();
}





int Dialog_Results::getHeadsR()
{
    return ui->comboBox_spokeHeadsR->currentIndex();
}





void Dialog_Results::setTable(QStandardItemModel *model)
{
    ui->tableView_Results->setModel(model);

    ui->tableView_Results->setColumnWidth(0, 90);
    ui->tableView_Results->setColumnWidth(1, 40);
    ui->tableView_Results->setColumnWidth(2, 90);
    ui->tableView_Results->setColumnWidth(3, 90);
    ui->tableView_Results->setColumnWidth(4, 90);
    ui->tableView_Results->setColumnWidth(5, 90);
    ui->tableView_Results->setColumnWidth(6, 90);
    ui->tableView_Results->setColumnWidth(7, 90);
    ui->tableView_Results->setColumnWidth(8, 90);
    ui->tableView_Results->setColumnWidth(9, 90);
}





void Dialog_Results::setDocLabels(QString hublabel, QString rimlabel, QString spokeslabelL, QString spokeslabelR, QString nippleslabelL, QString nippleslabelR)
{
    labelHub = hublabel;
    labelRim = rimlabel;
    labelSpL = spokeslabelL;
    labelSpR = spokeslabelR;
    labelNiL = nippleslabelL;
    labelNiR = nippleslabelR;
}





void Dialog_Results::setDocImg(QImage *imgAxial, QImage *imgRadial)
{
    imageAxial  = imgAxial;
    imageRadial = imgRadial;
}





void Dialog_Results::setToggle_D_Results()
{
    if (toggle_D_Results)
    {
    this->setGeometry(d_Position);
    this->show();
    }
else
    {
    d_Position = this->geometry();
    this->hide();
    }
    toggle_D_Results = !toggle_D_Results;
}





void Dialog_Results::on_doubleSpinBox_flangeThickness_valueChanged(double arg1)
{
    emit changedParameters (false);
    arg1++;
}





void Dialog_Results::on_doubleSpinBox_load_valueChanged(double arg1)
{
    emit changedParameters (false);
    arg1++;
}





void Dialog_Results::on_doubleSpinBox_young_valueChanged(double arg1)
{
    emit changedParameters (false);
    arg1++;
}





void Dialog_Results::on_doubleSpinBox_density_valueChanged(double arg1)
{
    density = arg1;
    emit changedParameters (false);
}





void Dialog_Results::on_comboBox_spokeHeadsL_currentIndexChanged(int index)
{
    emit changedParameters (false);
    index++;
}





void Dialog_Results::on_comboBox_spokeHeadsR_currentIndexChanged(int index)
{
    emit changedParameters (false);
    index++;
}





bool Dialog_Results::eventFilter(QObject *obj, QEvent *event)
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





void Dialog_Results::closeEvent(QCloseEvent *event)
{
    d_Position = this->geometry();
    toggle_D_Results = true;
    event->accept();
}





void Dialog_Results::on_Button_loadWheel_clicked()
{
    QString         openWheelFile;

    openWheelFile = QFileDialog::getOpenFileName(this , "Load Wheel" , QDir::currentPath() , "Wheel File (*.spq)");
    if (openWheelFile != "")
        {
        emit loadWheel(openWheelFile);
        }
}





void Dialog_Results::on_Button_saveWheel_clicked()
{
    QString         saveWheelFile;

    saveWheelFile = QFileDialog::getSaveFileName(this , "Save Wheel" , QDir::currentPath() , "Wheel File (*.spq)");
    if (saveWheelFile != "")
        {
        emit saveWheel(saveWheelFile);
        }
}





void Dialog_Results::on_Button_Print_clicked()
{
    int                     columns;
    int                     rows;
    float                   value;
    QImage                  imgAxial;
    QImage                  imgRadial;
    QStandardItemModel      *modelTmp;
    QStandardItem           *item;
    QTextTableCell          cell;
    QTextCursor             cursor(&doc);
    QTextCursor             cellCursor;
    QTextCharFormat         textFormat;
    QTextBlockFormat        blockFormat;
    QTextTableFormat        tableFormat;

    columns   = ui->tableView_Results->model()->columnCount();
    rows      = ui->tableView_Results->model()->rowCount();
    modelTmp  = static_cast<QStandardItemModel*>(ui->tableView_Results->model());

    emit imageRequest();
    imgAxial  = *imageAxial;
    imgRadial = *imageRadial;

    QFont textFont7B("Noto Sans",7*resolutionScale,QFont::Bold);

    doc.clear();


    //  GRAPH
    tableFormat.setAlignment(Qt::AlignLeft);
    tableFormat.setCellPadding(10);
    tableFormat.setCellSpacing(0);
    tableFormat.setMargin(0);
    tableFormat.setBorder(0);
    QTextTable *graphTable = cursor.insertTable(1,2,tableFormat);
    cell = graphTable->cellAt(0,0);
    cellCursor = cell.firstCursorPosition();
    imgAxial = imgAxial.scaledToWidth(printer->pageRect().width()*(4.0/5.0),Qt::SmoothTransformation);
    cellCursor.insertImage(imgAxial);
    cell = graphTable->cellAt(0,1);
    cellCursor = cell.firstCursorPosition();
    imgRadial = imgRadial.scaledToWidth(printer->pageRect().width()*(1.0/5.0),Qt::SmoothTransformation);
    cellCursor.insertImage(imgRadial);
    cellCursor.insertBlock();
    cursor.movePosition(QTextCursor::End);


// MAIN TABLE
    tableFormat.setAlignment(Qt::AlignLeft);
    tableFormat.setCellPadding(0);
    tableFormat.setCellSpacing(0);
    tableFormat.setMargin(0);
    tableFormat.setBorder(0);
    QTextTable *mainTable = cursor.insertTable(1,2,tableFormat);
    cell = mainTable->cellAt(0,0);
    cursor = cell.lastCursorPosition();


    //  MAIN TABLE 0,0
    // SPOKES
    tableFormat.setHeaderRowCount(1);
    tableFormat.setAlignment(Qt::AlignLeft);
    tableFormat.setCellPadding(0);
    tableFormat.setCellSpacing(0);
    tableFormat.setMargin(0);
    tableFormat.setBorder(0);
    textFormat.setFont(textFont7B);
    textFormat.setBackground(Qt::lightGray);
    QTextTable *textTable = cursor.insertTable(rows + 1, columns, tableFormat);
    for (int i = 0; i < columns; i++)
        {
        cell = textTable->cellAt(0,i);
        cell.setFormat(textFormat);
        cellCursor = cell.firstCursorPosition();
        blockFormat = cellCursor.blockFormat();
        blockFormat.setLeftMargin(5*resolutionScale);
        blockFormat.setRightMargin(5*resolutionScale);
        blockFormat.setAlignment(Qt::AlignHCenter);
        cellCursor.setBlockFormat(blockFormat);
        if (modelTmp->horizontalHeaderItem(i) || !(modelTmp->horizontalHeaderItem(i)->text().isEmpty()))
            cellCursor.insertText(modelTmp->horizontalHeaderItem(i)->data(Qt::DisplayRole).toString());
        }
    textFormat.setFont(doc.defaultFont());
    textFormat.setBackground(Qt::transparent);
    for (int i = 0; i < rows; i++)
        {
        for (int j = 0; j < columns; j++)
            {
            item = modelTmp->item(i,j);
            cell = textTable->cellAt(i+1,j);
            cell.setFormat(textFormat);
            cellCursor = cell.firstCursorPosition();
            blockFormat = cellCursor.blockFormat();
            blockFormat.setLeftMargin(10*resolutionScale);
            blockFormat.setRightMargin(10*resolutionScale);
            cellCursor.setBlockFormat(blockFormat);
            if (item || !(item->text().isEmpty()))
                {
                value = modelTmp->item(i,j)->text().toFloat();
                value = round(100.0*value)/100.0;
                if (j != 1)
                    cellCursor.insertText(QString::number(value));
                else
                    cellCursor.insertText(modelTmp->item(i,j)->text());
                }
            }
        }
    cursor.movePosition(QTextCursor::End);


    cell = mainTable->cellAt(0,1);
    cursor = cell.lastCursorPosition();


    //  MAIN TABLE 0,1
    tableFormat.setAlignment(Qt::AlignLeft);
    tableFormat.setCellPadding(0);
    tableFormat.setCellSpacing(0);
    tableFormat.setMargin(0);
    tableFormat.setBorder(0);
    QTextTable *resultsTable = cursor.insertTable(25,2,tableFormat);


    //  COMPONENTS
    resultsTable->mergeCells(0,0,1,2);
    cell = resultsTable->cellAt(0,0);
    textFormat.setFont(textFont7B);
    cell.setFormat(textFormat);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignCenter);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("COMPONENTS");

    cell = resultsTable->cellAt(1,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Rim: ");

    cell = resultsTable->cellAt(2,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Hub: ");

    cell = resultsTable->cellAt(3,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Spokes Left: ");

    cell = resultsTable->cellAt(4,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Spokes Right: ");

    cell = resultsTable->cellAt(5,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Nipples Left: ");

    cell = resultsTable->cellAt(6,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Nipples Right: ");

    cell = resultsTable->cellAt(1,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(labelRim);

    cell = resultsTable->cellAt(2,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(labelHub);

    cell = resultsTable->cellAt(3,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(labelSpL);

    cell = resultsTable->cellAt(4,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(labelSpR);

    cell = resultsTable->cellAt(5,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(labelNiL);

    cell = resultsTable->cellAt(6,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(labelNiR);
    cursor.movePosition(QTextCursor::End);


    //  WEIGHT
    resultsTable->mergeCells(8,0,1,2);
    cell = resultsTable->cellAt(8,0);
    textFormat.setFont(textFont7B);
    cell.setFormat(textFormat);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignCenter);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("WEIGHT");

    cell = resultsTable->cellAt(9,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Rim: ");

    cell = resultsTable->cellAt(10,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Hub: ");

    cell = resultsTable->cellAt(11,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Spokes: ");

    cell = resultsTable->cellAt(12,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Nipples: ");

    cell = resultsTable->cellAt(13,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Total Weight: ");


    cell = resultsTable->cellAt(9,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(QString::number(ui->spinBox_rimWeight->value())+"g");

    cell = resultsTable->cellAt(10,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(QString::number(ui->spinBox_hubWeight->value())+"g");

    cell = resultsTable->cellAt(11,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(QString::number(ui->spinBox_spokesWeight->value())+"g");

    cell = resultsTable->cellAt(12,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(QString::number(ui->spinBox_nipplesWeight->value())+"g");

    cell = resultsTable->cellAt(13,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(QString::number(ui->spinBox_totalWeight->value())+"g");
    cursor.movePosition(QTextCursor::End);


    //  TENSION ELONGATION
    resultsTable->mergeCells(15,0,1,2);
    cell = resultsTable->cellAt(15,0);
    textFormat.setFont(textFont7B);
    cell.setFormat(textFormat);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignCenter);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("MEAN VALUES");

    cell = resultsTable->cellAt(16,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Nominal Load: ");

    cell = resultsTable->cellAt(17,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Left Load: ");

    cell = resultsTable->cellAt(18,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Right Load: ");

    cell = resultsTable->cellAt(20,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Left Elongation: ");

    cell = resultsTable->cellAt(21,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Right Elongation: ");

    cell = resultsTable->cellAt(23,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Left Bracing Angle: ");

    cell = resultsTable->cellAt(24,0);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText("Right Bracing Angle: ");

    cell = resultsTable->cellAt(16,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(QString::number(ui->doubleSpinBox_load->value())+"N");

    cell = resultsTable->cellAt(17,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(QString::number(ui->doubleSpinBox_meanLoadL->value())+"N");

    cell = resultsTable->cellAt(18,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(QString::number(ui->doubleSpinBox_meanLoadR->value())+"N");

    cell = resultsTable->cellAt(20,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(QString::number(ui->doubleSpinBox_meanElonL->value())+"mm");

    cell = resultsTable->cellAt(21,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(QString::number(ui->doubleSpinBox_meanElonR->value())+"mm");

    cell = resultsTable->cellAt(23,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(QString::number(ui->doubleSpinBox_meanAngleL->value())+"°");

    cell = resultsTable->cellAt(24,1);
    cellCursor = cell.firstCursorPosition();
    blockFormat = cellCursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignLeft);
    cellCursor.setBlockFormat(blockFormat);
    cellCursor.insertText(QString::number(ui->doubleSpinBox_meanAngleR->value())+"°");
    cursor.movePosition(QTextCursor::End);

    QPrintDialog dialog(printer, this);
    dialog.setWindowTitle(("Print Document"));

    if (dialog.exec() == QDialog::Accepted)
        {
        doc.setPageSize(printer->pageRect().size());
        doc.print(printer);
        }
}





void Dialog_Results::PreviewPaintRequested(QPrinter* printerP)
{
    doc.setPageSize(printerP->pageRect().size());
    doc.print(printerP);
}
