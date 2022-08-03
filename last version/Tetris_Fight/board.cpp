#include "board.h"


board::board(int x, int y, int board_height, int board_width)
{
    board_h = board_height;
    board_w = board_width;

    board_space = new cell[board_height * board_width];
        //初始化背景板
    for(int h = 0; h < board_height; h++)
    {
        for(int w = 0; w < board_width; w++)
        {
            float _x = float(w) * float(CELL_LENGTH) + float(x);
            float _y = float(h) * float(CELL_LENGTH) + float(y);

            QPoint location_on_board(h, w);
            QPointF position_on_window(_x, _y);

            board_space[h * board_width + w] = cell(location_on_board, position_on_window);
        }
    }
}

cell& board::get_a_cell(int r, int c) const
{
    return board_space[r * board_w + c];
}
void board::clear_board()
{
    //遍历清空
    for(int r = 0; r < board_h; r++)
    {
        for(int c = 0; c < board_w; c++)
        {
            board_space[r * board_w + c].set_color(NO_COLOR);
        }
    }
}



//设定目标格子的颜色
void board::set_cell_color(cell& _cell, int _color)
{
    int _index = _cell.get_location().x() * board_w + _cell.get_location().y();
    board_space[_index].set_color(_color);
}

//获得目标格子的颜色
int board::get_cell_color(cell& _cell)
{
    int _index = _cell.get_location().x() * board_w + _cell.get_location().y();
    return board_space[_index].get_color();
}


//判断某一行(num这一行)是否满了
bool board::is_full(int num)
{
    int count = 0;

    for(int c = 0; c < board_w; c++)
    {
        if(board_space[num * board_w + c].get_color() != NO_COLOR)
        {
                count++;
        }

    }

    return (count == board_w);
}

//判断某一行(num这一行)是否都没格子

bool board::is_empty(int num)
{
    int count = 0;
    for(int c = 0; c < board_w; c++)
    {
        if(board_space[num * board_w + c].get_color() == NO_COLOR)
        {
                count++;
        }


    }
    return (count == board_w);
}

//判断某一行有没有格子(不满也不空，那就是有)
bool board::is_something(int num)
{
    return (!is_empty(num) && !is_full(num));
}
//清空这一行：把颜色变回背景色就完事了
void board::clear_row(int num)
{
    for(int c = 0; c < board_w; c++)
    {
        board_space[num * board_w + c].set_color(NO_COLOR);
    }
}
//把from行移动到to行(所以类似于裁剪)
void board::row_cut_paste(int from, int to)
{
    for(int c = 0; c < board_w; c++)
    {
        //得到源行的颜色
        int color = board_space[from * board_w + c].get_color();
        //目标行变成源行的颜色
        board_space[to * board_w + c].set_color(color);
        //源行变为无色
        board_space[from * board_w + c].set_color(NO_COLOR);
    }
}

board& board::copy(const board&bd)
{
    board_h = bd.board_h;
    board_w = bd.board_w;

    board_space = new cell[board_h * board_w];

    for(int r = 0; r < board_h; r++)
    {
        for(int c = 0; c < board_w; c++)
        {
            board_space[r * board_w + c] = bd.board_space[r * board_w + c];
        }
    }

    return *this;
}

//const QPoint get_start_location(int, int, int);
const QPoint board::get_start_location(int _shape, int hrz, int vrtx)
{
    int h = 0;
    int w = 0;
// 为什么J_L_VRTX_START_LOCATION是2，因为是从0开始计数哒 以此类推 实际上L是三个格子长度
//想要把整个图片 显示在最顶端，就要提前预留好空间，所以L 和J 一组 以此类推
    switch (_shape)
    {
    case L_SHAPE:
        w = (hrz == HRZ_CENTER ? board_w / HALF : ALL_HRZ_START_LOCATION);
        h = (vrtx == VRTX_CENTER ? board_w / HALF + BIAS : J_L_VRTX_START_LOCATION);
        break;

    case J_SHAPE:
        w = (hrz == HRZ_CENTER ? board_w / HALF - BIAS : ALL_HRZ_START_LOCATION);
        h = (vrtx == VRTX_CENTER ? board_w / HALF + BIAS : J_L_VRTX_START_LOCATION);
        break;

    case I_SHAPE:
        w = (hrz == HRZ_CENTER ? board_w / HALF : ALL_HRZ_START_LOCATION);
        h = (vrtx == VRTX_CENTER ? board_w / HALF + BIAS : I_VRTX_START_LOCATION);
        break;

    case Z_SHAPE:
        w = (hrz == HRZ_CENTER ? board_w / HALF + BIAS : ALL_HRZ_START_LOCATION);
        h = (vrtx == VRTX_CENTER ? board_w / HALF : S_O_Z_T_VRTX_START_LOCATION);
        break;

    case T_SHAPE:
        w = (hrz == HRZ_CENTER ? board_w / HALF : ALL_HRZ_START_LOCATION);
        h = (vrtx == VRTX_CENTER ? board_w / HALF : S_O_Z_T_VRTX_START_LOCATION);
        break;

    case S_SHAPE:
    case O_SHAPE:
        w = (hrz == HRZ_CENTER ? board_w / HALF - BIAS : ALL_HRZ_START_LOCATION);
        h = (vrtx == VRTX_CENTER ? board_w / HALF : S_O_Z_T_VRTX_START_LOCATION);
        break;

    default:
        break;
    }

    return QPoint(h, w);
}



board::~board()
{
    delete[] board_space;
    board_space = NULL;
}
