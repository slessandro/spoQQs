#include <dialog_about.h>
#include <ui_dialog_about.h>





Dialog_About::Dialog_About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_About)
{
    ui->setupUi(this);

    d_Position = this->geometry();
    toggle_D_About = true;
}





Dialog_About::~Dialog_About()
{
    delete ui;
}





void Dialog_About::setToggle_D_About()
{
    if (toggle_D_About)
        {
        this->setGeometry(d_Position);
        this->show();
        }
    else
        {
        d_Position = this->geometry();
        this->hide();
        }
    toggle_D_About = !toggle_D_About;
}
