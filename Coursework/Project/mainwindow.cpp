#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QtGui>
#include <QMessageBox>
#include <QtWidgets>
#include "help.h"
#include "new_user.h"
// https://youtu.be/kOVUovnj4lg
double plus(double item){//допустимая погрешность в 10%
    return item + (item  *0.1);
}
double minus (double item){
    return item - (item * 0.1);
}

void MainWindow::sum(){
    QString water;
    double water_d;
    for(int j = 1;j!=7;j++){
        water_d=0;
        for(int i=0;i<10;i++){
            if(ui->tableWidget_2->item(i,j)==0)
                break;
            water=ui->tableWidget_2->item(i,j)->text();
            water_d+=water.toDouble();
             }
        water = QString::number(water_d);
        ui->tableResult->setItem(0,j-1,new QTableWidgetItem(water));
      }
    QString recommendation_protein = ui->table_recom->item(0,0)->text(), result_protein = ui->tableResult->item(0,1)->text() ,
            recommendation_fat = ui->table_recom->item(0,1)->text(), result_fat = ui->tableResult->item(0,2)->text(),
            recommendation_carbohydrates = ui->table_recom->item(0,2)->text(), result_carbohydrates = ui->tableResult->item(0,3)->text(),
            recommendation_calories = ui->table_recom->item(0,3)->text(), result_calories = ui->tableResult->item(0,4)->text();
    double  Drecommendation_protein = recommendation_protein.toDouble(), Dresult_protein = result_protein.toDouble(),
            Drecommendation_fat = recommendation_fat.toDouble(), Dresult_fat = result_fat.toDouble(),
            Drecommendation_carbohydrates = recommendation_carbohydrates.toDouble(), Dresult_carbohydrates = result_carbohydrates.toDouble(),
            Drecommendation_calories = recommendation_calories.toDouble(), Dresult_calories = result_calories.toDouble();
    if(Drecommendation_protein > plus(Dresult_protein) || Drecommendation_protein < minus(Dresult_protein)){
        ui->tableResult->item(0,1)->setBackground(Qt::red);
     }
    else{ui->tableResult->item(0,1)->setBackground(Qt::green);}
    if(Drecommendation_fat > plus(Dresult_fat) || Drecommendation_fat < minus(Dresult_fat)){
        ui->tableResult->item(0,2)->setBackground(Qt::red);
     }
    else{ui->tableResult->item(0,2)->setBackground(Qt::green);}
    if(Drecommendation_carbohydrates > plus(Dresult_carbohydrates) || Drecommendation_carbohydrates < minus(Dresult_carbohydrates)){
        ui->tableResult->item(0,3)->setBackground(Qt::red);
     }
    else{ui->tableResult->item(0,3)->setBackground(Qt::green);}
    if(Drecommendation_calories > plus(Dresult_calories) || Drecommendation_calories < minus(Dresult_calories)){
        ui->tableResult->item(0,4)->setBackground(Qt::red);
     }
    else{ui->tableResult->item(0,4)->setBackground(Qt::green);}
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   QPalette Pal(palette());
   QImage background2(":/IMG/background.png");
       Pal.setBrush(QPalette::Background, background2);
       this->setAutoFillBackground(true);
       this->setPalette(Pal);
       New_User window;
       window.setModal(true);
       window.exec();
       ui->table_recom->setColumnCount(4);
       ui->table_recom->setRowCount(1);
       ui->table_recom->setHorizontalHeaderLabels(QStringList()<<"Белки"<<"Жиры"<<"Углеводы"<<"Калории");
       ui->tableWidget->horizontalHeader()->setDefaultSectionSize(106);
       ui->tableWidget_2->horizontalHeader()->setDefaultSectionSize(94);
       ui->tableResult->horizontalHeader()->setDefaultSectionSize(80);
       ui->tableWidget->setColumnCount(6);
       ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Продукт"<<"Вода"<<"Белки"<<"Жиры"<<"Углеводы"<<"Калории");
       ui->tableWidget_2->setColumnCount(7);
       ui->tableWidget_2->setHorizontalHeaderLabels(QStringList()<<"Продукт"<<"Вода"<<"Белки"<<"Жиры"<<"Углеводы"<<"Калории"<<"Грамм");
       ui->tableResult->setColumnCount(6);
       ui->tableResult->setRowCount(1);
       ui->tableResult->setHorizontalHeaderLabels(QStringList()<<"Вода"<<"Белки"<<"Жиры"<<"Углеводы"<<"Калории"<<"Грамм");
       ui->Choice_of_products->setEnabled(false);
       ui->comboBox->addItem("Хлебобулочные изд.");
       ui->comboBox->addItem("Мясо");
       ui->comboBox->addItem("Морепродукты");
       ui->comboBox->addItem("Молочные продукты");
       ui->comboBox->addItem("Фрукты и ягоды");
       ui->comboBox->addItem("Овощи");
       ui->comboBox->addItem("Крупы");
       ui->comboBox->addItem("Грибы и орехи");
       QFile inf(QApplication:: applicationDirPath () + "MANGAL.txt");
       if(!inf.open(QIODevice::ReadOnly)){
           QMessageBox::warning(0,"Предупреждение", " Не был выбран пользователь");
       }
       else{
           QTextStream stream(&inf);
           QString name_name;
           stream>>name_name;
           ui->gest->setText(name_name);
           inf.close();
           QFile::remove(QApplication:: applicationDirPath () + "MANGAL.txt");
           QFile Result(QApplication:: applicationDirPath () + "/User/"+name_name+".txt");
           if(!Result.open(QIODevice::ReadOnly)){
               ui->statusbar->showMessage("Файл не открыт");
           };
           QTextStream streama(&Result);
           QString sleep;
           for(int j=0;j!=4;j++){
               streama>>sleep;
               QTableWidgetItem *ittt=new QTableWidgetItem;
               ittt->setData(Qt::EditRole,sleep);
               ui->table_recom->setItem(0,j,ittt);
           }
           Result.close();
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Choice_of_products_clicked()
{
    QString str = QInputDialog::getText(this,"Вес","Введите вес продукта (гр) ",QLineEdit::Normal,"");
    double std =str.toDouble();
    if(std<=0){QMessageBox::warning(0,"Предупреждение", "Неккоректный ввод");}
    else{
        int i= ui->tableWidget->currentRow();//перенос целой строки
        int temp=0;
        bool flag = true,loop = true;
        QString textic,str_gramm;
        double dack, num_gramm;
        for(int val=0;val!=100;val++){
            QString tmp1, tmp2;
            tmp1 = ui->tableWidget->item(i,0)->text();
            if (ui->tableWidget_2->item(val,0) != 0){
                tmp2 = ui->tableWidget_2->item(val,0)->text();
                if(tmp1==tmp2){
                    QMessageBox::critical(this,"Внимание","Этот продукт уже выбран");
                    loop=false;
                    break;
               }
           }
       }
       if(loop){
           for(int j=0;j!=6;j++){
               while(flag){
                   if(ui->tableWidget_2->item(temp,0)== 0){
                       flag = false;
                   }else temp++;
               }
               num_gramm = str.toDouble();
               textic =ui->tableWidget->item(i,j)->text();
               dack=textic.toDouble()/100*num_gramm;
               if(j>0){
                   textic = QString::number(dack);
               }
               ui->tableWidget_2->setRowCount(temp+1);
               ui->tableWidget_2->setItem(temp,j,new QTableWidgetItem(textic));
               ui->tableWidget_2->setItem(temp,6,new QTableWidgetItem(str));//!!!
           }
       }
       sum();
    }
}

void MainWindow::on_Delete_Button_clicked()
{
    int i= ui->tableWidget_2->currentRow();
    ui->tableWidget_2->removeRow(i);
    sum();
}

void MainWindow::on_to_Change_clicked()
{
    ui->tableWidget_2->setFocus();
    if(ui->tableWidget_2->item(0,0)==0){
        QMessageBox::warning(0,"Предупреждение", "В таблице нет продуктов!");}
    else{
        QString str = QInputDialog::getText( /*0*/this,"Вес","Введите вес продукта (гр) ",QLineEdit::Normal,"");
        double std =str.toDouble();
        if(std<=0){QMessageBox::warning(0,"Предупреждение", "Неккоректный ввод!");}
        else{
            int i= ui->tableWidget_2->currentRow();//row
            QString tex_G = ui->tableWidget_2->item(i,6)->text(),tex_T;
            double num_G = tex_G.toDouble(),num_T,result;
            for(int j=1;j!=6;j++){
                tex_T=ui->tableWidget_2->item(i,j)->text();
                num_T=tex_T.toDouble();
                result=num_T/num_G*std;
                tex_T = QString::number(result);
                ui->tableWidget_2->setItem(i,j,new QTableWidgetItem(tex_T));
                ui->tableWidget_2->setItem(i,6,new QTableWidgetItem(str));
            }
        }
        sum();
    }
}
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0: {
        ui->Choice_of_products->setEnabled(true);
        QFile f(QApplication:: applicationDirPath () + "/Products_Lists/bread.txt");
        if(!f.open(QIODevice::ReadOnly)){
            ui->statusbar->showMessage("Файл не открыт");
        };
        QTextStream stream(&f);
        QString s;
        for(int i=0;i!=9;i++){
            ui->tableWidget->setRowCount(i+1);
            for(int j=0;j!=6;j++){
                stream>>s;
                QTableWidgetItem *it=new QTableWidgetItem;
                it->setData(Qt::EditRole,s);
                ui->tableWidget->setItem(i,j,it);
            }
        }
        f.close();
        ui->tableWidget->show();break;
    }
    case 1: {ui->Choice_of_products->setEnabled(true);
        QFile f(QApplication:: applicationDirPath () + "/Products_Lists/meat.txt");
        if(!f.open(QIODevice::ReadOnly)){ ui->statusbar->showMessage("Файл не открыт");};
        QTextStream stream(&f);
        QString s;
        for(int i=0;i!=11;i++){
            ui->tableWidget->setRowCount(i+1);
            for(int j=0;j!=6;j++){
                stream>>s;
                QTableWidgetItem *it=new QTableWidgetItem;
                it->setData(Qt::EditRole,s);
                ui->tableWidget->setItem(i,j,it);
            }
        }
        f.close();
        ui->tableWidget->show();} ;break;
    case 2: {ui->Choice_of_products->setEnabled(true);
        QFile f(QApplication:: applicationDirPath () + "/Products_Lists/fish.txt");
        if(!f.open(QIODevice::ReadOnly)){ ui->statusbar->showMessage("Файл не открыт");};
        QTextStream stream(&f);
        QString s;
        for(int i=0;i!=44;i++){
            ui->tableWidget->setRowCount(i+1);
            for(int j=0;j!=6;j++){
                stream>>s;
                QTableWidgetItem *it=new QTableWidgetItem;
                it->setData(Qt::EditRole,s);
                ui->tableWidget->setItem(i,j,it);
            }
        }
        f.close();
      ui->tableWidget->show();} ;break;
    case 3: {ui->Choice_of_products->setEnabled(true);
        QFile f(QApplication:: applicationDirPath () + "/Products_Lists/molocnie_prodykt.txt");
        if(!f.open(QIODevice::ReadOnly)){ ui->statusbar->showMessage("Файл не открыт");};
        QTextStream stream(&f);
        QString s;
        for(int i=0;i!=14;i++){
            ui->tableWidget->setRowCount(i+1);
            for(int j=0;j!=6;j++){
                stream>>s;
                QTableWidgetItem *it=new QTableWidgetItem;
                it->setData(Qt::EditRole,s);
                ui->tableWidget->setItem(i,j,it);
            }
        }
        f.close();
      ui->tableWidget->show();} ;break;
    case 4: {ui->Choice_of_products->setEnabled(true);
        QFile f(QApplication:: applicationDirPath () + "/Products_Lists/Fruits_and_yagodi.txt");
        if(!f.open(QIODevice::ReadOnly)){ ui->statusbar->showMessage("Файл не открыт");};
        QTextStream stream(&f);
        QString s;
        for(int i=0;i!=38;i++){
            ui->tableWidget->setRowCount(i+1);
            for(int j=0;j!=6;j++){
                stream>>s;
                QTableWidgetItem *it=new QTableWidgetItem;
                it->setData(Qt::EditRole,s);
                ui->tableWidget->setItem(i,j,it);
            }
        }
        f.close();
      ui->tableWidget->show();} ;break;
    case 5: {ui->Choice_of_products->setEnabled(true);
        QFile f(QApplication:: applicationDirPath () + "/Products_Lists/VEg.txt");
        if(!f.open(QIODevice::ReadOnly)){ ui->statusbar->showMessage("Файл не открыт");};
        QTextStream stream(&f);
        QString s;
        for(int i=0;i!=30;i++){
            ui->tableWidget->setRowCount(i+1);
            for(int j=0;j!=6;j++){
                stream>>s;
                QTableWidgetItem *it=new QTableWidgetItem;
                it->setData(Qt::EditRole,s);
                ui->tableWidget->setItem(i,j,it);
            }
        }
        f.close();
      ui->tableWidget->show();} ;break;
    case 6: {ui->Choice_of_products->setEnabled(true);
        QFile f(QApplication:: applicationDirPath () + "/Products_Lists/krypi.txt");
        if(!f.open(QIODevice::ReadOnly)){ ui->statusbar->showMessage("Файл не открыт");};
        QTextStream stream(&f);
        QString s;
        for(int i=0;i!=10;i++){
            ui->tableWidget->setRowCount(i+1);
            for(int j=0;j!=6;j++){
                stream>>s;
                QTableWidgetItem *it=new QTableWidgetItem;
                it->setData(Qt::EditRole,s);
                ui->tableWidget->setItem(i,j,it);
            }
        }
        f.close();
      ui->tableWidget->show();} ;break;
    case 7: {ui->Choice_of_products->setEnabled(true);
        QFile f(QApplication:: applicationDirPath () + "/Products_Lists/mashroom_and_orexi.txt");
        if(!f.open(QIODevice::ReadOnly)){ ui->statusbar->showMessage("Файл не открыт");};
        QTextStream stream(&f);
        QString s;
        for(int i=0;i!=10;i++){
            ui->tableWidget->setRowCount(i+1);
            for(int j=0;j!=6;j++){
                stream>>s;
                QTableWidgetItem *it=new QTableWidgetItem;
                it->setData(Qt::EditRole,s);
                ui->tableWidget->setItem(i,j,it);
            }
        }
        f.close();
        ui->tableWidget->show();} ;break;
    default:ui->statusbar->showMessage("Error");
    }
}

void MainWindow::on_action_triggered()
{
    Help window;
    window.setModal(true);
    window.exec();
}


