#include "Menu.h"
#include "Gotoxy.h"
#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace std;

void setCursor(bool visible);


void main() {
	setCursor(false);
	Menu menu;
	menu.runMenu();
}

void setCursor(bool visible) {
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = visible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}