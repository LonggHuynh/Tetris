#include "Bomb.h"

void Bomb::pickBlockType(Point offset) {
	points[0].setPosition(offset.getX(),offset.getY());
	center.setPosition(offset.getX(), offset.getY());
}

void Bomb::draw() const {
	drawShape('@');
}

int Bomb::getDiameter() const {
	return 2 * BOMB_RADIUS;
}

void Bomb::explode(vector<vector<int>>& field, Point offset, Point &startIndex, int height, int width)
{
	int offsetY = offset.getY();
	int offsetX = offset.getX();
	int explosionStartX = max(this->center.getX() - BOMB_RADIUS, offsetX);
	int explosionStartY = max(this->center.getY() - BOMB_RADIUS, offsetY);
	startIndex.setPosition(explosionStartX - offsetX, explosionStartY - offsetY);

	for (int i = 0; i <= 2 * BOMB_RADIUS; i++)
	{
		int bombedY = explosionStartY + i;
		if (bombedY >= (offsetY + height))
		{
			continue;
		}
		//else
		for (int j = 0; j <= 2 * BOMB_RADIUS; j++)
		{
			int bombedX = explosionStartX + j;
			if (bombedX < offsetX || bombedX > offsetX + width)
			{
				continue;
			}
			//else if field is not empty
			int clear_x = bombedX - offsetX;
			int clear_y = bombedY - offsetY;
			if (field[clear_y][clear_x]) {
				field[clear_y][clear_x] = 0;

				Point temp = Point(bombedX, bombedY);
				temp.draw(' ');
			}
		}
	}
}
