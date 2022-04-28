#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "menuwindow.h"
#include <QPoint>
#include <QRandomGenerator>
#include <QTimer>
#include <QPainter>
#include <algorithm>
#include <QTransform>

const int MainWindow::kPipesCount(5);
const int MainWindow::kDistanceBetweenPipes(350);
const int MainWindow::kMinPipeHeight(100);
const int MainWindow::kTopBottomSpacing(170);
int death(0), mez(0);
const int radius(30);
QString score;
QPoint const bird_center(500, 300);
QPoint const refresh(1000, 600);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pipe_pixmap_up(new QPixmap(":/new/pipes/graphics/pipe_up.png"))
    , pipe_pixmap_d(new QPixmap(":/new/pipes/graphics/pipe_d.png"))
    , presset(new QPixmap(":/new/pipes/graphics/presset.jpg"))
    , Scoreboard(new QPixmap(":/new/pipes/graphics/Score board.jpg"))
    , bird(new QPixmap(":/new/pipes/graphics/bird.png"))
    , birddeth(new QPixmap(":/new/pipes/graphics/blood.png"))
    , bird_center_(500, 300)
    , ball(bird_center_)
    , pos(0,0)
    , min_center_y(0)
{
    ui->setupUi(this);
    menu = new menuwindow();
    connect(menu, &menuwindow::firstWindow, this, &MainWindow::show);


}

void MainWindow::Init() {
    min_center_y = kMinPipeHeight + kTopBottomSpacing / 2;

    for(int i = 0; i < kPipesCount; i++) {
        int y = QRandomGenerator::global()->bounded(min_center_y, height() - min_center_y);
        pipes.push_back(Pipe(QPoint(width() + i * kDistanceBetweenPipes, y)));
    }
    timer = new QTimer(this);
    timer->setInterval(1000 / 120);
    timer->start();

    connect(timer, &QTimer::timeout, this, &MainWindow::Update);
    connect(timer, &QTimer::timeout, this, &MainWindow::Inrtersects);
    connect(timer, &QTimer::timeout, this, &MainWindow::Score);
}

void MainWindow::Update() {

    ball.Update_bird();



    int max_x = -1000;
    for(int i = 0; i < kPipesCount; i++) {
        pipes[i].Update();
        max_x = std::max(max_x, pipes[i].GetPosition().x());
    }
    for(int i = 0; i <kPipesCount; i++) {
         pos = pipes[i].GetPosition();
        if (pos.x() < -100) {
            pipes[i].SetPosition(QPoint{max_x + kDistanceBetweenPipes, pos.y()});
            max_x = pipes[i].GetPosition().x();
        }

    }

    this->repaint();
}
void MainWindow::keyPressEvent(QKeyEvent *event){
 ball.IncreaseSpeed(event);
 if(event->key() == Qt::Key_Escape){
     menu->showFullScreen();
     this->close();

 }
 if(event->key() == Qt::Key_R){
   ball = bird_center;
   timer->start();
   death = 0;
   result = 0;
   pos = refresh;
   Update();
   for(int i=0; i<kPipesCount; i++){
   mez += kDistanceBetweenPipes;
   int y = QRandomGenerator::global()->bounded(min_center_y, height() - min_center_y);
   pipes[i].SetPosition(QPoint{refresh.x()+mez,y});
}
   mez = 0;
 }
 jump.setSource(QUrl::fromLocalFile("space.wav"));
 jump.setLoopCount(1);
 jump.setVolume(0.25f);
 jump.play();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* paint_event) {
    QPainter painter(this);
    painter.drawPixmap(-200,-200, *presset);
    QPen whiteP(Qt::white);
    painter.setPen(whiteP);
    //painter.drawEllipse(ball.GetPosition_bird(), radius, radius);
    painter.drawPixmap(ball.GetPosition_bird().x()-39, ball.GetPosition_bird().y()-35, radius*2+9, radius*2+6, *bird);

    for (int i = 0; i < pipes.size(); i++) {
        QPoint pos = pipes[i].GetPosition();
        painter.drawPixmap(pos.x() - pipe_pixmap_up->width() / 2 + 3, pos.y() + kTopBottomSpacing / 2 - 48, *pipe_pixmap_up);
        //painter.drawRect(pos.x() - 22, pos.y() + kTopBottomSpacing / 2, 44, 600);
        painter.drawPixmap(pos.x() - pipe_pixmap_d->width() / 2 - 7, pos.y() - kTopBottomSpacing / 2 - pipe_pixmap_d->height() + 48, *pipe_pixmap_d);
        //painter.drawRect(pos.x() - 22, pos.y() - kTopBottomSpacing / 2, 44, -600);
    }
       //painter.drawRect(0, 0, 600, 10);
       //painter.drawRect(0, 790, 600 , 800);
       painter.drawPixmap(0,790,1600, 1080, *Scoreboard);
       QPainter mytext(this);
       mytext.setFont(QFont("Times", 16, QFont::Bold));
       score = QString::number(result);
       mytext.drawText(QPoint(60,100), "Score:");
       mytext.drawText(QPoint(130,100), score);
       if (death == 1 || death == 2){
           QPainter painter(this);
           painter.drawPixmap(0,0, *birddeth);
           timer->stop();
           mytext.setFont(QFont("Times", 72, QFont::Bold));
           mytext.drawText(this->width()/2-350, 200, "You Died");
           mytext.setFont(QFont("Times", 60, QFont::Bold));
           mytext.drawText(this->width()/2-400, 400, "Press esc to menu");
           mytext.setFont(QFont("Times", 60, QFont::Bold));
           mytext.drawText(this->width()/2-400, 500, "Press r to restart");

       }


    painter.end();
}
void MainWindow::Inrtersects(){
    if(ball.GetPosition_bird().y()+30 >= 790 || ball.GetPosition_bird().y()+30 <= 10 ){
         death++;
    }
    for (int i = 0; i < pipes.size(); i++) {
    if(ball.GetPosition_bird().x()+radius >= pipes[i].GetPosition().x()-26 && ball.GetPosition_bird().x()-radius <= pipes[i].GetPosition().x()+22){
    {
            if((ball.GetPosition_bird().y()+radius >= pipes[i].GetPosition().y() + kTopBottomSpacing / 2 || ball.GetPosition_bird().y()-radius <= pipes[i].GetPosition().y()- kTopBottomSpacing / 2)){
        death++;
         }}}}}
void MainWindow::Score(){
    for (int i = 0; i < pipes.size(); i++) {
    if(ball.GetPosition_bird().x()+radius >= pipes[i].GetPosition().x()-18 && ball.GetPosition_bird().x()-radius <= pipes[i].GetPosition().x()+21){
    result++;
        }
    }

}


void MainWindow::on_pushButton_clicked(bool checked)
{
    menu->show();
    this->close();
}

