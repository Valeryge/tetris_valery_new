#include "ComputerPlayer.h"


int ComputerPlayer::calculateProb(int compLevel) {
	switch (compLevel) {
	case ComputerLevel::BEST:
		return 0;
	case ComputerLevel::GOOD:
		return 10;
	default:
		return 30;
	}
}

void ComputerPlayer::playMove(int ch) {
	if (currRound < Player::board.getCurrRound()) {
		int random = rand() % 100;
		if (board.isBombFlagOn()) {
			if (level == ComputerLevel::BEST) { // find best place for bomb
				findBestPlaceForBomb();
			}
			else {
				this->findRandomMove();
			}
		}
		else { // find place for regular piece
			if (random < missProbability) {
				this->findRandomMove();
			}
			else {
				this->findBestMove();
			}
		}

		currRound++;
	}
	this->playWantedMove();
	int deletedLines = board.deleteLines();
	if (deletedLines > 0)
		score += deletedLines;
	return;
}

void ComputerPlayer::findBestMove() {
	int* best = Player::board.findBestPositionAndLocation();
	wantedPositionIndex = best[0];
	wantedLocationIndex = best[1];
}

void ComputerPlayer::findRandomMove() {
	srand(time(0));

	wantedPositionIndex = rand() % 4;
	wantedLocationIndex = rand() % 10;
}

void ComputerPlayer::findBestPlaceForBomb() {
	wantedLocationIndex = Player::board.findBestLocationForBomb();
}

void ComputerPlayer::playWantedMove() {
	if (board.isBombFlagOn()) {
		this->playMoveWithBomb();
	}
	else {
		this->playMoveWithPiece();
	}
}

void ComputerPlayer::playMoveWithBomb() {
	int x = board.getBombLocation();
	if (board.getBombLocation() < wantedLocationIndex) {
		board.updateBoard(Point::RIGHT);
	}
	else if (board.getBombLocation() > wantedLocationIndex) {
		board.updateBoard(Point::LEFT);
	}
	board.updateBoard(Point::NONE);
}

void ComputerPlayer::playMoveWithPiece() {
	if (Player::board.getCurrPiecePositionIndex() > wantedPositionIndex) {
		board.updateBoard(Point::CLOCK_ROTATE);
	}
	else if (Player::board.getCurrPiecePositionIndex() < wantedPositionIndex) {
		board.updateBoard(Point::COUNTER_CLOCK_ROTATE);
	}
	else if (Player::board.getCurrPieceLocationIndex() < wantedLocationIndex) {
		board.updateBoard(Point::RIGHT);
	}
	else if (Player::board.getCurrPieceLocationIndex() > wantedLocationIndex) {
		board.updateBoard(Point::LEFT);
	}
	board.updateBoard(Point::NONE);
}