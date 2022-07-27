#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTimer>
#include<QKeyEvent>
#include<QPainter>
#include<QEvent>
#include<QTimerEvent>
#include<QDebug>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ge = new gameEngine(ui->frm_main->x(), ui->frm_main->y(), ui->frm_next->x(), ui->frm_next->y());
    connect(ui->btn_start, SIGNAL(clicked(bool)), this, SLOT(start_game()));
    connect(ui->btn_new, SIGNAL(clicked(bool)), this, SLOT(new_game()));
    setFocusPolicy(Qt::StrongFocus);
    game_is_started = false;
}




void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    int key = event->key();
    if(game_is_started)
    {
        switch (key)
        {
         case Qt::Key_Down:
            re=timer_releaseup_id;
            if(re!=-1)
            {
                killTimer(re);
            }
            timer_releaseup_id=startTimer(1000);
            break;
           case Qt::Key_Up:
            if(ge->get_move_down_ok())
            {
                ge->rotate();
                update();
            }
            break;

        default:
            break;
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if(ge->get_move_down_ok() && game_is_started)
    {
        int key = event->key();

        switch (key)
        {
        case Qt::Key_Left:
            ge->move_left();
            break;

        case Qt::Key_Right:
            ge->move_right();
            break;

        case Qt::Key_Down:
            ge->move_down();
            ps=timer_pressdown_id;
            if(ps!=-1)
            {
                killTimer(ps);
            }
            timer_pressdown_id=startTimer(100);

            break;
        }
    }

    update();
}
void MainWindow::paintEvent(QPaintEvent *)
{
    int h = MAIN_BOARD_HEIGHT;
    int w = MAIN_BOARD_WIDTH;

    QPainter painter(this);

    for(int n = 0; n < NUM_OF_BOARDS; n++)
    {
        h = (n == MAIN_BOARD ? h : NEXT_BOARD_HEIGHT);
        w = (n == MAIN_BOARD ? w : NEXT_BOARD_WIDTH);

        for(int r = 0; r < h; r++)
        {
            for(int c = 0; c < w; c++)
            {
                //Draw a rectangle in the cell
                cell acell = (n == NEXT_BOARD ? ge->get_next_bd().get_a_cell(r, c) : ge->get_main_bd().get_a_cell(r, c));
                QPointF position = acell.get_position();
                QSizeF sizef(CELL_LENGTH, CELL_LENGTH);
                QRectF rectf(position, sizef);
                QColor color = acell.draw_cell_color();
                painter.fillRect(rectf, color);
            }
        }
    }
}
void MainWindow::timerEvent(QTimerEvent *event)
{

    if(event->timerId()==timer_pressdown_id)
    {
        if(ge->get_move_down_ok())
        {

        }
        else
        {
            if(ge->num_rows_cld() > 0)
            {
                int score = ge->compute_score();
                score += ui->lbl_score->text().toInt();
                ge->clear_rows();
                ge->rows_move_down();
                ui->lbl_score->setText(QString::number(score));
            }

            if(ge->is_game_over())
            {
                killTimer(event->timerId());
                QMessageBox::information(this,"游戏结束","Game Over",QMessageBox::Yes);
                return;
            }

            ge->main_place_a_shape();
            ge->get_next_bd().clear_board();
            ge->next_place_a_shape();
        }
        update();
    }

    if(event->timerId()==timer_releaseup_id)
    {
        if(ge->get_move_down_ok())
        {
             ge->move_down();

        }
        else
        {
            if(ge->num_rows_cld() > 0)
            {
                int score = ge->compute_score();
                score += ui->lbl_score->text().toInt();
                ge->clear_rows();
                ge->rows_move_down();
                ui->lbl_score->setText(QString::number(score));
            }
            if(ge->is_game_over())
            {
                killTimer(event->timerId());


                return;
            }

            ge->main_place_a_shape();
            ge->get_next_bd().clear_board();
            ge->next_place_a_shape();
        }


        update();

    }
}


void MainWindow::start_game()
{
    ge->next_place_a_shape();
    ge->main_place_a_shape();
    ge->get_next_bd().clear_board();
    ge->next_place_a_shape();
    update();
    ui->btn_start->setEnabled(false);

    timer_releaseup_id=startTimer(1000);
    game_is_started = true;
}

void MainWindow::new_game()
{


    game_is_started = false;
    killTimer(timer_releaseup_id);

    delete ge;
    ge = NULL;

    ge = new gameEngine(ui->frm_main->x(), ui->frm_main->y(), ui->frm_next->x(), ui->frm_next->y());

    ui->lbl_score->setText("0");
    ui->btn_start->setEnabled(true);

    update();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ge;
    ui = NULL;
    ge = NULL;
}
