#include "achivementwindow.h"
#include "ui_achivementwindow.h"

achivementwindow::achivementwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::achivementwindow)
{
    ui->setupUi(this);
}

achivementwindow::~achivementwindow()
{
    delete ui;
}
