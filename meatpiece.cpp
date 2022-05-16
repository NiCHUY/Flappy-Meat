#include "meatpiece.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QTimer>
#include <QKeyEvent>
#include <QWidget>
#include <cmath>

double Speed_bird(0), start_Speed_bird(0);
const double Speed_bird_max(8), Speed_bird_min(-6);
double  gravity(0.1);
int rounded(0),rounded_(0), check(0), space(4);
qreal angle(0);

meatpiece::meatpiece(QPoint bird_center): bird_center_(bird_center)
{

}

void meatpiece::tydasyda(){
    rounded_ = std::round(start_Speed_bird);
    if(bird_center_.y() > 480){
    start_Speed_bird = 5;
    angle = -45;
    }

    bird_center_ -= QPoint{0, rounded_};

    if(start_Speed_bird > -2 ){
    start_Speed_bird -= 0.1;
    }
    angle += 0.85;
  }

void meatpiece::Update_bird() {
    rounded = std::round(Speed_bird);
    bird_center_ -= QPoint{0, rounded };
    if(Speed_bird > Speed_bird_min){
    Speed_bird -= gravity;
    if(angle >= -45){
        angle += 1;
    }
    }
}


QPoint meatpiece::GetPosition_bird() {
    return bird_center_;
}

void meatpiece::SetPosition_bird(QPoint pos_) {
    bird_center_ = pos_;
}

void meatpiece::IncreaseSpeed(QKeyEvent *event){
    if(event->key() == Qt::Key_Space){
        angle = -45;
        if(Speed_bird < Speed_bird_max){
        Speed_bird = space;

        }
    }
}

void meatpiece::SpeedChanger(int dif){
    if(dif == 1){
        gravity = 0.1;
        space = 3;
    }
    if(dif == 2){
        gravity = 0.1;
        space = 4;
    }
    if(dif == 3){
        gravity = 0.125;
        space = 5;
    }

}

void meatpiece::Lost(){
    if(Speed_bird < 0){
            Speed_bird = -Speed_bird-1;
    }
}

void meatpiece::DeathJump(){
    Speed_bird = 4;
}

qreal meatpiece::returnAngle(){
    return angle;
}
