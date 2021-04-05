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
            { 0, 1, 0, 0 },
            { 0, 1, 0, 0 },
            { 0, 1, 0, 0 },
            { 0, 1, 0, 0 }
        },
        {
            { 0, 0, 0, 0 },
            { 0, 1, 1, 0 },
            { 0, 1, 0, 0 },
            { 0, 1, 0, 0 }
        },
        {
            { 0, 0, 1, 0 },
            { 0, 1, 1, 0 },
            { 0, 1, 0, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 0, 1, 0, 0 },
            { 0, 1, 1, 0 },
            { 0, 0, 1, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 0, 0, 0, 0 },
            { 0, 1, 0, 0 },
            { 1, 1, 1, 0 },
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
    /*vector<vector<int>> shape =
    {
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    };  */  
    Point points[4];
    Point &center = points[2];
    void drawShape(char ch);
    void pickPrimaryBlockRotation();
    void pickBlockType(Point offset);
    void setMaxYtoOffset(int y);
public:
    Block() : Block(Point()) {}
	Block(Point offset) {
        pickBlockType(offset);
        pickPrimaryBlockRotation();
        setMaxYtoOffset(offset.getY());
        draw();
	}
	void draw();
    void clearDraw();
    void rotateQuarterly(int clockwise);
    void move(int _x, int _y);
    const Point getPoint(int i);
    int getBlockMaxX();
    int getBlockMinX();
    int getBlockMaxY();
    int getBlockMinY();
};

#endif