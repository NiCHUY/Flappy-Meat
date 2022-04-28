#include "mainwindow.h"

#include <QApplication>

#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << 1111 << std::endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.showFullScreen();
    w.Init();
    return a.exec();
}
