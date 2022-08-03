#include "opponents_window.h"
#include "ui_opponents_window.h"
#include<QPainter>
#include"public_define.h"
#include"package.h"

opponents_window::opponents_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::opponents_window)
{
    ui->setupUi(this);
    ge_opponents=new gameEngine(ui->frm_main->x(),ui->frm_main->y(),ui->frm_next->x(),ui->frm_next->y());
   //这边只接收



}

void opponents_window::slot_ClientDealData(unsigned int socket,char*buf,int )
{
    uint var = 0;
    BoardTrasInfo* S_TO_C=(BoardTrasInfo*)buf;
    if(S_TO_C->mark==MAIN_BOARD_TRASFORM_MARK)
    {
        for (var = 0; var < S_TO_C->opponents_colorful_cell.size(); ++var)
        {

            ge_opponents->get_main_bd().set_cell_color(S_TO_C->opponents_colorful_cell[var],S_TO_C->opponents_colorful_cell[var].get_color());
        }
    }
    update();
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
