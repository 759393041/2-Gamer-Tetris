#pragma once
#ifndef ZSHAPE_H
#define ZSHAPE_H
#include"cell.h"
#include"board.h"
#include"shape.h"
#include<QPoint>
class zshape:public shape
{

public:
    zshape(cell &, board &);
    ~zshape();

private:
    virtual void compute_rotate_positions() override;
};

#endif // ZSHAPE_H
