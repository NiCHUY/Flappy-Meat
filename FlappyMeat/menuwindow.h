#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>

#include <QPixmap>
#include <vector>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QTimer>
#include <QKeyEvent>
#include <QWidget>
#include <QTextDocument>
#include <QProcess>
#include <QDir>

namespace Ui {
class menuwindow;
}

class menuwindow : public QWidget
{
    Q_OBJECT

public:
    explicit menuwindow(QWidget *parent = nullptr);
    ~menuwindow();
signals:
    void firstWindow();
private:
    Ui::menuwindow *ui;
    QPixmap *pressetmenu;
    QPixmap *name;
private slots:

    void StartGame();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();

    public slots:
    void paintEvent(QPaintEvent* paintevent);

};

#endif // MENUWINDOW_H
