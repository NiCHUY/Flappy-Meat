#ifndef ACHIVEMENTWINDOW_H
#define ACHIVEMENTWINDOW_H

#include <QWidget>

namespace Ui {
class achivementwindow;
}

class achivementwindow : public QWidget
{
    Q_OBJECT

public:
    explicit achivementwindow(QWidget *parent = nullptr);
    ~achivementwindow();

private:
    Ui::achivementwindow *ui;
};

#endif // ACHIVEMENTWINDOW_H
