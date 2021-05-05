#include "Point.h"

void Point::draw(char ch) {
	if (y >= 0) {
		gotoxy(x, y);
		cout << ch << endl;
	}
}

int Point::getX() {
	return x;
}

int Point::getY() {
	return y;
}

void Point::move(int _x, int _y) {	
	x = x + _x;
	y = y + _y;	
}

void Point::setPosition(int _x, int _y) {
	x = _x;
	y = _y;
}