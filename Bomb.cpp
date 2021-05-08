#include "Bomb.h"

void Bomb::pickBlockType(Point offset) {
	points[0].setPosition(offset.getX(),offset.getY());
	center.setPosition(offset.getX(), offset.getY());
}


void Bomb::draw() {
	drawShape('@');
}
