#pragma once

#ifndef CELL_H
#define CELL_H

#include"public_define.h"
#include<QPoint>
#include<QColor>
class cell
{
public:

    cell() {}//构造函数
    cell(QPoint &, QPointF &, int _color = NO_COLOR);//重载构造函数，给方块的两个坐标和颜色赋值
    cell(const cell& c) { copy(c); }//拷贝构造



    //操作函数：

    cell& copy(const cell&);//方块拷贝
    cell& operator=(const cell& c) { return copy(c); }//方块拷贝，但是是重载操作符

    void set_color(int _color) { color = _color; }//设置方块的颜色
    QColor draw_cell_color() const;//根据类内的color 给颜色，所以不用参数
    int get_color() { return color; }
    QPointF& get_position() { return position_on_window; }
    QPoint& get_location() { return location_on_board; }




    //变量
private:

    QPointF position_on_window;//方块在窗口上的位置
    QPoint location_on_board;//方块在棋盘(格格)上的位置
    int color;//方块的颜色

};

#endif // CELL_H
