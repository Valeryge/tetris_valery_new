#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "Board.h"
#include "Player.h"

class ComputerPlayer : public Player {
	int wantedPositionIndex, wantedLocationIndex;
	int currRound;
	enum ComputerLevel { BEST, GOOD, NOVICE };
	int missProbability, level;

public:
	ComputerPlayer() {}

	ComputerPlayer(int corner_x, int compLevel = 1) : Player(corner_x) {
		currRound = 0;
		level = compLevel;
		missProbability = calculateProb(level);
	}

	void playMove(int ch) override;
	void playMoveWithPiece();
	void playMoveWithBomb();
	void playWantedMove();
	void findBestPlaceForBomb();
	void findRandomMove();
	void findBestMove();
	int calculateProb(int compLevel);
};

#endif // !COMPUTER_PLAYER_H
