#include "Board.h"

void Board::draw() const {
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			char ch = ' ';

			if (field[y][x]) {
				ch = '#';
			}

			Point(boardOffset.getX() + x, boardOffset.getY() + y).draw(ch);
		}
	}

	if (block)
		block->draw();
}

void Board::clearRow(int y) {
	for (int x = 5; x < WIDTH; x++) {
		Point(boardOffset.getX() + x, boardOffset.getY() + y).draw(' ');
		Point(boardOffset.getX() + WIDTH - 1 - x, boardOffset.getY() + y).draw(' ');
		Sleep(CLEAR_ROW_DELAY);
	}
}

bool Board::isLost() const {
	return hasLost;
}

bool Board::checkIfLost() {
	int minY = block->getBlockMinY();
	hasLost = minY - boardOffset.getY() < 0;
	return hasLost;
}

void Board::shrinkEmptyRow(int rowDeleted) {
	for (int y = rowDeleted; y > 0; y--) {
		field[y] = field[y - 1];
	}

	fill(field[0].begin(), field[0].end(), 0);
}

void Board::rotateBlock(int quarters) {
	block->clearDraw();
	block->rotateQuarterly(quarters);

	auto deltaX = getRightBorderDeviation();
	bool isColiding = false;

	if (deltaX > 0) {
		isColiding = tryMoveBlock(-deltaX, 0, false);
	}
	else {
		deltaX = getLeftBorderDeviation();

		if (deltaX < 0) {
			isColiding = tryMoveBlock(-deltaX, 0, false);
		}
		else {
			isColiding = checkBlockFieldColision();
		}
	}

	if (isColiding)
		block->rotateQuarterly(-quarters);

	block->draw();
}

bool Board::tryMoveBlock(int x, int y, bool shouldDraw) {
	if (shouldDraw)
		block->clearDraw();

	block->move(x, y);
	bool isOut = isOutOfBounds();
	// we should check the colision only if the block is in bounds
	bool isColiding = isOut ? isOutOfMaxY() : checkBlockFieldColision();

	if (isOut || isColiding)
		block->move(-x, -y);

	if (shouldDraw)
		block->draw();

	return isColiding;
}

void Board::rotateCounterClockwise() {
	rotateBlock(-1);
}

void Board::rotateClockwise() {
	rotateBlock(1);
}

void Board::moveRight() {
	tryMoveBlock(1, 0);
}

void Board::moveLeft() {
	tryMoveBlock(-1, 0);
}

bool Board::isOutOfBounds() const {
	return getLeftBorderDeviation() < 0 || getRightBorderDeviation() > 0 || isOutOfMaxY();
}

int Board::getLeftBorderDeviation() const {
	int minX = block->getBlockMinX();

	return minX - boardOffset.getX();
}

int Board::getRightBorderDeviation() const {
	int maxX = block->getBlockMaxX();

	return maxX - (boardOffset.getX() + WIDTH - 1);
}

bool Board::isOutOfMaxY() const {
	return block->getBlockMaxY() >= boardOffset.getY() + HEIGHT;
}

void Board::layBlockInField() {
	auto numPoints = block->getNumberOfPoints();

	for (int i = 0; i < numPoints; i++) {
		Point p = block->getPoint(i);
		int y = p.getY() - boardOffset.getY();
		int x = p.getX() - boardOffset.getX();
		field[y][x] = 1;
	}
}

bool Board::checkBlockFieldColision() {
	for (int i = 0; i < 4; i++) {
		Point p = block->getPoint(i);
		int y = p.getY() - boardOffset.getY();
		int x = p.getX() - boardOffset.getX();

		if (y < 0)
			continue;

		bool isEmpty = !field[y][x];

		if (!isEmpty) {
			return true;
		}
	}

	return false;
}

void Board::generateNewBlock() {
	if (block) {
		delete block;
		block = nullptr;
	}

	auto chance = getRandom(1, 20);
	bool shouldGenerateBomb = (chance == 10); //draw 1 specific number out of 20 is at 5% chance

	if (shouldGenerateBomb) {
		block = new Bomb(Point(boardOffset.getX() + WIDTH / 2 - 2, 0));
	}
	else {
		block = new Block(Point(boardOffset.getX() + WIDTH / 2 - 2, 0));
	}

}

void Board::checkForCompletedRows(int bottom, int top) {
	for (int y = bottom; y <= top; y++) {
		int occupiedCells = count(field[y].begin(), field[y].end(), 1);

		if (occupiedCells == WIDTH) {
			clearRow(y);
			shrinkEmptyRow(y);
			draw();
		}
	}
}

void Board::step() {
	if (hasLost) {
		shouldDropBlock = false;
		return;
	}

	bool isColiding = tryMoveBlock(0, 1);

	if (isColiding) {

		if (checkIfLost()) {
			return;
		}
		layBlockInField();
		int bottom = block->getBlockMinY() - boardOffset.getY();
		int top = block->getBlockMaxY() - boardOffset.getY();
		auto bomb = dynamic_cast<Bomb*>(block);

		if (bomb) {
			Point explotionStartIndex;
			int diameter = bomb->getDiameter();
			bomb->explode(field, boardOffset, explotionStartIndex, HEIGHT, WIDTH - 1);
			delete bomb;
			block = nullptr;
			reduceExplosion(explotionStartIndex, diameter);
		}
		else {
			checkForCompletedRows(bottom, top);
		}

		shouldDropBlock = false;
		generateNewBlock();
	}
	else if (shouldDropBlock) {
		Sleep(DROP_SPEED);
		this->step();
	}
}

void Board::reduceExplosion(Point startIndex, int diameter) {
	int maxX = min(startIndex.getX() + diameter, WIDTH - 1);

	for (int i = 0; i < HEIGHT - startIndex.getY(); i++) {
		for (int y = i + startIndex.getY() - 1; y >= 0; y--) {
			for (int x = startIndex.getX(); x <= maxX; x++) {
				if (y < HEIGHT && field[y+1][x] == 0) {					
					field[y+1][x] = field[y][x];
					field[y][x] = 0;
				}
			}
		}

		draw();
		Sleep(DROP_SPEED);
	}
}
