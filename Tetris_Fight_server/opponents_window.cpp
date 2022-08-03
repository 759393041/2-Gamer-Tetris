#include "opponents_window.h"
#include "ui_opponents_window.h"
#include<QPainter>
#include"public_define.h"
#include<QDebug>
#include"package.h"

opponents_window::opponents_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::opponents_window)
{
    ui->setupUi(this);
    ge_opponents=new gameEngine(ui->frm_main->x(),ui->frm_main->y(),ui->frm_next->x(),ui->frm_next->y());
   //这边只接收

}

void opponents_window::slot_ServerDealData(unsigned int Socket,char*buf,int )
{


    BoardTrasInfo* C_TO_S=(BoardTrasInfo*)buf;
    ge_opponents->get_main_bd().set_cell_color(C_TO_S->opponents_colorful_cell,C_TO_S->opponents_colorful_cell.get_color());
   opponents_window::update();
   delete []buf;

}
void opponents_window::paintEvent(QPaintEvent *)
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
                cell acell = (n == NEXT_BOARD ? ge_opponents->get_next_bd().get_a_cell(r, c) : ge_opponents->get_main_bd().get_a_cell(r, c));
                QPointF position = acell.get_position();
                QSizeF sizef(CELL_LENGTH, CELL_LENGTH);
                QRectF rectf(position, sizef);
                QColor color = acell.draw_cell_color();
                painter.fillRect(rectf, color);
            }
        }
    }


}
opponents_window::~opponents_window()
{
    delete ui;
}
