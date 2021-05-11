#include "Game.h"
#include "Player.h"

void Game::initGame(int humanPlayersNum, int computersLevel) {
	switch (humanPlayersNum) {
	case 2: {
		leftPlayer = new HumanPlayer(LEFT_PLAYER_POS, leftPlayerKeys);
		rightPlayer = new HumanPlayer(RIGHT_PLAYER_POS, rightPlayerKeys);
		break;
	}
	case 1: {
		leftPlayer = new HumanPlayer(LEFT_PLAYER_POS, leftPlayerKeys);
		rightPlayer = new ComputerPlayer(RIGHT_PLAYER_POS, computersLevel);
		break;
	}
	default: {
		leftPlayer = new ComputerPlayer(LEFT_PLAYER_POS);
		rightPlayer = new ComputerPlayer(RIGHT_PLAYER_POS);
		break;
	}
	}
	isGameOver = false;
	winner = playerSide::NONE;
	leftPlayer->initPlayersBoard();
	rightPlayer->initPlayersBoard();
}


// this function returns true is game is paused (escape was pressed) and false if the game is over
bool Game::runGame(bool isNewGame, int humanPlayersNum, int computersLevel) {
	char ch = '0';
	char leftPlayerMove, rightPlayerMove;
	if (isNewGame) {
		this->initGame(humanPlayersNum, computersLevel);
	}
	leftPlayer->printPlayerBoard();
	rightPlayer->printPlayerBoard();

	while (!isGameOver) {
		leftPlayerMove = '0';
		rightPlayerMove = '0';
		for (int i = 0; i < 20; i++) {
			if (_kbhit()) {
				ch = _getch();
				if (ch == ESCAPE) {
					return true;
				}

				int side = checkKeysOwner(ch);
				if (side == LEFT) {
					leftPlayerMove = ch;
				}
				else if (side == RIGHT) {
					rightPlayerMove = ch;
				}
			}
		}

		executeMoves(leftPlayerMove, rightPlayerMove);
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); // flushing input buffer
		Sleep(SLEEP_TIME);
		this->scoreManager();
		if (checkIsGameOver()) {
			return false;
		}
	}
}

int Game::checkKeysOwner(char ch) {
	for (size_t i = 0; i < 5; i++)
	{
		if (ch == leftPlayerKeys[i] || ch == leftPlayerKeys[i] + 32)
			return playerSide::LEFT;
		else if (ch == rightPlayerKeys[i] || ch == rightPlayerKeys[i] + 32)
		{
			return playerSide::RIGHT;
		}
	}
	return playerSide::NONE;
}

void Game::executeMoves(char leftPlayerMove, char rightPlayerMove) {
	if (leftPlayerMove != '0') {
		leftPlayer->playMove(leftPlayerMove);
	}
	else {
		leftPlayer->playMove();
	}

	if (rightPlayerMove != '0') {
		rightPlayer->playMove(rightPlayerMove);
	}
	else {
		rightPlayer->playMove();
	}

}

bool Game::checkIsGameOver() {
	bool isGameOverLeftPlayer = leftPlayer->isGameOver();
	bool isGameOverRightPlayer = rightPlayer->isGameOver();

	if (isGameOverLeftPlayer || isGameOverRightPlayer) {
		this->winner = gameOverManager(isGameOverLeftPlayer, isGameOverRightPlayer);
		delete leftPlayer;
		delete rightPlayer;
		return true;
	}
	return false;
}

void Game::scoreManager() {
	gotoxy(40, 0);
	printf("LEFT PLAYER SCORE: %d RIGHT PLAYER SCORE: %d \n", leftPlayer->getScore(), rightPlayer->getScore());
}


int Game::gameOverManager(bool isGameOverLeftPlayer, bool isGameOverRightPlayer) {

	isGameOver = true;
	if (isGameOverLeftPlayer && isGameOverRightPlayer)
		return this->getWinnerByScore();
	if (isGameOverLeftPlayer && !isGameOverRightPlayer)
		return playerSide::RIGHT;
	else
		return playerSide::LEFT;
}

int Game::getWinnerByScore() {

	int rightPlayerScore = rightPlayer->getScore();
	int leftPlayerScore = leftPlayer->getScore();
	if (rightPlayerScore < leftPlayerScore)
		return playerSide::LEFT;
	else if (rightPlayerScore > leftPlayerScore)
		return playerSide::RIGHT;
	else
		return playerSide::NONE;
}
