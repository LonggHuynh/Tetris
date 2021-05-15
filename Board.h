#ifndef _BOARD_H_
#define _BOARD_H_
#include <vector>
#include "io_utils.h"
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
protected:
	virtual void generateNewBlock();
	Block* block = nullptr;
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
	virtual ~Board() {
			delete block;
	};
	virtual void step();
	virtual void actOnNextKey(char key) = 0;
	bool isLost() const;
	void draw() const;
	void rotateCounterClockwise();
	void rotateClockwise();
	void moveRight();
	void moveLeft();
	bool isOutOfBounds() const;
	int getRightBorderDeviation() const;
	int getLeftBorderDeviation() const;
	bool isOutOfMaxY() const;
};

#endif