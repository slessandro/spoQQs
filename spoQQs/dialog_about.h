#ifndef DIALOG_ABOUT_H
#define DIALOG_ABOUT_H

#include <QDialog>

namespace Ui {
class Dialog_About;
}

class Dialog_About : public QDialog
{
    Q_OBJECT


private:
    bool            toggle_D_About;
    QRect           d_Position;


public:
    explicit Dialog_About(QWidget *parent = 0);
    ~Dialog_About();

    void    setToggle_D_About();


private:
    Ui::Dialog_About *ui;
};

#endif // DIALOG_ABOUT_H
