#ifndef _PLAYER_H
#define _PLAYER_H

#include "Board.h"
#include "Consts.h"

class Player {
	enum positions { leftPlayer = 0, rightPlayer = BOARD_WIDTH + 2 };

protected:
	int score;
	Board board;
	int cornerX;

public:
	Player() {}

	Player(int corner_x) {
		cornerX = corner_x;
		score = 0;
		board = Board(corner_x);
	}

	int getScore() const {
		return score;
	}

	void initPlayersBoard();
	void printPlayerBoard();
	virtual void playMove(int ch = Point::NONE) = 0;
	bool isGameOver();
};

#endif // !_PLAYER_H
