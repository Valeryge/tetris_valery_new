#include "Menu.h"


void Menu::runMenu() {
	this->printMenu();
	int level = 0;
	char ch = 0;

	while (ch != EXIT_KEY) {
		ch = _getch();

		switch (ch)
		{
		case START_NEW_GAME_HUMAN_VS_HUMAN:
			this->clearScreen();
			isGamePaused = game.runGame(true, 2);
			if (!isGamePaused) {
				int winner = game.getWinner();
				this->gameOver(winner);
			}
			this->printMenu(isGamePaused);
			break;
		case START_NEW_GAME_HUMAN_VS_COMPUTER:
			level = this->printLevelSelection();
			isGamePaused = game.runGame(true, 1, level);
			if (!isGamePaused) {
				int winner = game.getWinner();
				this->gameOver(winner);
			}
			this->printMenu(isGamePaused);
			break;
		case START_NEW_GAME_COMPUTER_VS_COMPUTER:
			this->clearScreen();
			isGamePaused = game.runGame(true, 0);
			if (!isGamePaused) {
				int winner = game.getWinner();
				this->gameOver(winner);
			}
			this->printMenu(isGamePaused);
			break;
		case STOP_AND_CONTINUE_KEY:
			this->clearScreen();
			isGamePaused = game.runGame(false);
			if (isGamePaused) {
				this->printMenu(isGamePaused);
			}
			else {
				int winner = game.getWinner();
				this->gameOver(winner);
			}
			break;
		case INFO_KEY:
			this->printInstructionsAndKeys();
			this->printMenu(isGamePaused);
			break;
		}
	}
}


int Menu::printLevelSelection() {
	this->clearScreen();
	bool gotLevel = false;
	cout << " Select Computers Level - " << endl;
	cout << " " << endl;
	cout << "(1) ---> BEST" << endl;
	cout << "(2) ---> GOOD" << endl;
	cout << "(3) ---> NOVICE" << endl;
	char ch;
	while (!gotLevel) {
		ch = _getch();
		if (ch == '1' || ch == '2' || ch == '3') {
			gotLevel = true;
		}
	}
	this->clearScreen();
	return ch - '0' - 1;
}

void Menu::printMenu(bool isGamePaused) {
	this->clearScreen();
	cout << " T E T R I S " << endl;
	cout << " " << endl;
	cout << "(1) ---> Start a new game - Human vs Human" << endl;
	cout << "(2) ---> Start a new game - Human vs Computer" << endl;
	cout << "(3) ---> Start a new game - Computer vs Computer" << endl;
	if (isGamePaused) {
		cout << "(4) ---> Continue a paused game" << endl;
	}
	cout << "(8) ---> Present instructions and keys" << endl;
	cout << "(9) ---> Exit" << endl;
}

void Menu::printInstructionsAndKeys(bool isGamePaused) {
	this->clearScreen();
	gotoxy(0, 1);
	cout << "                         Left Player         Right Player" << endl;
	cout << "LEFT                    |   a or A    |    	j or J" << endl;
	cout << "RIGHT                   |   d or D    |     l( small L ) or L" << endl;
	cout << "ROTATE clockwise        |   s or S    |        k or K  " << endl;
	cout << "ROTATE counterclockwise |   w or W    |   i or I(uppercase i) " << endl;
	cout << "DROP                    |   x or X    |        m or M" << endl;
	cout << "                                                        " << endl;
	cout << "Press any key to return to menu" << endl;

	char a;
	a = _getch();
}

void Menu::clearScreen() {
	system("CLS");
}

void Menu::printGameOver() {
	this->clearScreen();
	std::cout << "\n"
		" #####     #    #     # #######    ####### #     # ####### ######\n"
		"#     #   # #   ##   ## #          #     # #     # #       #     #\n"
		"#        #   #  # # # # #          #     # #     # #       #     #\n"
		"#  #### #     # #  #  # #####      #     # #     # #####   ######\n"
		"#     # ####### #     # #          #     #  #   #  #       #   #\n"
		"#     # #     # #     # #          #     #   # #   #       #    #\n"
		" #####  #     # #     # #######    #######    #    ####### #     #\n";

}


void Menu::printWinner(int winner) {

	gotoxy(PRINT_WINNER_X_LOCATION, PRINT_WINNER_Y_LOCATION);
	cout << "WINNER IS: \n\n" << endl;
	gotoxy(10, 7);
	if (winner == Game::RIGHT)
		cout << "RIGHT PLAYER" << endl;
	else if (winner == Game::LEFT)
		cout << "LEFT PLAYER" << endl;
	else
		cout << "IT'S A TIE !" << endl;

	cout << "\n\n\nPress any key and enter to return to menu\n" << endl;
	char a;
	a = _getch();

}

void Menu::gameOver(int winner) {
	this->printGameOver();
	Sleep(GAME_OVER_SLEEP_TIME);
	this->clearScreen();
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); // flushing input buffer
	this->printWinner(winner);
}
