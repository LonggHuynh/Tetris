#include "Point.h"

void Point::draw(char ch) const {
	if (y >= 0) {
		gotoxy(x, y);
		cout << ch << endl;
	}
}

int Point::getX() const {
	return x;
}

int Point::getY() const {
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