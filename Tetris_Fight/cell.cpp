#include "cell.h"




cell::cell(QPoint &_location, QPointF &_position, int _color ) //重载构造函数，给方块的两个坐标和颜色赋值
{
    location_on_board = _location;
    position_on_window = _position;
    color = _color;

}
cell& cell::copy(const cell& c)//方块拷贝
{

    this->color = c.color;
    this->position_on_window = c.position_on_window;
    this->location_on_board = c.location_on_board;

    return *this;
}

QColor cell::draw_cell_color() const //根据类内的color 给颜色，所以不用参数,用返回值
{
    QColor qcolor;
    switch(color)
    {
    case RED:
        qcolor = QColor("red");
        break;
    case YELLOW:
        qcolor = QColor("yellow");
        break;
    case BLUE:
        qcolor = QColor("blue");
        break;
    case GRAY:
        qcolor = QColor("gray");
        break;
    case BLACK:
        qcolor = QColor("black");
        break;
    case PURPLE:
        qcolor = QColor("purple");
        break;
    case ORANGE:
        qcolor = QColor("orange");
        break;
    default:
        qcolor = QColor("transparent");
        break;
    }

    return qcolor;
}


