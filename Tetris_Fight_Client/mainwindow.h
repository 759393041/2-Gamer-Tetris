#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<game_engine.h>
#include"INetMediator.h"
#include"package.h"
#include"opponents_window.h"


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
    int re=-1;
    int ps=-1;
public slots:
    void start_game();
    void new_game();
public:
    opponents_window* ow;
private:
    Ui::MainWindow *ui;
    gameEngine* ge;
    int timer_pressdown_id;
    int timer_releaseup_id;
    bool game_is_started;
    INetMediator* m_client;
};
#endif // MAINWINDOW_H
