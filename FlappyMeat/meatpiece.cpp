#include "meatpiece.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QTimer>
#include <QKeyEvent>
#include <QWidget>
#include <cmath>
double Speed_bird = 0;
const double Speed_bird_max = 8;
const double Speed_bird_min = -6 ;
int rounded;
meatpiece::meatpiece(QPoint bird_center): bird_center_(bird_center)
{

}
void meatpiece::Update_bird() {
    rounded = std::round(Speed_bird);
    bird_center_ -= QPoint{0, rounded };
    if(Speed_bird > Speed_bird_min){
    Speed_bird -= 0.1;

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

        if(Speed_bird < Speed_bird_max){
        Speed_bird = 4;
    }
    }
}

