#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>

#include <vector>

#include "pipe.h"

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

    void paintEvent(QPaintEvent* paint_event) override;

private:
    static const int kPipesCount;
    static const int kDistanceBetweenPipes;
    static const int kMinPipeHeight;
    const static int kTopBottomSpacing;

    Ui::MainWindow *ui;
    std::vector<Pipe> pipes;
    QPixmap* pipe_pixmap_;
};
#endif // MAINWINDOW_H
