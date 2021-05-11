#ifndef BOMB_H
#define BOMB_H

#include <stdlib.h>  
#include "Point.h"
#include "Consts.h"
#include <ctime>


class Bomb : public Point {
    int min_x;

public:


    Bomb() {}

    void init(int x) {
        min_x = x + PIECE_START_POS;
        Point::init(min_x, 0, BOMB_SHAPE);
        Point::draw();
    }


    void moveBomb(Point::Direction dir) {
        Point::erase();
        Point::move(dir);
        Point::draw();
    }
};
#endif
