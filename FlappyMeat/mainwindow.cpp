#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPoint>
#include <QRandomGenerator>
#include <QTimer>
#include <QPainter>

#include <algorithm>

const int MainWindow::kPipesCount = 10;
const int MainWindow::kDistanceBetweenPipes = 300;
const int MainWindow::kMinPipeHeight = 100;
const int MainWindow::kTopBottomSpacing = 200;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pipe_pixmap_(new QPixmap(":/new/prefix1/pipe.png"))
{
    setFixedSize(600,800);
    ui->setupUi(this);
    int min_center_y = kMinPipeHeight + kTopBottomSpacing / 2;

    for(int i = 0; i < kPipesCount; i++) {
        int y = QRandomGenerator::global()->bounded(min_center_y, height() - min_center_y);
        pipes.push_back(Pipe(QPoint(width() + i * kDistanceBetweenPipes, y)));
    }


    QTimer* timer = new QTimer(this);
    timer->setInterval(1000 / 120);
    timer->start();

    connect(timer, &QTimer::timeout, this, &MainWindow::Update);
}

void MainWindow::Update() {
    int max_x = -1000;
    for(int i = 0; i < pipes.size(); i++) {
        pipes[i].Update();
        max_x = std::max(max_x, pipes[i].GetPosition().x());
    }
    for(int i = 0; i < pipes.size(); i++) {
        QPoint pos = pipes[i].GetPosition();
        if (pos.x() < -100) {
            pipes[i].SetPosition(QPoint{max_x + kDistanceBetweenPipes, pos.y()});
            max_x = pipes[i].GetPosition().x();
        }
    }
    this->repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* paint_event) {
    QPainter painter(this);

    for(int i = 0; i < pipes.size(); i++) {
        QPoint pos = pipes[i].GetPosition();
        painter.drawRect(pos.x() - 5, pos.y() - 5, 10, 10);
        painter.drawPixmap(pos.x() - pipe_pixmap_->width() / 2, pos.y() + kTopBottomSpacing / 2, *pipe_pixmap_);
        painter.drawPixmap(pos.x() - pipe_pixmap_->width() / 2, pos.y() - kTopBottomSpacing / 2 - pipe_pixmap_->height(), *pipe_pixmap_);
    }

    painter.end();
}
