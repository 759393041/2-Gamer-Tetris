#ifndef OPPONENTS_WINDOW_H
#define OPPONENTS_WINDOW_H

#include <QWidget>

#include"game_engine.h"

namespace Ui {
class opponents_window;
}

class opponents_window : public QWidget
{
    Q_OBJECT

public:
    explicit opponents_window(QWidget *parent = nullptr);
    ~opponents_window();

     void paintEvent(QPaintEvent *);
public slots:
    void slot_ServerDealData(unsigned int Socket,char*,int);

private:

    Ui::opponents_window *ui;

    gameEngine* ge_opponents;
public:
};


#endif // OPPONENTS_WINDOW_H
