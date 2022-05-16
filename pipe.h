#ifndef PIPE_H
#define PIPE_H

#include <QPoint>


class Pipe
{
public:

    Pipe(QPoint center);

    QPoint GetPosition();


    void Update();

    void SetPosition(QPoint pos);

private:

    const static int kSpeed;
    QPoint center_;
};

#endif // PIPE_H
