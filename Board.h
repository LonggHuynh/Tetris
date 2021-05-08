#ifndef _BOARD_H_
#define _BOARD_H_
#include <vector>
#include "Point.h"
#include "Block.h"
#include "Bomb.h"

using std::vector;
using std::cout;
using std::endl;

class Board
{
	bool hasLost = false;
	bool checkBlockFieldColision();
	bool checkIfLost();
	void layBlockInField();
	void clearRow(int y);
	void rotateBlock(int quarters);
	bool tryMoveBlock(int x, int y, bool shouldDraw = true);
	void shrinkEmptyRow(int y);
	void checkForCompletedRows(int bottom, int top);
	int steps = 1;
protected:
	virtual void generateNewBlock();
	Block* block = nullptr;
	Bomb* bomb = nullptr;
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
	bool shouldDropBlock = false;
	enum {
		WIDTH = 12,
		HEIGHT = 18,
		DROP_SPEED = 5,
		CLEAR_ROW_DELAY = 10
	};
public:
	Board() : Board(0, 0) {}
	Board(int offsetX, int offsetY) {
		boardOffset = Point(offsetX, offsetY);
		generateNewBlock();
	}
	~Board() {
		if (bomb)
			delete bomb;
		else if (block)
			delete block;
	};
	virtual void step();
	virtual void actOnNextKey(char key) = 0;
	bool isLost();
	void draw();
	void rotateCounterClockwise();
	void rotateClockwise();
	void moveRight();
	void moveLeft();
	bool isOutOfBounds();
	int getRightBorderDeviation();
	int getLeftBorderDeviation();
	bool isOutOfMaxY();
};

#endif