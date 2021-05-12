#include "Bomb.h"

void Bomb::pickBlockType(Point offset) {
	points[0].setPosition(offset.getX(),offset.getY());
	center.setPosition(offset.getX(), offset.getY());
}

void Bomb::draw() const {
	drawShape('@');
}

void Bomb::explode(vector<vector<int>>* field, int offsetX, int offsetY, int height, int width)
{
	int x = max(this->center.getX() - 4,0);
	int y = max(this->center.getY() - 4,0);
	for (int i = 0; i < 9; i++)
	{
		int new_y = y + i;
		if (new_y >= (offsetY + height))
		{
			continue;
		}
		//else
		for (int j = 0; j < 9; j++)
		{
			int new_x = x + j;
			if (new_x < offsetX || new_x > offsetX + width)
			{
				continue;
			}
			//else if field is not empty
			int offset_x = new_x - offsetX;
			int offset_y = new_y - offsetY;
			if ((*field)[offset_y][offset_x]) {
				(*field)[offset_y][offset_x] = 0;

				Point temp = Point(new_x, new_y);
				temp.draw(' ');
			}
		}
	}
}
