#include "Player.h"


class HumanPlayer : public Player {
	int leftKey, rightKey, rotateColckWiseKey, rotateCounterClockWiseKey, dropKey;


public:
	HumanPlayer(int corner_x, int* keys) : Player(corner_x) {
		this->setPlayerKeys(keys);
	}

	void playMove(int ch) override;


private:
	void setPlayerKeys(int* keys) {
		leftKey = keys[0];
		rightKey = keys[1];
		rotateColckWiseKey = keys[2];
		rotateCounterClockWiseKey = keys[3];
		dropKey = keys[4];
	}
}; 