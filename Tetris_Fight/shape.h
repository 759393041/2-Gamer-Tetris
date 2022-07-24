#pragma once
#ifndef SHAPE_H
#define SHAPE_H
#include"cell.h"
#include"board.h"

class shape
{


public:
    shape(cell &, board& bd);//初始化形状
    virtual ~shape() = 0;
    virtual void rotate();//形状旋转函数
    int get_color() { return color; }
    cell& get_a_cell(int n) { return cells[n]; }
    void set_a_cell(int n, cell& _cell) { cells[n] = _cell; }//设置方块

    //疑问 是否需要加入染色操作函数
    //答案 不需要，在构造的时候就可以给了，而且还有继承

protected:
    virtual void compute_rotate_positions();
    bool is_vaild_position(int);
    int color;//形状的颜色 每个形状颜色各不相同
    cell cells[NUM_OF_CELLS];//形状的空间
    QPoint rotate_positions[NUMBER_OF_ROTATE_POSITIONS][NUM_OF_CELLS];
    int which_position;
    board m_bd;
};

#endif // SHAPE_H
