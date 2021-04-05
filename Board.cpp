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
		Point(boardOffset.getX() + WIDTH -1 - x, boardOffset.getY() + y).draw(' ');
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

	if (isOutOfBounds() || checkBlockFieldColision())
		block->rotateQuarterly(-quarters);

	block->draw();
}

void Board::moveBlock(int x, int y) {	
	block->clearDraw();
	block->move(x, y);

	if (isOutOfMinX() || isOutOfMaxX() || checkBlockFieldColision())
		block->move(-x, -y);

	block->draw();
}

void Board::rotateCounterClockwise() {	
	rotateBlock(-1);
}

void Board::rotateClockwise() {	
	rotateBlock(1);
}

void Board::moveRight() {	
	moveBlock(1, 0);
}

void Board::moveLeft() {
	moveBlock(-1, 0);
}

bool Board::isOutOfBounds() {
	return isOutOfMinX() || isOutOfMaxX() || 
		block->getBlockMaxY() >= boardOffset.getY() + HEIGHT;
}

bool Board::isOutOfMinX() {
	int minX = block->getBlockMinX();

	return minX < boardOffset.getX();		
}

bool Board::isOutOfMaxX() {
	int maxX = block->getBlockMaxX();

	return maxX > boardOffset.getX() + WIDTH -1;		
}

void Board::layBlockInField() {
	for (int i = 0; i < 4; i++) {
		Point p = block->getPoint(i);
		int y = p.getY() - boardOffset.getY();
		int x = p.getX() - boardOffset.getX();
		field[y][x] = 1;
	}
}

bool Board::checkBlockFieldColision() {
	for (int i = 0; i < 4; i++) {
		Point p = block->getPoint(i);
		int y = p.getY() - boardOffset.getY() + 1;
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

	block = new Block(Point(boardOffset.getX() + WIDTH / 2, 0));
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

void Board::step(bool drop) {
	if (hasLost) {
		return;
	}

	block->clearDraw();
	block->move(0, 1);
	block->draw();
	bool isColiding = checkBlockFieldColision();

	if (isColiding) {
		if (checkIfLost()) {
			return;
		}
		layBlockInField();	
		int bottom = block->getBlockMinY() - boardOffset.getY();
		int top = block->getBlockMaxY() - boardOffset.getY();
		checkForCompletedRows(bottom, top);
		generateNewBlock();
	}
	else if (drop) {
		Sleep(DROP_SPEED);
		this->step(drop);
	}
}