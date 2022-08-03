#pragma once
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "shape.h"


#include "board.h"
#include "shape.h"
class gameEngine
{
public:
    gameEngine(int, int, int, int);//重载构造函数
    ~gameEngine();

   //操作函数：

    board& get_main_bd() { return main_bd; }
    board& get_next_bd() { return next_bd; }
    bool get_move_down_ok() { return move_down_ok; }

    void next_place_a_shape();//下一个放的形状
    void main_place_a_shape();//当前放的形状

    void move_down();
    void move_left();
    void move_right();

    void clear_rows();
    int num_rows_cld();
    void rows_move_down();
    void rotate();
    int compute_score();//计分 可以在此调用信号槽 发送攻击信号
    bool is_game_over();//判断游戏结束
private:

    void traverse_rows(int* cld_rows = NULL);
    int set_shape_color(int);
    shape* place_a_shape(board &, int, int, int);
    bool is_moveable(int, int, bool);
    void move(int, int);
    board main_bd;
    board next_bd;
    shape* tracked_shape;
    bool move_down_ok;
    int m_ishape;

};

#endif // GAME_ENGINE_H
