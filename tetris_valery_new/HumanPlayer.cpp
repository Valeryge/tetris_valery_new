#include "HumanPlayer.h"


void HumanPlayer::playMove(int ch) {
	if (ch == leftKey || ch == leftKey + 32)
	{
		board.updateBoard(Point::LEFT);
	}
	else if (ch == rightKey || ch == rightKey + 32)
	{
		board.updateBoard(Point::RIGHT);
	}
	else if (ch == rotateColckWiseKey || ch == rotateColckWiseKey + 32)
	{
		board.updateBoard(Point::CLOCK_ROTATE);
	}
	else if (ch == rotateCounterClockWiseKey || ch == rotateCounterClockWiseKey + 32)
	{
		board.updateBoard(Point::COUNTER_CLOCK_ROTATE);
	}
	else if (ch == dropKey || ch == dropKey + 32)
	{
		board.updateBoard(Point::DROP);
	}

	else if (ch == 27) {
		return;
	}
	board.updateBoard(Point::NONE);
	int deletedLines = board.deleteLines();
	if (deletedLines > 0)
		score += deletedLines;
	return;
}