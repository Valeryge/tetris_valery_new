#ifndef _MENU_H
#define _MENU_H

#pragma once
#include <iostream> 
using namespace std;
#include "Gotoxy.h"
#include <conio.h>
#include "Consts.h"
#include "Game.h"

class Menu {
	Game game;
	bool isGamePaused = false;

public:
	void runMenu();
	void printMenu(bool isGamePaused = false);
	void printInstructionsAndKeys(bool isGamePaused = false);
	void clearScreen();
	void printGameOver();
	void printWinner(int winner);
	void gameOver(int winner);
	int printLevelSelection();
};

#endif // !_MENU_H
