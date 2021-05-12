#ifndef _BOMB_H_
#define _BOMB_H_

#include "io_utils.h"
#include "Block.h"
#include <vector>

class Bomb : public Block {
	void pickBlockType(Point offset) override;
public:
	Bomb() : Block(Point()) {
		numberOfPoints = 1;
	}
	Bomb(Point offset) {
		numberOfPoints = 1;
		allowRotation = false;
		pickBlockType(offset);
		setMaxYtoOffset(offset.getY());
		draw();
	}
	void draw() const override;
	void explode(vector<vector<int>>* fields, int offsetX, int offsetY, int height, int width);
};

#endif