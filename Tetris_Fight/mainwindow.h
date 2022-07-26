#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<game_engine.h>





QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    void paintEvent(QPaintEvent *) override;
    void keyReleaseEvent(QKeyEvent * event) override;
    void keyPressEvent(QKeyEvent * event) override;
    void timerEvent(QTimerEvent *event)override;

public slots:
    void start_game();
    void new_game();

private:
    Ui::MainWindow *ui;
    gameEngine* ge;
    int timer_pressdown_id;
    int timer_releaseup_id;
    bool game_is_started;

};
#endif // MAINWINDOW_H
