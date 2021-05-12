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
    enum { CUBE_SHAPE_INDEX=0 };
    const vector<vector<vector<int>>> block_list =
    {
        {
            { 0, 0, 0, 0 },
            { 0, 1, 1, 0 },
            { 0, 1, 1, 0 },
            { 0, 0, 0, 0 }
        },
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
            { 0, 0, 1, 0 },
            { 0, 0, 1, 0 }
        }
    };

protected:
	Point points[4];
	virtual void pickBlockType(Point offset);
	void setMaxYtoOffset(int y);
	void pickPrimaryBlockRotation();
	Point center;
    bool allowRotation = true;
	int numberOfPoints = 4;
public:
    Block() : Block(Point()) {}
	Block(Point offset) {
        pickBlockType(offset);
        pickPrimaryBlockRotation();
        setMaxYtoOffset(offset.getY());
        draw();
	}
	virtual void drawShape(char ch) const;	
	virtual void draw() const;
    void clearDraw();
    void rotateQuarterly(int clockwise);
    void move(int _x, int _y);
    const Point getPoint(int i) const;
    int getNumberOfPoints() const;
    int getBlockMaxX() const;
    int getBlockMinX() const;
    int getBlockMaxY() const;
    int getBlockMinY() const;
    int calcWidthAtHeight(int height) const;
    int calcHeightAtWidth(int width) const;
    int getBlockMinXAtBottom() const;
    int getBlockMaxXAtBottom() const;
};

#endif