#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPoint>
#include <QRandomGenerator>
#include <QTimer>
#include <QPainter>
#include <algorithm>
#include <QTransform>

const int MainWindow::kPipesCount(5), MainWindow::kDistanceBetweenPipes(350), MainWindow::kMinPipeHeight(100), radius(30);
int MainWindow::kTopBottomSpacing(170), highscore(0), button_w(400), button_h(65), dif(1), birdtype(1);
bool start(false), death(false), menu(true), settings(false), skins(false), sp(0);
const QPoint center(450, 540);
QPoint const refresh(1100, 600);
QString score("BETA"), diff;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pipe_pixmap_up(new QPixmap(":/graphics/pipes/pipe_up.png"))
    , pipe_pixmap_d(new QPixmap(":/graphics/pipes/pipe_d.png"))
    , presset(new QPixmap(":/graphics/presset.jpg"))
    , Scoreboard(new QPixmap(":/graphics/Scoreboard.png"))
    , bird(new QPixmap(":/graphics/bird/bird.png"))
    , smoke(new QPixmap(":/graphics/smoke.png"))
    , flappymeat(new QPixmap(":/graphics/FlappyMeat.png"))
    , Death(new QPixmap(":/graphics/Death.png"))
    , Setting(new QPixmap(":/graphics/Settings.png"))
    , bird_center_(450, 500)
    , ball(bird_center_)
    , pos(0,0)
    , min_center_y(0)
    , space(this)
    , label(new QLabel(this))
{
    QScreen *screen = QApplication::screens().at(0);
    int x = screen->size().width();
    int y = screen->size().height();

    ui->setupUi(this);
    space.setSource(QUrl::fromLocalFile("space.wav"));
    space.setVolume(0.25f);

    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label->setStyleSheet("border: none;");


//buttons
    //start
    Start_button = new QPushButton("Start", this);
    Start_button->setGeometry(QRect(QPoint((x - button_w)/2, 500), QSize(button_w, button_h)));
    Start_button->setFocusPolicy(Qt::NoFocus);
    connect(Start_button, SIGNAL (released()), this, SLOT (StartGame()));

    Skin_button = new QPushButton("Skins", this);
    Skin_button->setGeometry(QRect(QPoint((x - button_w)/2, 565), QSize(button_w, button_h)));
    Skin_button->setFocusPolicy(Qt::NoFocus);
    connect(Skin_button, SIGNAL (released()), this, SLOT (Skins()));

    Setting_button = new QPushButton("Settings", this);
    Setting_button->setGeometry(QRect(QPoint((x - button_w)/2, 630), QSize(button_w, button_h)));
    Setting_button->setFocusPolicy(Qt::NoFocus);
    connect(Setting_button, SIGNAL (released()), this, SLOT (Settings()));

    Exit_button = new QPushButton("Exit", this);
    Exit_button->setGeometry(QRect(QPoint((x - button_w)/2, 695), QSize(button_w, button_h)));
    Exit_button->setFocusPolicy(Qt::NoFocus);
    connect(Exit_button, SIGNAL (released()), this, SLOT (EndGame()));

    Replay_button = new QPushButton("Replay", this);
    Replay_button->setGeometry(QRect(QPoint((x - button_w)/2, 500), QSize(button_w, button_h)));
    Replay_button->setFocusPolicy(Qt::NoFocus);
    connect(Replay_button, SIGNAL (released()), this, SLOT (Replay()));

    Menu_button = new QPushButton("Menu", this);
    Menu_button->setGeometry(QRect(QPoint((x - button_w)/2, 565), QSize(button_w, button_h)));
    Menu_button->setFocusPolicy(Qt::NoFocus);
    connect(Menu_button, SIGNAL (released()), this, SLOT (GoToMenu()));

    Easy_button = new QPushButton("Easy", this);
    Easy_button->setGeometry(QRect(QPoint((x - button_w)/2, 500), QSize(button_w, button_h)));
    Easy_button->setFocusPolicy(Qt::NoFocus);
    connect(Easy_button, SIGNAL (released()), this, SLOT (Easy()));

    Medium_button = new QPushButton("Medium", this);
    Medium_button->setGeometry(QRect(QPoint((x - button_w)/2, 565), QSize(button_w, button_h)));
    Medium_button->setFocusPolicy(Qt::NoFocus);
    connect(Medium_button, SIGNAL (released()), this, SLOT (Medium()));

    Hard_button = new QPushButton("Hard", this);
    Hard_button->setGeometry(QRect(QPoint((x - button_w)/2, 630), QSize(button_w, button_h)));
    Hard_button->setFocusPolicy(Qt::NoFocus);
    connect(Hard_button, SIGNAL (released()), this, SLOT (Hard()));

    ms_button = new QPushButton("Return", this);
    ms_button->setGeometry(QRect(QPoint(x-150, y-100), QSize(100, 40)));
    ms_button->setFocusPolicy(Qt::NoFocus);
    connect(ms_button, SIGNAL (released()), this, SLOT (GoToMenu()));

    birdorigin_button = new QPushButton("Original Bird", this);
    birdorigin_button->setGeometry(QRect(QPoint(x/2-200, 200), QSize(400, 40)));
    birdorigin_button->setFocusPolicy(Qt::NoFocus);
    connect(birdorigin_button, SIGNAL (released()), this, SLOT (bird1()));

    birdred_button = new QPushButton("Red Bird", this);
    birdred_button->setGeometry(QRect(QPoint(x/2-200, 240), QSize(400, 40)));
    birdred_button->setFocusPolicy(Qt::NoFocus);
    connect(birdred_button, SIGNAL (released()), this, SLOT (bird2()));

    hohlobird_button = new QPushButton("XoXol Bird", this);
    hohlobird_button->setGeometry(QRect(QPoint(x/2-200, 280), QSize(400, 40)));
    hohlobird_button->setFocusPolicy(Qt::NoFocus);
    connect(hohlobird_button, SIGNAL (released()), this, SLOT (bird3()));

    custom_button = new QPushButton("Your Bird", this);
    custom_button->setGeometry(QRect(QPoint(x/2-200, 320), QSize(300, 40)));
    custom_button->setFocusPolicy(Qt::NoFocus);
    connect(custom_button, SIGNAL (released()), this, SLOT (GoToMenu()));

    custom_button_picker = new QPushButton("...", this);
    custom_button_picker->setGeometry(QRect(QPoint(x/2+100, 320), QSize(100, 40)));
    custom_button_picker->setFocusPolicy(Qt::NoFocus);
    connect(custom_button_picker, SIGNAL (released()), this, SLOT (GoToMenu()));
}

void MainWindow::Restart(){
    death = false; result = 0; pos = refresh;


    for(int i=0; i<kPipesCount; i++){
    int y = QRandomGenerator::global()->bounded(min_center_y, height() - min_center_y);
    pipes[i].SetPosition(QPoint{refresh.x() + (i+1)*kDistanceBetweenPipes, y});
 } 
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
    connect(timer, &QTimer::timeout, this, &MainWindow::ButtonChecker);
    connect(timer, &QTimer::timeout, this, &MainWindow::randomanimation);
    connect(timer, &QTimer::timeout, this, &MainWindow::DifficultyChecker);
}

void MainWindow::Update() {
    if(ball.GetPosition_bird().y()+radius >= this->height()){
        ball.Lost();
    }
    if(death == true){
        QPoint pos = {ball.GetPosition_bird().x()-2 ,ball.GetPosition_bird().y()};
        ball.SetPosition_bird(pos);
    }
if(start == true){
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
}
else{
    ball.tydasyda();
}
    this->repaint();
}

void MainWindow::keyPressEvent(QKeyEvent *event){
if(menu == false){

    if(event->key() == Qt::Key_M){
         GoToMenu();
     }
    if(death == true){

        if(event->key() == Qt::Key_R){
        Replay();
        }
    }
//jump
if(event->key() == Qt::Key_Space){
    if(death == false){
    ball.IncreaseSpeed(event);
    space.play();
    }

    if(start == false){
        start = true;}
  }
    }
//
if(menu == true && death ==false){
    if(event->key() == Qt::Key_Space){
    menu = false;
    }
    if(event->key() == Qt::Key_Escape){
       this->close();
    }
}
}

MainWindow::~MainWindow(){
     delete ui;
 }

void MainWindow::randomanimation(){
    if(sp == 0){
        sp = 1;
    }
    if(sp == 1){
        sp = 0;
    }
    if(birdtype == 1){
         bird = new QPixmap(":/graphics/bird/bird.png");
    }
    if(birdtype == 2){
         bird = new QPixmap(":/graphics/bird/bird_red.png");
    }
    if(birdtype == 3){
         bird = new QPixmap(":/graphics/bird/bird_ukr.png");
    }
 }

void MainWindow::paintEvent(QPaintEvent* paint_event) {
    QPainter painter(this);
    QFont font = label->font();
    font.setPixelSize(60);
    label->setFont(font);
//background
    painter.drawPixmap(-200,-200, *presset);

    if (menu == false){
//bird
    painter.save();
    painter.translate(QPoint{ball.GetPosition_bird().x(), ball.GetPosition_bird().y()});
    painter.rotate(ball.returnAngle());
    painter.drawPixmap(-39-sp, -35, radius*2+9, radius*2+6, *bird);
    painter.restore();

//pipes
    for (int i = 0; i < pipes.size(); i++) {
        QPoint pos = pipes[i].GetPosition();
        painter.drawPixmap(pos.x() - pipe_pixmap_up->width() / 2 + 3, pos.y() + kTopBottomSpacing / 2 - 48, *pipe_pixmap_up);
        painter.drawPixmap(pos.x() - pipe_pixmap_d->width() / 2 - 7, pos.y() - kTopBottomSpacing / 2 - pipe_pixmap_d->height() + 48, *pipe_pixmap_d);
    }
//score
    QPainter mytext(this);

    label->setGeometry(this->width()/2-100,100,200,80);


        score = QString::number(result);
        label->setText(score);

    //death
        if (death == true){
            painter.drawPixmap((this->width() - Death->width())/2, 200, *Death);
            label->setGeometry(this->width()/2-500,400,1000,80);

            if(result > highscore){
                 highscore = result;
            }



           }
    //start
            if (start == false){
                 QPainter mytext(this);
                 mytext.setFont(QFont("Times", 40, QFont::Bold));
                 mytext.drawText(this->width()/2-200, 450, "Press SPACE to start");
            }
        }

    //menu
        if(menu == true && settings == false && skins == false){
            painter.drawPixmap((this->width() - flappymeat->width())/2, 200, *flappymeat);
            label->setGeometry(this->width()/2-500,400,1000,80);
            label->setText(score);
    //settings
        if(settings == true){
        QPainter painter(this);
        painter.drawPixmap((this->width() - Setting->width())/2, 200, *Setting);

        }
        }
        painter.end();

    }

    void MainWindow::Inrtersects(){
        if(!death){
        if(ball.GetPosition_bird().y()+radius+4 >= this->height()-4 || ball.GetPosition_bird().y()+radius+1 <= 0 ){
             death = true;
             ball.DeathJump();
        }

        for (int i = 0; i < pipes.size(); i++) {
            int diameter = radius * 2;
            QRegion r1(QRect(ball.GetPosition_bird().x() - radius, ball.GetPosition_bird().y() - radius, diameter, diameter), QRegion::Ellipse);
            QRegion r2(QRect(pipes[i].GetPosition().x() - 22, pipes[i].GetPosition().y() + kTopBottomSpacing / 2, 44, 10000));
            QRegion r3(QRect(pipes[i].GetPosition().x() - 22, pipes[i].GetPosition().y() - kTopBottomSpacing / 2 - 10000, 44, 10000));
            if (r1.intersects(r2) || r1.intersects(r3)) {
                ball.DeathJump();
                death = true;
            }

//            if(ball.GetPosition_bird().x()+radius >= pipes[i].GetPosition().x()-22 && ball.GetPosition_bird().x()-radius <= pipes[i].GetPosition().x()+16){
//                if((ball.GetPosition_bird().y()+radius-4 >= pipes[i].GetPosition().y() + kTopBottomSpacing / 2 || ball.GetPosition_bird().y()-radius+4 <= pipes[i].GetPosition().y()- kTopBottomSpacing / 2)){
//                     ball.DeathJump();
//                     death = true;
//                }
//            }
        }
    }
}
    void MainWindow::Score(){
        if(death == false){
        for (int i = 0; i < pipes.size(); i++) {
        if(ball.GetPosition_bird().x()+radius >= pipes[i].GetPosition().x()-18 && ball.GetPosition_bird().x()-radius <= pipes[i].GetPosition().x()+21){
        result++;
        }
            }
        }
    }

    void MainWindow::ButtonChecker(){
        if(menu == false || settings == true || skins == true){
            Start_button->setVisible(false);
        }else{
            Start_button->setVisible(true);
        }
        if(menu == false || settings == true || skins == true){
            Setting_button->setVisible(false);
        }else{
            Setting_button->setVisible(true);
        }
        if(menu == false || settings == true || skins == true){
            Exit_button->setVisible(false);
        }else{
            Exit_button->setVisible(true);
        }
        if(menu == false || settings == true || skins == true){
            Skin_button->setVisible(false);
        }else{
            Skin_button->setVisible(true);
        }
        if(death == true){
            Replay_button->setVisible(true);
        }else{
            Replay_button->setVisible(false);
        }
        if(death == true){
            Menu_button->setVisible(true);
        }else{
            Menu_button->setVisible(false);
        }

        if(settings == true || skins == true){
          ms_button->setVisible(true);
        }else{
            ms_button->setVisible(false);

        }

        if(settings == true){
            Easy_button->setVisible(true);
            Medium_button->setVisible(true);
            Hard_button->setVisible(true);

        }else{
            Easy_button->setVisible(false);
            Medium_button->setVisible(false);
            Hard_button->setVisible(false);

        }
        if(skins == true){
            birdorigin_button->setVisible(true);
            birdred_button->setVisible(true);
            hohlobird_button ->setVisible(true);
            custom_button->setVisible(true);
            custom_button_picker->setVisible(true);
        }else{
            birdorigin_button->setVisible(false);
            birdred_button->setVisible(false);
            hohlobird_button->setVisible(false);
            custom_button->setVisible(false);
            custom_button_picker->setVisible(false);
}
    }


    void MainWindow::StartGame(){
        menu = false;
    }

    void MainWindow::EndGame(){
        this->close();
    }

    void MainWindow::Settings(){
        settings = true;

        }

    void MainWindow::Replay(){
        ball = bird_center_;
        timer->start();
        this->Restart();
        start = false;

    }

    void MainWindow::GoToMenu(){
        ball = bird_center_;
        this->Restart();
        menu = true;
        settings = false;
        skins = false;
        start = false;
        score = QString::number(highscore);
        score = "hightscore: " + score;
    }


    void MainWindow::Easy(){
        dif = 1;
    }
    void MainWindow::Medium(){
        dif = 2;
    }
    void MainWindow::Hard(){
        dif = 3;
    }

    void MainWindow::DifficultyChecker(){
        if(settings == true){
            ball.SpeedChanger(dif);
            if(dif == 1){
              kTopBottomSpacing = 250;
            }
            if(dif == 2){
              kTopBottomSpacing = 175;
            }
            if(dif == 3){
              kTopBottomSpacing = 170;
            }

            label->setGeometry(this->width()/2-500,700,1000,80);

            if(dif == 1){
                diff = "Easy";
            }
            if(dif == 2){
                diff = "Medium";
            }
            if(dif == 3){
                diff = "Hard";
            }
            label->setText("Currently is "+diff);
        }
    }

    void MainWindow::Skins(){
        skins = true;
        label->setGeometry(this->width()/2-500,100,1000,80);
        label->setText("Pick your fighter");
    }
    void MainWindow::bird1(){
        birdtype = 1;
    }
    void MainWindow::bird2(){
        birdtype = 2;
    }
    void MainWindow::bird3(){
        birdtype = 3;
    }



