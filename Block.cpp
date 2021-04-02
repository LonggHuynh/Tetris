#include "Block.h"

void Block::setMaxYtoOffset(int y) {
	auto maxY = max(getBlockMaxY(),0);
	move(0, -maxY -1);
}

void Block::pickPrimaryBlockRotation() {
	int rotation = getRandom(-3, 3);

	if (!rotation)
		return;

	int rotationCount = abs(rotation);
	int direction = rotation / rotationCount;

	for (int i = 0; i < rotationCount; i++)
		rotateQuarterly(direction);
}

void Block::pickBlockType(Point offset) {
	int blockType = getRandom(0, 6);

	for (size_t i = 0, p = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			/*shape[i][j] = 0;
			shape[i][j] = block_list[blockType][i][j];*/
			if (block_list[blockType][i][j] == 1) {
				points[p++].setPosition(
					offset.getX() + i,
					offset.getY() + j
				);
			}
		}
	}
}

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

int Block::getBlockMaxY() {
	int maxY = points[0].getY();

	for (int i = 1; i < 4; i++) {
		int y = points[i].getY();

		if (maxY < y) {
			maxY = y;
		}
	}

	return maxY;
}

int Block::getBlockMinY() {
	int minY = points[0].getY();

	for (int i = 1; i < 4; i++) {
		int y = points[i].getY();

		if (minY > y) {
			minY = y;
		}
	}

	return minY;
}