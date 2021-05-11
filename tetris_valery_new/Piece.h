#ifndef _PIECE_H_
#define _PIECE_H_

#include <stdlib.h>  
#include "Point.h"
#include "Consts.h"


class Piece {
	char shape[SHAPE_SIZE][SHAPE_SIZE];
	Point points[SHAPE_SIZE];
	int corner_x;
	int corner_y;
	int shapeIndex = 0, posIndex = 0;

public:

	Piece() {}

	Piece(int _x, int _y = 0);

	void init(int _x);
	void rotateCounterClockwise();
	void erasePiece();
	void drawPiece();
	void movePiece(Point::Direction dir);
	void rotateClockwise();
	void initWithParams(int _x, int shapeInd, int posInd);
	int getCornerX() const { return corner_x; };
	int getCornerY() const { return corner_y; };
	int getShapeIndex() const { return shapeIndex; }
	int getPosIndex() const { return posIndex; };
	bool isPieceRepeatsItself();
	Point* getPointsArr() {
		return points;
	}
};

#endif