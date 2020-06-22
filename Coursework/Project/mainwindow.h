#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "new_user.h"
#include <QStringList>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:




    void on_Choice_of_products_clicked();

    void on_Delete_Button_clicked();

    void on_to_Change_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void sum();

    void on_action_triggered();

    void on_new_user_triggered();

private:

    Ui::MainWindow *ui;
    QString meat="Мясо",bread="Хлебобулочные изд.",seafood="Морепродукты",dairy_produce="Молочные продукты",
    fruits_and_berries="Фрукты и ягоды",vegetables="Овощи",cereal="Крупы",Mushrooms_and_nuts="Грибы и орехи";
};
#endif // MAINWINDOW_H
