#include "mainwindow.h"
#include "new_user.h"
#include <QtGui>
#include <QTextCodec>
#include <QApplication>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8")); //чтоб не было краказябл
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
