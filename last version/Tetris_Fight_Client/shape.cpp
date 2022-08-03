#include "shape.h"

//shape::
//shape(cell &, board& bd);
shape::shape(cell& first_cell, board& bd): m_bd(bd)
{
    color = NO_COLOR;
    //无论是啥方块 都是四个块 反正弄出来先给空间
    for(int i = 0; i < NUM_OF_CELLS; i++)
    {
        cells[i] = cell();
    }

    cells[FIRST_CELL] = first_cell;
    which_position = 0;
}

void shape::rotate()
{
    //计算要旋转的位置
    compute_rotate_positions();
    //记录旋转的次数
    which_position++;

    //对旋转次数取余4，得到0123 四个形态
    which_position = which_position % NUMBER_OF_ROTATE_POSITIONS;

    if(is_vaild_position(which_position))//预先对旋转后的位置做判断：超出棋盘或位置被占都不能转
    {
        //能转 就转
        for(int i = 0; i < NUM_OF_CELLS; i++)
        {
            int r = rotate_positions[which_position][i].x();
            int c = rotate_positions[which_position][i].y();

            cells[i] = m_bd.get_a_cell(r, c);
        }
    }
    else
    {
        //转不了 旋转次数回退
        which_position--;
    }
}

bool shape::is_vaild_position(int which)
{
    bool is_vaild = false;

    for(int i = 0; i < NUM_OF_CELLS; i++)
    {
        QPoint tmp = rotate_positions[which][i];

        int x = tmp.x();
        int y = tmp.y();

        if(x >= 0 && y >= 0 && x < MAIN_BOARD_HEIGHT && y < MAIN_BOARD_WIDTH && m_bd.get_a_cell(x, y).get_color() == NO_COLOR)
            is_vaild = true;
        else
        {
            is_vaild = false;
            break;
        }
    }

    return is_vaild;
}

void shape::compute_rotate_positions()
{
    for(int i = 0; i < NUMBER_OF_ROTATE_POSITIONS; i++)
    {
        rotate_positions[i][SECOND_CELL] = cells[SECOND_CELL].get_location();
    }
}

shape::~shape()
{

}
