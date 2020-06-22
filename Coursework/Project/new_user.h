#ifndef NEW_USER_H
#define NEW_USER_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class New_User;
}

class New_User : public QDialog
{
    Q_OBJECT

public:
    explicit New_User(QWidget *parent = nullptr);
    ~New_User();

private slots:
     //void closeEvent(QCloseEvent *event);

    void on_pushButton_2_clicked();

    double coefficient(double,int);

    void on_VIBOR_clicked();

    void on_Delete_Button_clicked();

private:
    Ui::New_User *ui;

};

#endif // NEW_USER_H
