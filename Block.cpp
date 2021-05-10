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

	allowRotation = blockType != CUBE_SHAPE_INDEX;

	for (size_t i = 0, p = 0; i < numberOfPoints; i++)
	{
		for (size_t j = 0; j < numberOfPoints; j++)
		{
			if (block_list[blockType][i][j] == 1) {
				points[p++].setPosition(
					offset.getX() + i,
					offset.getY() + j
				);
			}
		}
	}

	center.setPosition(offset.getX() + 2, offset.getY() + 2);
}

void Block::drawShape(char ch) const {
	for (int i = 0; i < numberOfPoints; i++) {
		points[i].draw(ch);				
	}
}

void Block::draw() const {
	drawShape('#');
}

void Block::clearDraw() {
	drawShape(' ');
}

void Block::move(int x, int y) {
	for (int i = 0; i < numberOfPoints; i++) {
		points[i].move(x, y);
	}

	center.move(x, y);
}

void Block::rotateQuarterly(int clockwise) {
	if (!allowRotation) {
		return;
	}
	 
	for (int i = 0; i < numberOfPoints; i++) {
		Point& p = points[i];
		int x = p.getX() - center.getX();
		int y = p.getY() - center.getY();
		int xNew = clockwise * (-y) + center.getX();
		int yNew = clockwise * x + center.getY();
		p.setPosition(xNew, yNew);
	}
}

int Block::getNumberOfPoints() const{
	return numberOfPoints;
}

const Point Block::getPoint(int i) const {
	if(i >= 0 && i <= 3)
		return points[i];
}

int Block::getBlockMaxX() const {
	int maxX = points[0].getX();
	
	for (int i = 1; i < numberOfPoints; i++) {
		int x = points[i].getX();
		
		if (maxX < x) {
			maxX = x;
		}
	}

	return maxX;
}

int Block::getBlockMinX() const {
	int minX = points[0].getX();

	for (int i = 1; i < numberOfPoints; i++) {
		int x = points[i].getX();

		if (minX > x) {
			minX = x;
		}
	}

	return minX;
}

int Block::getBlockMaxY() const {
	int maxY = points[0].getY();

	for (int i = 1; i < numberOfPoints; i++) {
		int y = points[i].getY();

		if (maxY < y) {
			maxY = y;
		}
	}

	return maxY;
}

int Block::getBlockMinY() const {
	int minY = points[0].getY();

	for (int i = 1; i < numberOfPoints; i++) {
		int y = points[i].getY();

		if (minY > y) {
			minY = y;
		}
	}

	return minY;
}

int Block::calcWidthAtHeight(int height) const {
	int width = 0;
	for (int i = 0; i < 4; i++) {
		int y = points[i].getY();

		if (height == y) {
			width++;
		}
	}

	return width;
}

int Block::calcHeightAtWidth(int width) const {
	int height = 0;
	for (int i = 0; i < 4; i++) {
		int x = points[i].getX();

		if (width == x) {
			height++;
		}
	}

	return height;
}

int Block::getBlockMinXAtBottom() const {
	int minX = points[0].getX();
	int maxY = points[0].getY();

	for (int i = 1; i < 4; i++) {
		int x = points[i].getX();
		int y = points[i].getY();

		if (maxY < y) {
			maxY = y;
			minX = x;
		}
		else if (maxY == y && minX > x) {
			minX = x;
		}
	}

	return minX;
}

int Block::getBlockMaxXAtBottom() const {
	int maxX = points[0].getX();
	int maxY = points[0].getY();

	for (int i = 1; i < 4; i++) {
		int x = points[i].getX();
		int y = points[i].getY();

		if (maxY < y) {
			maxY = y;
			maxX = x;
		}
		else if (maxY == y && maxX < x) {
			maxX = x;
		}		
	}

	return maxX;
}