#include "mainwindow.h"

#include <QApplication>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("FlappyMeat V1.0");
    w.showFullScreen();
    w.Init();
    return a.exec();
}
