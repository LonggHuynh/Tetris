#include "Board.h"

void Board::draw() {
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

bool Board::isLost() {
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

bool Board::isOutOfBounds() {
	return getLeftBorderDeviation() < 0 || getRightBorderDeviation() > 0 || isOutOfMaxY();
}

int Board::getLeftBorderDeviation() {
	int minX = block->getBlockMinX();

	return minX - boardOffset.getX();
}

int Board::getRightBorderDeviation() {
	int maxX = block->getBlockMaxX();

	return maxX - (boardOffset.getX() + WIDTH - 1);
}

bool Board::isOutOfMaxY() {
	return block->getBlockMaxY() >= boardOffset.getY() + HEIGHT;
}

void Board::layBlockInField() {
	for (int i = 0; i < block->numberOfPoints; i++) {
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
	if (block)
		delete block;
	if (steps % 5 == 0) {
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
		if (block->numberOfPoints == 1) {
			explode(block->getPoint(0));
		}
		else {
			checkForCompletedRows(bottom, top);
		}
		

		shouldDropBlock = false;
		steps++;
		generateNewBlock();
	}
	else if (shouldDropBlock) {
		Sleep(DROP_SPEED);
		this->step();
	}
}

void Board::explode(Point point) {
	int x = point.getX() - 4;
	int y = point.getY() - 4;
	for (int i = 0; i < 9; i++)
	{
		int new_y = y + i;
		if (new_y >= (boardOffset.getY() + HEIGHT)) 
		{
			continue;
		}
		//else
		for (int j = 0; j < 9; j++)
		{
			int new_x = x + j;
			if (new_x < boardOffset.getX() || new_x > boardOffset.getX() + WIDTH - 1)
			{
				continue;
			}
			//else if field is not empty
			int offset_x = new_x - boardOffset.getX();
			int offset_y = new_y - boardOffset.getY();
			if (field[offset_y][offset_x]) {
				field[offset_y][offset_x] = 0;

				Point temp = Point(new_x, new_y);
				temp.draw(' ');
			}	
		}
	}
}