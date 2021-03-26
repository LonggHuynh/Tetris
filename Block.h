#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "io_utils.h"
#include "Point.h"
#include <vector>

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
    Point& center = points[1];
    void drawShape(char ch);

public:
    Block() : Block(Point()) {}
	Block(Point offset) {
        int blockType = getRandom(0,6);
        int rotation = getRandom(-3, 3);        

        for (size_t i = 0, p = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                /*shape[i][j] = 0;
                shape[i][j] = block_list[blockType][i][j];*/
                if (block_list[blockType][i][j] == 1) {
                    points[p++].setPosition(
                        offset.getX() + i, 
                        offset.getY() + j
                    );
                }
            }
        }

        //rotateQuarterly(true);
	}
	void draw();
    void clearDraw();
    void rotateQuarterly(int clockwise);
    void move(int _x, int _y);
    const Point getPoint(int i);
    int getBlockMaxX();
    int getBlockMinX();
};

#endif