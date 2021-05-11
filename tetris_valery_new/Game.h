#ifndef _GAME_H
#define _GAME_H

#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Consts.h"

class Game {
	Player* leftPlayer;
	Player* rightPlayer;
	bool isGameOver;

	int winner;

public:
	enum playerSide { RIGHT, LEFT, NONE };

	Game() {
		isGameOver = false;
	}

	void initGame(int humanPlayersNum, int computersLevel);

	int getWinner() {
		return winner;
	}

	bool runGame(bool isNewGame, int humanPlayersNum = -1, int computersLevel = 1);


private:
	void executeMoves(char leftPlayerMove, char rightPlayerMove);
	int leftPlayerKeys[5] = { LEFT_PLAYER_LEFT_KEY , LEFT_PLAYER_RIGHT_KEY , LEFT_PLAYER_CLOCKWISE_KEY ,  LEFT_PLAYER_COUNTERCLOCKWISE_KEY , LEFT_PLAYER_DROP_KEY };
	int rightPlayerKeys[5] = { RIGHT_PLAYER_LEFT_KEY , RIGHT_PLAYER_RIGHT_KEY , RIGHT_PLAYER_CLOCKWISE_KEY ,  RIGHT_PLAYER_COUNTERCLOCKWISE_KEY , RIGHT_PLAYER_DROP_KEY };
	int checkKeysOwner(char ch);
	bool checkIsGameOver();
	int gameOverManager(bool isGameOverLeftPlayer, bool isGameOverRightPlayer);
	int getWinnerByScore();
	void scoreManager();
};

#endif // !_GAME_H
