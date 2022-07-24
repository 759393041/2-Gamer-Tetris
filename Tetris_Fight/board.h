#pragma once
#ifndef BOARD_H
#define BOARD_H

#include<QPoint>
#include"cell.h"

class board
{
public:
    board(){}
    board(int, int, int, int);
    board(const board& bd) { copy(bd); }
    cell& get_a_cell(int, int) const;//创建背景
    void clear_board();//清空背景板
    void set_cell_color(cell &, int);//设定目标格子颜色
    int get_cell_color(cell &);//获得背景中目标格子的颜色
    bool is_full(int);//判断一行是否满了
    bool is_empty(int);//判断一行是否是空的
    bool is_something(int);//判断一行是否有东西
    void clear_row(int);//清空这一行
    void row_cut_paste(int from,int to);//把这行从from行整体移动到to行(所以类似于裁剪)
    const QPoint get_start_location(int, int, int);//获取在棋盘上开始的位置location on board
    board& operator=(const board& bd) { return copy(bd); }
    ~board();

private:
    board& copy(const board&);

private:
    cell *board_space;//背景数组
    int board_h;//背景高度
    int board_w;//背景宽度
};

#endif // BOARD_H
