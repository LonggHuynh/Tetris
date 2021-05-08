#ifndef _BOMB_H_
#define _BOMB_H_

#include "io_utils.h"
#include "Block.h"
#include <vector>
#include <cmath>

//using std::vector;

class Bomb : public Block {
	void pickBlockType(Point offset);
public:
	Bomb() : Block(Point()) {
		numberOfPoints = 1;
	}
	Bomb(Point offset) {
		numberOfPoints = 1;
		pickBlockType(offset);
		//pickPrimaryBlockRotation();
		setMaxYtoOffset(offset.getY());
		draw();
	}
	void draw();
};

#endif