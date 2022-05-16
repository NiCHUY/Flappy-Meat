#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
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
#include <QtMultimedia>
#include <QSoundEffect>
#include <QFile>
#include <QTextStream>
#include <QTransform>
#include <QPushButton>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>

#include "pipe.h"
#include "meatpiece.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;


public slots:
    void Update();

    void Init();

    void paintEvent(QPaintEvent* painevent) ;

    void Inrtersects();

    void Score();

    void Restart();

    void ButtonChecker();

    void randomanimation();



private slots:

   void keyPressEvent(QKeyEvent *event) ;

   void StartGame();

   void EndGame();

   void Replay();

   void GoToMenu();

   void Settings();

   void Skins();

   void Easy();
   void Medium();
   void Hard();

   void DifficultyChecker();

   void bird1();
   void bird2();
   void bird3();

private:

    double result = 0;

    static const int kPipesCount;
    static const int kDistanceBetweenPipes;
    static const int kMinPipeHeight;
    static int kTopBottomSpacing;


    QTimer* timer ;
    std::vector<Pipe> pipes;
    QPixmap* pipe_pixmap_up;
    QPixmap* pipe_pixmap_d;
    QPixmap* bird;
    QPixmap* presset;
    QPixmap* Scoreboard;
    QPixmap* smoke;
    QPixmap* flappymeat;
    QPixmap* Death;
    QPixmap* Setting ;
    QSoundEffect space;
    QPoint bird_center_;
    QPoint pos;
    meatpiece ball;
    int min_center_y;
    QLabel *label;


    QPushButton *Start_button;
    QPushButton *Setting_button;
    QPushButton *Skin_button;
    QPushButton *Exit_button;
    QPushButton *Replay_button;
    QPushButton *Menu_button;
    QPushButton *Easy_button;
    QPushButton *Medium_button;
    QPushButton *Hard_button;
    QPushButton *ms_button;

    QPushButton *birdorigin_button;
    QPushButton *birdred_button;
    QPushButton *hohlobird_button;
    QPushButton *custom_button;
    QPushButton *custom_button_picker;


};
#endif // MAINWINDOW_H
