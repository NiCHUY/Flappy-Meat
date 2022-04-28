#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <vector>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QTimer>
#include <QKeyEvent>
#include <QWidget>
#include <QTextDocument>
#include "pipe.h"
#include "meatpiece.h"
#include "menuwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void Update();
    void Init();
    void paintEvent(QPaintEvent* painevent) ;
    void Inrtersects();
    void Score();

private slots:
   void keyPressEvent(QKeyEvent *event) ;
   void on_pushButton_clicked(bool checked);

private:
    double result = 0;

    static const int kPipesCount;
    static const int kDistanceBetweenPipes;
    static const int kMinPipeHeight;
    const static int kTopBottomSpacing;

    QTimer* timer ;
    Ui::MainWindow *ui;
    std::vector<Pipe> pipes;
    QPixmap* pipe_pixmap_up;
    QPixmap* pipe_pixmap_d;
    QPixmap* bird;
    QPixmap* presset;
    QPixmap* Scoreboard;
    QPixmap* birddeth;
    QPoint bird_center_;
    QPoint pos;
    meatpiece ball;
    menuwindow *menu;
    QSoundEffect jump;
    int min_center_y;

};
#endif // MAINWINDOW_H
