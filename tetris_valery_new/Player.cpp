#include "Player.h"


void Player::printPlayerBoard() {
	board.printBoard();
}

void Player::initPlayersBoard() {
	board.init(cornerX);
	score = 0;
}

bool Player::isGameOver() {
	return board.getIsGameOver();
}
