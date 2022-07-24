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

shape::~shape()
{

}


//virtual void rotate();//形状旋转函数


//int get_color() { return color; }


//cell& get_a_cell(int n) { return cells[n]; }


//void set_a_cell(int n, cell& _cell) { cells[n] = _cell; }//设置方块
