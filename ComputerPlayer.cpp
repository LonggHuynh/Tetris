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

Point ComputerPlayer::getLowestFieldPointFromLevel(int minHeightAllowed, int minX) {
	int maxEmptySpace = 0; 
	int columnNumber = 0;
	for (int x = minX; x < WIDTH; x++) {
		int columnEmptySpace;
		
		for (columnEmptySpace = 0;
			field[columnEmptySpace][x] == 0 && columnEmptySpace <= minHeightAllowed; 
			columnEmptySpace++) {
		}

		columnEmptySpace--;

		if (columnEmptySpace > maxEmptySpace) {
			maxEmptySpace = columnEmptySpace;
			columnNumber = x;
		}
	}

	return Point(columnNumber, maxEmptySpace);
}

int ComputerPlayer::getWidthAvailableAroundPoint(Point p, int &leftSpaceStart, int minX, int maxX) {
	vector<int> row = field[p.getY()];
	int width = 0;

	for (int left = p.getX(); left >= minX; left--) {
		if (row[left] == 0) {
			int ocupiedSpaceAbove = p.getY();
			for (; field[ocupiedSpaceAbove][left] == 0 && ocupiedSpaceAbove > 0; ocupiedSpaceAbove--) {
			}
			if (ocupiedSpaceAbove <= 0) {
				leftSpaceStart = left;
				width++;
			}
			else {
				break;
			}
		}
		else
			break;
	}

	for (int right = p.getX() + 1; right <= maxX; right++) {
		if (row[right] == 0) {
			int ocupiedSpaceAbove = p.getY();
			
			for (; field[ocupiedSpaceAbove][right] == 0 && ocupiedSpaceAbove > 0; ocupiedSpaceAbove--) {
			}

			if (ocupiedSpaceAbove <= 0) {
				width++;
			}
			else {
				break;
			}
		}
		else
			break;
	}

	return width;
}

bool ComputerPlayer::tryMatchSideAndRotate(int width, int shapeBottomWidth, int shapeTopWidth,
	int shapeLeftHeight, int shapeRightHeight) {
	bool foundMatch = false;
	if (width == shapeBottomWidth) {
		foundMatch = true;
	}
	else if (width == shapeTopWidth) {
		rotateClockwise();
		rotateClockwise();
		foundMatch = true;
	}
	else if (width == shapeLeftHeight) {
		rotateCounterClockwise();
		foundMatch = true;
	}
	else if (width == shapeRightHeight) {
		foundMatch = true;
		rotateClockwise();
	}

	return foundMatch;
}

void ComputerPlayer::calcBlockDestination(int minHeight = HEIGHT + 1, int minX = 0, int maxX = WIDTH -1) {
	Point lowestPoint = getLowestFieldPointFromLevel(minHeight, minX);
	int leftSpaceStart = lowestPoint.getX();
	int width = getWidthAvailableAroundPoint(lowestPoint, leftSpaceStart, minX, maxX);
	
	int shapeBottomWidth = block->calcWidthAtHeight(block->getBlockMaxY());
	int shapeTopWidth = block->calcWidthAtHeight(block->getBlockMinY());
	int shapeLeftHeight = block->calcHeightAtWidth(block->getBlockMinX());
	int shapeRightHeight = block->calcHeightAtWidth(block->getBlockMaxX());

	bool foundMatch = tryMatchSideAndRotate(width, shapeBottomWidth, shapeTopWidth,
		shapeLeftHeight, shapeRightHeight);

	if (!foundMatch) {
		int maxLength = max(
			max(shapeBottomWidth, shapeTopWidth),
			max(shapeLeftHeight, shapeRightHeight)
		);

		if (width >= maxLength) {
			width = maxLength;
		}
		else {
			int minLength = min(
				min(shapeBottomWidth, shapeTopWidth),
				min(shapeLeftHeight, shapeRightHeight)
			);

			if (width >= minLength) {
				width = minLength;
			}
			else {
				return calcBlockDestination(lowestPoint.getY(), lowestPoint.getX() + 1);
			}
		}

		tryMatchSideAndRotate(width, shapeBottomWidth, shapeTopWidth,
			shapeLeftHeight, shapeRightHeight);
	}

	if (leftSpaceStart == 0) {
		int bottomMinX = block->getBlockMinXAtBottom();
		int blockMinX = block->getBlockMinX();
		
		if (blockMinX < bottomMinX) {
			int shapeBottomWidth = block->calcWidthAtHeight(block->getBlockMaxY());
			int shapeLefttHeight = block->calcHeightAtWidth(block->getBlockMaxX());

			if (shapeBottomWidth == shapeLeftHeight)
				rotateCounterClockwise();
			else 
				return calcBlockDestination(lowestPoint.getY() - 1, 1);
		}
	}

	if (leftSpaceStart == WIDTH-1 || leftSpaceStart == WIDTH-2) {
		int bottomMaxX = block->getBlockMaxXAtBottom();
		int blockMaxX = block->getBlockMaxX();

		if (blockMaxX > bottomMaxX) {
			int shapeBottomWidth = block->calcWidthAtHeight(block->getBlockMaxY());
			int shapeRightHeight = block->calcHeightAtWidth(block->getBlockMaxX());

			if (shapeBottomWidth == shapeRightHeight)
				rotateClockwise();
			else 
				return calcBlockDestination(lowestPoint.getY()-1);
		}
	}

	blockDestination = new Point(boardOffset.getX() + leftSpaceStart, boardOffset.getY() + lowestPoint.getY());
}

void ComputerPlayer::makeRandomMistakeByChance(int& delta) {
	int shouldMakeMistake=0;
	if(level == 1)
		shouldMakeMistake = getRandom(1, 10);
	else if (level == 2)
		shouldMakeMistake = getRandom(1, 40);

	if (shouldMakeMistake == 1) {
		int mistakeType = getRandom(1, 5);

		switch (mistakeType) {
		case 1:
			delta = -delta;
			break;
		case 2:
			delta = 0;
			break;
		case 3:
			rotateClockwise();
			break;
		case 4:
			rotateClockwise();
			rotateClockwise();
			break;
		case 5:
			rotateCounterClockwise();
			break;
		}
	}
}

void ComputerPlayer::moveToDestination() {
	int bottomMinX = block->getBlockMinXAtBottom();
	int delta = bottomMinX - blockDestination->getX();

	makeRandomMistakeByChance(delta);

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
		if(block->getBlockMaxY() >= boardOffset.getY())
			calcBlockDestination();
	}	 
	else {
		moveToDestination();
	}

	Board::step();
}

void ComputerPlayer::actOnNextKey(char key) {}