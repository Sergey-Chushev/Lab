#include "new_user.h"
#include "ui_new_user.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QtGui>
#include <QMessageBox>
#include <iostream>
using namespace std;
double New_User::coefficient(double num, int i){
    switch (i) {
    case 0: num*=1.2;break;
    case 1: num*=1.3;break;
    case 2: num*=1.5;break;
    case 3: num*=1.7;break;
    case 4: num*=1.9;break;
    }
    return num;
}
New_User::New_User(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::New_User)
{
    ui->setupUi(this);
    QRegExp rx = QRegExp("[^\x0020]*");
    QRegExpValidator * LoginValidator = new QRegExpValidator(rx, this);
    ui->user_name->setValidator(LoginValidator);
    QFile f( "username.txt");
    if(!f.open(QIODevice::ReadOnly))
        return;
    while(true){
        QString line = f.readLine();
        line.chop(2);
        if(line==""){
            break;
        }
        ui->listWidget->addItem(line);
    }
    f.close();
}
New_User::~New_User()
{
    delete ui;
}
void New_User::on_pushButton_2_clicked()
{
QFile Pop("username.txt");
int n = 0;
 Pop.open(QIODevice::ReadOnly | QIODevice::Text);
   n = QTextStream(&Pop).readAll().split('\n').count();
   if(n==6){
       QMessageBox::warning(0,"Предупреждение", "Превышен лимит пользователей");
   }
   else{
    QString str_age = ui->age->text(),
            str_weight = ui->weight->text(),
            str_height = ui->height->text();
    double  std_age =str_age.toDouble(),
            std_weight = str_weight.toDouble(),
            std_height = str_height.toDouble();
    if (ui->men->isChecked()==false && ui->women->isChecked()==false){QMessageBox::warning(0,"Предупреждение", "Выберите пол");}else
    if (std_age <= 0 || std_age > 100){QMessageBox::warning(0,"Предупреждение", "Введен неккорректный возраст");}else
    if (std_weight <= 0 || std_weight>200 )  {QMessageBox::warning(0,"Предупреждение", "Введен неккорректный вес");}else
    if (std_height <= 0 || std_height>2500 ){QMessageBox::warning(0,"Предупреждение", "Введен неккорректный рост");}
    else {
    QString file_name =  ui->user_name->text();
    QFile user_name("username.txt");
    if(user_name.open(QIODevice::Append | QIODevice::Text)){
        QTextStream fout(&user_name);
        fout<<file_name<<endl;
        user_name.close();
    QString file_name =  ui->user_name->text();
    QFile user(QApplication:: applicationDirPath () +"/User/"+file_name + ".txt");
        if(user.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&user);
 double protein,fats,carb;
        if(ui->men->isChecked()){
            int index=ui->activ->currentIndex();
            int index_reason=ui->reason->currentIndex();
            double need_men;
            need_men = 66.47+13.75*ui->weight->text().toDouble()+5*ui->height->text().toDouble()-6.74*ui->age->text().toDouble();
            switch(index_reason){
            case 0:
                protein = 1.3*ui->weight->text().toDouble();
                fats = 1.1*ui->weight->text().toDouble();
                carb = 6.8*ui->weight->text().toDouble();
                ;break;
            case 1:
                protein = 2.3*ui->weight->text().toDouble();
                fats = 0.9*ui->weight->text().toDouble();
                carb = 6.6*ui->weight->text().toDouble();
                ;break;
            case 2:
                protein = 1.5*ui->weight->text().toDouble();
                fats = 0.7*ui->weight->text().toDouble();
                carb = 2.7*ui->weight->text().toDouble();
                ;break;
            }
            out<<protein<<endl;
            out<<fats<<endl;
            out<<carb<<endl;
            out<<coefficient(need_men,index)<<endl;
        }else
            if(ui->women->isChecked()){
                int index=ui->activ->currentIndex();
                double need_women;
                need_women = 655.1 + 9.6*ui->weight->text().toDouble()+1.85*ui->height->text().toDouble()-4.68*ui->age->text().toDouble();
                int index_reason=ui->reason->currentIndex();
                switch(index_reason){
                case 0:
                    protein = 1.3 * ui->weight->text().toDouble();
                    fats = 1.1 * ui->weight->text().toDouble();
                    carb = 6.8 * ui->weight->text().toDouble();
                    ;break;
                case 1:
                    protein = 2.3 * ui->weight->text().toDouble();
                    fats = 0.9 * ui->weight->text().toDouble();
                    carb = 6.6 * ui->weight->text().toDouble();
                    ;break;
                case 2:
                    protein = 1.5 * ui->weight->text().toDouble();
                    fats = 0.7 * ui->weight->text().toDouble();
                    carb = 2.7 * ui->weight->text().toDouble();
                    ;break;
                }
                out<<protein<<endl;
                out<<fats<<endl;
                out<<carb<<endl;
                out<<coefficient(need_women,index)<<endl;
            }
        user.close();
        }
    }
}
    ui->listWidget->clear();
    QFile f( "username.txt");
    if(!f.open(QIODevice::ReadOnly))
          return;
for(int i = 0 ;i!=5;i++){
    QString line = f.readLine();
     line.chop(2);
    ui->listWidget->addItem(line);
        }
f.close();
    }
}
void New_User::on_VIBOR_clicked()
{
    QString tex_G = ui->listWidget->currentItem()->text();
    QFile user_tmp(QApplication:: applicationDirPath ()+"MANGAL.txt");
    if( user_tmp.open((QIODevice::WriteOnly | QIODevice::Text))){
    QTextStream hex(&user_tmp);
    hex<<tex_G;
    }
  close();
}
void New_User::on_Delete_Button_clicked()
{
    if(ui->listWidget->count()==0){
        QMessageBox::critical(0,"Ошибка", "Создайте пользователя");
    }else{

    QString delta = ui->listWidget->currentItem()->text();
    QFile::remove(QApplication:: applicationDirPath () + "/User/" +  delta +".txt");
            QListWidgetItem *it = ui->listWidget->item(ui->listWidget->currentRow());
                delete it;
            QFile f( "username.txt");
            if(f.open(QIODevice::WriteOnly | QIODevice::Text)){
             QTextStream ret(&f);
             int betta = ui->listWidget->count();
             for(int i = 0; i<betta; i++){
                 ret<<ui->listWidget->item(i)->text();
             }
            }
    }
}

