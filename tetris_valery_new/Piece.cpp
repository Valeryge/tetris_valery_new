#include "Piece.h"


Piece::Piece(int _x, int _y) {
    corner_x = _x + PIECE_START_POS;
    corner_y = _y;
    for (int i = 0; i < SHAPE_SIZE; i++) {
        for (int j = 0; j < SHAPE_SIZE; j++) {
            shape[i][j] = 0;
        }
    }
}

void Piece::init(int _x) {
    corner_x = _x + PIECE_START_POS;
    corner_y = 0;
    int pointsIndex = 0;

    shapeIndex = rand() % 7;
    posIndex = rand() % 4;

    for (int i = 0; i < SHAPE_SIZE; i++) {
        for (int j = 0; j < SHAPE_SIZE; j++) {
            shape[i][j] = shapeOptions[shapeIndex][posIndex][i][j];
            if (shape[i][j]) {
                points[pointsIndex].init(corner_x + i, corner_y + j);
                pointsIndex++;
            }
        }
    }
}

bool Piece::isPieceRepeatsItself() {
    for (int i = 0; i < SHAPE_SIZE; i++) {
        for (int j = 0; j < SHAPE_SIZE; j++) {
            if (shapeOptions[shapeIndex][0][i][j] != shapeOptions[shapeIndex][2][i][j])
                return false;
        }
    }
    return true;
}

void Piece::drawPiece() {
    for (int i = 0; i < SHAPE_SIZE; i++) {
        points[i].draw();
    }
}

void Piece::erasePiece() {
    for (int i = 0; i < SHAPE_SIZE; i++) {
        points[i].erase();
    }
}

void Piece::rotateCounterClockwise() {
    int pointsIndex = 0;
    this->erasePiece();
    posIndex = (posIndex + 1) % 4;

    for (int i = 0; i < SHAPE_SIZE; i++) {
        for (int j = 0; j < SHAPE_SIZE; j++) {
            shape[i][j] = shapeOptions[shapeIndex][posIndex][i][j];
            if (shape[i][j]) {
                points[pointsIndex].init(corner_x + i, corner_y + j);
                pointsIndex++;
            }
        }
    }
}

void Piece::rotateClockwise() {
    int pointsIndex = 0;
    this->erasePiece();
    if (posIndex == 0) {
        posIndex = 3;
    }
    else {
        posIndex = posIndex - 1;
    }

    for (int i = 0; i < SHAPE_SIZE; i++) {
        for (int j = 0; j < SHAPE_SIZE; j++) {
            shape[i][j] = shapeOptions[shapeIndex][posIndex][i][j];
            if (shape[i][j]) {
                points[pointsIndex].init(corner_x + i, corner_y + j);
                pointsIndex++;
            }
        }
    }
}

void Piece::movePiece(Point::Direction dir) {
    for (int i = NUM_OF_POINTS - 1; i >= 0; i--) {
        points[i].erase();
        points[i].move(dir);
    }
    switch (dir) {
    case Point::NONE: {
        corner_y++;
        break;
    }
    case Point::LEFT: {
        corner_x--;
        break;
    }
    case Point::RIGHT: {
        corner_x++;
        break;
    }
    default:
        break;
    }
}


void Piece::initWithParams(int _x, int shapeInd, int posInd) {
    corner_x = _x;
    corner_y = 0;

    int pointsIndex = 0;

    for (int i = 0; i < SHAPE_SIZE; i++) {
        for (int j = 0; j < SHAPE_SIZE; j++) {
            shape[i][j] = shapeOptions[shapeInd][posInd][i][j];
            if (shape[i][j]) {
                points[pointsIndex].init(corner_x + i, corner_y + j);
                pointsIndex++;
            }
        }
    }
}
