#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "Gotoxy.h"

class Point
{
	char figure;
	int diry;
	int x, y;   // Every points holds its location in accordance to the whole screen

public:
	enum Direction { NONE, LEFT, RIGHT, CLOCK_ROTATE, COUNTER_CLOCK_ROTATE, DROP };

	Point()						// Constructor
	{
		x = y = 0;						// X , y coordination (0, 0)
		diry = 1;
		figure = 219;
	}
	void init(int x1, int y1, char figure1 = 219)		//אתחול נקודה 
	{
		x = x1;
		y = y1;
		figure = figure1;
		diry = 1;
	}
	void move(Direction dir);
	void draw();
	void erase();
	int getX();
	int getY();
};

#endif
