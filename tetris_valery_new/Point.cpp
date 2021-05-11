
#include "Point.h"

void Point::move(Direction dir)
{
	if (dir == NONE) {
		y += diry;
	}
	else {
		int dirX = dir == RIGHT ? 1 : -1;
		x += dirX;
	}
}

void Point::draw()
{
	gotoxy(x, y);
	cout << figure << endl;
}


void Point::erase()
{
	gotoxy(x, y);
	cout << ' ' << endl;
}

int Point::getX() {
	return x;
}


int Point::getY() {
	return y;
}