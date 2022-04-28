#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "mainwindow.h"
menuwindow::menuwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menuwindow),
    pressetmenu(new QPixmap(":/new/pipes/graphics/presset.jpg")),
    name(new QPixmap(":/new/pipes/graphics/FlappyMeat.png"))

{    setFixedSize(600,800);
      ui->setupUi(this);

}


    void menuwindow::paintEvent(QPaintEvent* paintevent){
        QPainter painterm(this);
        painterm.drawPixmap(-200,-200, *pressetmenu);
        painterm.drawPixmap(0,100, *name);
      }


menuwindow::~menuwindow()
{
    delete ui;
}
void menuwindow::StartGame()
{
    this->close();
    emit firstWindow();
}

void menuwindow::on_pushButton_3_clicked()
{
     menuwindow::close();
}


void menuwindow::on_pushButton_clicked()
{

       QString program = QApplication::applicationFilePath();
       QStringList arguments = QApplication::arguments();
       QString workingDirectory = QDir::currentPath();
       QProcess::startDetached(program, arguments, workingDirectory);
       QApplication::exit();

}

