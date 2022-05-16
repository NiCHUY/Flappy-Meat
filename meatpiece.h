#ifndef MEATPIECE_H
#define MEATPIECE_H

#include <QPoint>
#include <QMainWindow>
#include <QSoundEffect>


class meatpiece
{
public:

    meatpiece(QPoint bird_center);

    void paintBirdEllips(QPaintEvent *event);

    QPoint GetPosition_bird();

    void Update_bird();

    void SetPosition_bird(QPoint pos_);

    void IncreaseSpeed(QKeyEvent *event);

    void tydasyda();

    void SpeedChanger(int);

    void Lost();

    void DeathJump();

    qreal returnAngle();
private:

    QPoint bird_center_;

};

#endif // MEATPIECE_H
