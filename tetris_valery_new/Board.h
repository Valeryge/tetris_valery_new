#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Consts.h"
#include "Bomb.h"
using namespace std;


class Board
{
	int min_x;
	bool isDroppingBomb = false;
	bool isDroppingPiece = false;
	Piece currPiece;
	Piece fake;
	enum { POS_FREE, POS_FILLED, BORDER };    // POS_FREE = free position of the board; POS_FILLED = filled position of the board
	int roundCounter;
	int bombFlag;
	Bomb bomb;
	int boardMatrix[BOARD_HEIGHT][BOARD_WIDTH];
	bool isGameOver = false;

public:

	Board() {}

	Board(int x) {
		this->init(x);
	}
	int findBestLocationForBomb();
	int* findBestPositionAndLocation();
	void init(int x);
	bool checkGameOver();
	void updateBoard(Point::Direction dir);
	void printBoard();
	void clearBoard();
	int deleteLines();

	bool isBombFlagOn() const {
		return bombFlag;
	}

	bool getIsGameOver() const {
		return isGameOver;
	}

	int getCurrRound() const {
		return roundCounter;
	}

	int getCurrPiecePositionIndex() const {
		return currPiece.getPosIndex();
	}

	int getCurrPieceLocationIndex() const {
		int x = currPiece.getCornerX() - min_x;;
		return x;
	}

	bool isEmptyLine(const int lineIndex) {
		int j = 1;
		while (j < BOARD_WIDTH - 1 && boardMatrix[lineIndex][j] == POS_FREE) {
			j++;
		}
		if (j == BOARD_WIDTH - 2) //line is empty
			return true;
		return false;
	}

	int getBombLocation() {
		return bomb.getX() - min_x;
	}

private:
	int countNumOfLinesDeleted(int shapeIndex, int posIndex, int col);
	int countFullLines();
	int getHighestPointOfFakePiece(int shapeIndex, int posIndex, int col);
	bool dropFakePieceToPlace(int shapeIndex, int posIndex, int col); //returns false if the location wasnt valid
	bool isPieceOutOfLimits(Piece piece);
	void changeBoardToOrigin();
	int isLineFull(int index); // returns index of column where the hole is - if line is full return -1

	void deleteLine(const int line_index, const int minX, const int maxX); //get line index to delete and move all upper lines one line down.
	void dropPieceIfPossible();
	bool canPiecePrecede(Piece piece);
	bool canPieceMove(Point::Direction dir);
	bool canPieceRotate(Point::Direction dir);
	void storePiece();

	void updateBoardWithBomb(Point::Direction dir);
	bool canBombMove(Point::Direction dir);
	void bombExplosion();
	void dropBombIfPossible();
	void updateBoardWithPiece(Point::Direction dir);
	void randBombOrPiece();
};

#endif