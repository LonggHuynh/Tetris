#include "Block.h"

void Block::drawShape(char ch) {
	for (int i = 0; i < 4; i++) {
		points[i].draw(ch);				
	}
}

void Block::draw() {
	drawShape('#');
}

void Block::clearDraw() {
	drawShape(' ');
}

void Block::move(int x, int y) {
	for (int i = 0; i < 4; i++) {
		points[i].move(x, y);
	}
}

void Block::rotateQuarterly(int clockwise) {
	for (int i = 0; i < 4; i++) {
		Point& p = points[i];
		int x = p.getX() - center.getX();
		int y = p.getY() - center.getY();
		int xNew = clockwise * (-y) + center.getX();
		int yNew = clockwise * x + center.getY();
		p.setPosition(xNew, yNew);
	}
}

const Point Block::getPoint(int i) {
	if(i >= 0 && i <= 3)
		return points[i];
}

int Block::getBlockMaxX() {
	int maxX = points[0].getX();
	
	for (int i = 1; i < 4; i++) {
		int x = points[i].getX();
		
		if (maxX < x) {
			maxX = x;
		}
	}

	return maxX;
}

int Block::getBlockMinX() {
	int minX = points[0].getX();

	for (int i = 1; i < 4; i++) {
		int x = points[i].getX();

		if (minX > x) {
			minX = x;
		}
	}

	return minX;
}