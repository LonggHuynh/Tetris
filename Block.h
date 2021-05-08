#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "io_utils.h"
#include "Point.h"
#include <vector>
#include <cmath>

using std::vector;
using std::cout;
using std::endl;
using std::rand;

class Block {	
    const vector<vector<vector<int>>> block_list =
    {
        {
            { 0, 0, 1, 0 },
            { 0, 0, 1, 0 },
            { 0, 0, 1, 0 },
            { 0, 0, 1, 0 }
        },
        {
            { 0, 0, 0, 0 },
            { 0, 1, 1, 0 },
            { 0, 1, 0, 0 },
            { 0, 1, 0, 0 }
        },
        {
            { 0, 0, 0, 0 },
            { 0, 0, 1, 0 },
            { 0, 1, 1, 0 },
            { 0, 1, 0, 0 }
        },
        {
            { 0, 0, 0, 0 },
            { 0, 1, 0, 0 },
            { 0, 1, 1, 0 },
            { 0, 0, 1, 0 }
        },
        {
            { 0, 0, 0, 0 },
            { 0, 0, 1, 0 },
            { 0, 1, 1, 1 },
            { 0, 0, 0, 0 }
        },
        {
            { 0, 0, 0, 0 },
            { 0, 1, 1, 0 },
            { 0, 1, 1, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 0, 0, 0, 0 },
            { 0, 1, 1, 0 },
            { 0, 0, 1, 0 },
            { 0, 0, 1, 0 }
        }
    };

protected:
	Point points[4];
	virtual void pickPrimaryBlockRotation();
	virtual void setMaxYtoOffset(int y);
	virtual void pickBlockType(Point offset);
	Point center;
public:
	int numberOfPoints = 4;
	virtual void drawShape(char ch);	
    Block() : Block(Point()) {}
	Block(Point offset) {
        pickBlockType(offset);
        pickPrimaryBlockRotation();
        setMaxYtoOffset(offset.getY());
        draw();
	}
	virtual void draw();
    void clearDraw();
    void rotateQuarterly(int clockwise);
    void move(int _x, int _y);
    const Point getPoint(int i);
    int getBlockMaxX();
    int getBlockMinX();
    int getBlockMaxY();
    int getBlockMinY();
    int calcWidthAtHeight(int height);
    int calcHeightAtWidth(int width);
    int getBlockMinXAtBottom();
    int getBlockMaxXAtBottom();
};

#endif