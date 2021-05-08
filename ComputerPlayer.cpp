#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(int offsetX, int offsetY, int level)
	: Board(offsetX, offsetY), level(level) {
}

void ComputerPlayer::generateNewBlock() {
	Board::generateNewBlock();
	
	if (blockDestination) {
		delete blockDestination;
		blockDestination = nullptr;
	}
}

Point ComputerPlayer::getLowestFieldPoint() {
	int maxEmptySpace = 0; 
	int columnNumber = 0;
	for (int x = 0 ; x < WIDTH; x++) {
		int columnEmptySpace;
		
		for (columnEmptySpace = 0; field[columnEmptySpace][x] == 0; columnEmptySpace++) {}

		columnEmptySpace--;

		if (columnEmptySpace > maxEmptySpace) {
			maxEmptySpace = columnEmptySpace;
			columnNumber = x;
		}
	}

	return Point(columnNumber, maxEmptySpace);
}

int ComputerPlayer::getWidthAvailableAroundPoint(Point p, int &leftSpaceStart) {
	vector<int> row = field[p.getY()];
	int width = 0;

	for (int left = p.getX(); left >= 0; left--) {
		if (row[left] == 0) {
			leftSpaceStart = left;
			width++;
		}
		else
			break;
	}

	for (int right = p.getX() + 1; right < WIDTH; right++) {
		if (row[right] == 0)
			width++;
		else
			break;
	}

	return width;
}

void ComputerPlayer::calcBlockDestination() {
	Point p = getLowestFieldPoint(); int leftSpaceStart = p.getX();
	int width = getWidthAvailableAroundPoint(p, leftSpaceStart);
	int shapeWidth = block->getBlockMaxX() - block->getBlockMinX();

	if (shapeWidth > width) {
		int shapeHeight = block->getBlockMaxY() - block->getBlockMinY();

		if (shapeHeight < shapeWidth) {
			rotateClockwise();			
		}
	}

	blockDestination = new Point(boardOffset.getX() + leftSpaceStart, boardOffset.getY() + p.getY());
}

void ComputerPlayer::moveToDestination() {
	int delta = block->getBlockMinX() - blockDestination->getX();

	if (delta == 0)
		shouldDropBlock = true;
	else {
		if (delta > 0) {
			moveLeft();
		}
		else {
			moveRight();
		}
	}
}

void ComputerPlayer::step() {
	if (!blockDestination) {
		if(block->getBlockMinY() >= boardOffset.getY())
			calcBlockDestination();
	}	 
	else {
		moveToDestination();
	}

	Board::step();
}

void ComputerPlayer::actOnNextKey(char key) {}