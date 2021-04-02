#include "Board.h"

void Board::draw() {
	block->draw();
}

void Board::rotateCounterClockwise() {	
	block->clearDraw();
	block->rotateQuarterly(-1);	
	
	if (isOutOfBounds())
		block->rotateQuarterly(1);

	block->draw();
}

void Board::rotateClockwise() {	
	block->clearDraw();
	block->rotateQuarterly(1);
	
	if (isOutOfBounds())
		block->rotateQuarterly(-1);

	block->draw();
}

void Board::moveRight() {	
	if (isOutOfMaxX())
		return;
	block->clearDraw();
	block->move(1, 0);
	block->draw();
}

void Board::moveLeft() {
	if (isOutOfMinX())
		return;

	block->clearDraw();
	block->move(-1, 0);
	block->draw();
}

bool Board::isOutOfBounds() {
	return isOutOfMinX() || isOutOfMaxX();
}

bool Board::isOutOfMinX() {
	int minX = block->getBlockMinX();

	return minX <= boardOffset.getX();		
}

bool Board::isOutOfMaxX() {
	int maxX = block->getBlockMaxX();

	return maxX >= boardOffset.getX() + WIDTH - 1;
		
}

void Board:: layBlockInField() {
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
	delete block;
	block = new Block(Point(boardOffset.getX() + WIDTH / 2, -4));
}

void Board::step(bool drop) {
	block->clearDraw();
	block->move(0, 1);
	block->draw();
	bool isColiding = checkBlockFieldColision();

	if (isColiding) {
		layBlockInField();
		generateNewBlock();
	}
	else if (drop) {
		this->step(drop);
	}
}