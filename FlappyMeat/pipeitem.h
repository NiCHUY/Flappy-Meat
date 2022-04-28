#ifndef PIPEITEM_H
#define PIPEITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>

class pipeitem : public QGraphicsItemGroup, public QObject
{
    Q_OBJECT
public:
    explicit pipeitem();
signals:

public slots:
private:
    QGraphicsPixmapItem *toppipe;
    QGraphicsPixmapItem *lowpipe;
};

#endif // PIPEITEM_H
