#ifndef _BOARD_H_
#define _BOARD_H_
#include <vector>
#include "Point.h"
#include "Block.h"

using std::vector;
using std::cout;
using std::endl;

class Board
{
	enum { 
		WIDTH = 12, 
		HEIGHT = 18, 
		DROP_SPEED = 5, 
		CLEAR_ROW_DELAY = 10
	};
	vector<vector<int>> field = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};
	Point boardOffset;	
	Block* block = nullptr;
	bool hasLost = false;
	bool checkBlockFieldColision();
	bool checkIfLost();
	void layBlockInField();
	void clearRow(int y);
	void rotateBlock(int quarters);
	void moveBlock(int x, int y);
	void shrinkEmptyRow(int y);
	void checkForCompletedRows(int bottom, int top);
	void generateNewBlock();
public:
	Board() : Board(0,0) {}
	Board(int offsetX, int offsetY) {
		boardOffset = Point(offsetX, offsetY);	
		generateNewBlock();
	}
	bool isLost();
	void draw();
	void rotateCounterClockwise();
	void rotateClockwise();
	void moveRight();
	void moveLeft();
	void step(bool drop);
	bool isOutOfBounds();
	bool isOutOfMaxX();
	bool isOutOfMinX();
};

#endif