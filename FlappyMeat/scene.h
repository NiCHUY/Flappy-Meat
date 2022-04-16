#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit scene(QObject *parent = nullptr);
signals:

public slots:
};

#endif // SCENE_H
