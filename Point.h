#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "io_utils.h"

using namespace std;

class Point {
	int x = 1, y = 1;
public:
	Point() {}
	Point(int _x, int _y) : x(_x), y(_y) {}	
	void draw(char ch) const;
	int getX() const;
	int getY() const;
	void setPosition(int _x, int _y);
	void move(int _x, int _y);	
};

#endif