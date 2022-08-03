#ifndef ISHAPE_H
#define ISHAPE_H
#pragma once
#include "shape.h"
#include "board.h"

class ishape : public shape
{
public:
    ishape(cell &, board &);
    ~ishape();

private:
    virtual void compute_rotate_positions() override;
};

#endif // ISHAPE_H
