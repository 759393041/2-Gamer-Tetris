#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ge = new gameEngine(ui->frm_main->x(), ui->frm_main->y(), ui->frm_next->x(), ui->frm_next->y());
    timer = new QTimer();
    timer->setInterval(SLOW_TIME_INTERVAL);
    connect(ui->btn_start, SIGNAL(clicked(bool)), this, SLOT(start_game()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_start()));
    connect(ui->btn_new, SIGNAL(clicked(bool)), this, SLOT(new_game()));
    setFocusPolicy(Qt::StrongFocus);
    game_is_started = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

