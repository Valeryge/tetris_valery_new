#include "Board.h"

// Board Functions 

void Board::printBoard() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (boardMatrix[i][j] == POS_FILLED) {
				gotoxy(j + min_x, i);
				cout << char(POS_FILLED_CHAR);
			}
			if (boardMatrix[i][j] == BORDER) {
				gotoxy(j + min_x, i);
				cout << char(BORDER_CHAR);
			}
			if (boardMatrix[i][j] == POS_FREE) {
				gotoxy(j + min_x, i);
				cout << " ";
			}
		}
	}
}

void Board::init(int x) {
	bomb.init(min_x);
	roundCounter = 1;
	isGameOver = false;
	min_x = x;
	bombFlag = 0;
	bomb.init(min_x);
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (j == 0 || j == BOARD_WIDTH - 1 || i == BOARD_HEIGHT - 1)
				boardMatrix[i][j] = BORDER;
			else
				boardMatrix[i][j] = POS_FREE;
		}
	}
	currPiece.init(min_x);
}

int Board::deleteLines() {
	int deletedLines = 0;
	for (int i = BOARD_HEIGHT - 2; i >= 0; i--)
	{
		int j = 0;
		while (j < BOARD_WIDTH && boardMatrix[i][j] != POS_FREE)
		{
			j++;
		}
		if (j == BOARD_WIDTH) // if line is full
		{
			this->deleteLine(i, 0, BOARD_WIDTH);
			this->printBoard();
			deletedLines++;
		}
	}
	return deletedLines;
}

void Board::deleteLine(const int line_index, const int minX, const int maxX) //get line index to delete and move all upper lines one line down. 
{
	for (int i = line_index; i > 0; i--)
	{
		for (int j = minX; j < maxX; j++)
		{
			boardMatrix[i][j] = boardMatrix[i - 1][j];
		}
	}

}

bool Board::checkGameOver() {
	for (int i = PIECE_START_POS; i < BOARD_WIDTH - 1; i++) {
		if (boardMatrix[2][i] == POS_FILLED)
			return true;
	}
	return false;
}

void Board::randBombOrPiece() {
	int random = rand() % 100;
	if (random <= BOMB_PROB) {
		bomb.init(min_x);
		bombFlag = 1;
		return;
	}
	currPiece.init(min_x);
	isDroppingPiece = false;
	bombFlag = 0;
}

void Board::clearBoard() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (boardMatrix[i][j] == POS_FILLED) {
				boardMatrix[i][j] = POS_FREE;
			}
		}
	}
}

void Board::updateBoard(Point::Direction dir) {
	if (!bombFlag) {
		this->updateBoardWithPiece(dir);
	}
	else
	{
		updateBoardWithBomb(dir);
	}
}

int Board::findBestLocationForBomb() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (boardMatrix[i][j] == POS_FILLED) {
				return j;
			}
		}
	}
	return 1;
}

int* Board::findBestPositionAndLocation() {
	int bestPositionIndex = 0;
	int bestColIndex = 1;
	int maxLinesDeleted = 0;
	int positionsToCheck = currPiece.isPieceRepeatsItself() ? 2 : 4;

	for (int i = 0; i < positionsToCheck; i++) {
		for (int j = 1; j < BOARD_WIDTH; j++) {
			int temp = this->countNumOfLinesDeleted(currPiece.getShapeIndex(), i, j);
			if (temp > maxLinesDeleted) {
				maxLinesDeleted = temp;
				bestPositionIndex = i;
				bestColIndex = j;
			}
			else {
				if (temp == maxLinesDeleted) {
					int option = this->getHighestPointOfFakePiece(currPiece.getShapeIndex(), i, j);
					int best = this->getHighestPointOfFakePiece(currPiece.getShapeIndex(), bestPositionIndex, bestColIndex);
					if (option > best) {
						bestPositionIndex = i;
						bestColIndex = j;
					}
				}
			}
		}
	}
	int posAndCol[2] = { bestPositionIndex, bestColIndex };
	return posAndCol;
}

int Board::countNumOfLinesDeleted(int shapeIndex, int posIndex, int col) {
	if (!this->dropFakePieceToPlace(shapeIndex, posIndex, col)) {
		return -1;
	}
	int possibleDeletedLines = this->countFullLines();
	this->changeBoardToOrigin();
	return possibleDeletedLines;
}

int Board::countFullLines() {
	int fullLinesCounter = 0;
	for (int i = BOARD_HEIGHT - 2; i >= 0; i--) {
		if (isLineFull(i) != -1) {
			break;
		}
		fullLinesCounter++;
	}
	return fullLinesCounter;
}

int Board::getHighestPointOfFakePiece(int shapeIndex, int posIndex, int col) {
	if (!this->dropFakePieceToPlace(shapeIndex, posIndex, col)) {
		return -1;
	}
	Point currPoint;
	int minY = BOARD_HEIGHT; // we want the minimun y. the smaller the y - the higher the point is
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		if (fake.getPointsArr()[i].getY() < minY) {
			minY = fake.getPointsArr()[i].getY();
		}
	}
	this->changeBoardToOrigin();
	return minY;
}

bool Board::dropFakePieceToPlace(int shapeIndex, int posIndex, int col) { //returns false if the location wasnt valid
	fake.initWithParams(this->min_x + col, shapeIndex, posIndex);
	if (this->isPieceOutOfLimits(fake)) {
		return false;
	}
	while (this->canPiecePrecede(fake)) {
		fake.movePiece(Point::NONE);
	}
	Point currPoint;
	for (int i = 0; i < NUM_OF_POINTS; i++) {  // faking 'store piece'
		currPoint = fake.getPointsArr()[i];
		boardMatrix[currPoint.getY()][currPoint.getX() - min_x] = POS_FILLED;
	}
	return true;
}

bool Board::isPieceOutOfLimits(Piece piece) {
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		if (piece.getPointsArr()[i].getX() - min_x < 1 || piece.getPointsArr()[i].getX() - min_x > 12) {
			return true;
		}
	}
	return false;
}

void Board::changeBoardToOrigin() {
	Point currPoint;

	for (int i = 0; i < NUM_OF_POINTS; i++) {  // we dont want to change the board really
		currPoint = fake.getPointsArr()[i];
		boardMatrix[currPoint.getY()][currPoint.getX() - min_x] = POS_FREE;
	}
}

int Board::isLineFull(int index) { // returns index of column where the hole is - if line is full return -1
	for (int i = 0; i < BOARD_WIDTH; i++) {
		if (boardMatrix[index][i] == POS_FREE) {
			return i;
		}
	}
	return -1;
}

void Board::updateBoardWithPiece(Point::Direction dir) {
	if (isDroppingPiece) {
		this->dropPieceIfPossible();
		return;
	}

	if (dir != Point::NONE) {
		if (dir == Point::LEFT || dir == Point::RIGHT) {
			if (this->canPieceMove(dir))
				currPiece.movePiece(dir);
		}
		else if (dir == Point::DROP)
			isDroppingPiece = true;
		else {
			if (this->canPieceRotate(dir)) {
				if (dir == Point::CLOCK_ROTATE)
					currPiece.rotateClockwise();
				else
					currPiece.rotateCounterClockwise();
			}
		}
	}
	else {
		if (this->canPiecePrecede(currPiece))
			currPiece.movePiece(dir);
		else
			this->storePiece();
	}
	if (!checkGameOver())
		currPiece.drawPiece();
	else
		isGameOver = true;
}



// Piece Functions

bool Board::canPieceRotate(Point::Direction dir) {
	char tempMatrix[SHAPE_SIZE][SHAPE_SIZE];
	int posIndex = currPiece.getPosIndex();
	int rotatedShapePositionIndex = (dir == Point::CLOCK_ROTATE) ? posIndex + 1 : posIndex - 1;
	int cornerX = currPiece.getCornerX();
	int cornerY = currPiece.getCornerY();

	for (int i = 0; i < SHAPE_SIZE; i++) {
		for (int j = 0; j < SHAPE_SIZE; j++) {
			tempMatrix[i][j] = shapeOptions[currPiece.getShapeIndex()][rotatedShapePositionIndex][i][j];
			if (tempMatrix[i][j]) { // possible place of a point
				if (boardMatrix[i + cornerY][j + cornerX] != POS_FREE) {
					return false;
				}
			}
		}
	}
	return true;

}

bool Board::canPiecePrecede(Piece piece) {
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		int newY = (piece.getPointsArr())[i].getY() + 1;
		if (boardMatrix[newY][(piece.getPointsArr())[i].getX() - min_x] != POS_FREE) {
			return false;
		}
	}
	return true;
}

void Board::dropPieceIfPossible() {
	for (int i = 0; i < 5; i++) {
		if (this->canPiecePrecede(currPiece)) {
			currPiece.movePiece(Point::NONE);
			currPiece.drawPiece();
		}
		else {
			this->storePiece();
			return;
		}
	}
}

bool Board::canPieceMove(Point::Direction dir) {
	int dirX;
	dirX = dir == Point::LEFT ? -1 : 1;
	Point currPoint;
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		currPoint = currPiece.getPointsArr()[i];
		int newX = currPoint.getX() + dirX;
		if (boardMatrix[currPoint.getY()][newX - min_x] != POS_FREE) {
			return false;
		}
	}
	return true;
}

void Board::storePiece() {
	Point currPoint;
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		currPoint = currPiece.getPointsArr()[i];
		boardMatrix[currPoint.getY()][currPoint.getX() - min_x] = POS_FILLED;
	}
	this->randBombOrPiece();
	roundCounter++;

}



// Bomb Functions

bool Board::canBombMove(Point::Direction dir) {
	if (dir == Point::LEFT || dir == Point::RIGHT) {
		int dirX;
		dirX = dir == Point::LEFT ? -1 : 1;
		int newX = bomb.getX() + dirX;
		if (boardMatrix[bomb.getY()][newX - min_x] != POS_FREE)
			return false;
	}
	else if (dir == Point::NONE) {
		int newY = bomb.getY() + 1;
		if (boardMatrix[newY][bomb.getX() - min_x] != POS_FREE)
			return false;
	}
	return true;
}

void Board::bombExplosion() {
	int x = bomb.getX() - min_x;
	int y = bomb.getY();

	int minX = (x - 4) < 1 ? 1 : (x - 4);
	int maxX = (x + 4) > BOARD_WIDTH - 2 ? BOARD_WIDTH - 2 : (x + 4);
	int minY = (y - 4) < 1 ? 1 : (y - 4);
	int maxY = (y + 4) > BOARD_HEIGHT - 2 ? BOARD_HEIGHT - 2 : (y + 4);
	for (int i = minY; i < maxY + 1; i++) {
		for (int j = minX; j < maxX + 1; j++) {
			if (boardMatrix[i][j] == POS_FILLED)
				boardMatrix[i][j] = POS_FREE;
		}
		if (this->isEmptyLine(i))
			this->deleteLine(i, 0, BOARD_WIDTH); //if line is empty remove all cell one row down
		else
			this->deleteLine(i, minX, maxX + 1); //move relevant cells one row down
	}
	bomb.erase();
	this->printBoard();
	this->randBombOrPiece();
	roundCounter++;
}

void Board::dropBombIfPossible() {
	for (int i = 0; i < 5; i++) {
		if (this->canBombMove(Point::NONE)) {
			bomb.moveBomb(Point::NONE);
		}
		else {
			this->bombExplosion();
			isDroppingBomb = false;
			return;
		}
	}
}

void Board::updateBoardWithBomb(Point::Direction dir) {
	if (isDroppingBomb) {
		this->dropBombIfPossible();
		return;
	}
	if (dir != Point::DROP) {
		if (this->canBombMove(dir))
			bomb.moveBomb(dir);
		else
			this->bombExplosion();
	}
	else {
		isDroppingBomb = true;
	}

}


