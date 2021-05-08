#ifndef _COMPUTER_PLAYER_H_
#define _COMPUTER_PLAYER_H_

#include "io_utils.h"
#include "numeric"
#include "Board.h"

using std::cout;
using std::endl;
using std::accumulate;

class ComputerPlayer : public Board {
	int level;
	Point* blockDestination = nullptr;
	void moveToDestination();
	void calcBlockDestination();
	Point getLowestFieldPoint();
	virtual void generateNewBlock() override;
	int getWidthAvailableAroundPoint(const Point p, int &leftSpaceStart);
public:
	ComputerPlayer(int offsetX, int offsetY, int level);
	~ComputerPlayer() {
		if (blockDestination)
			delete blockDestination;
	}
	virtual void step();
	virtual void actOnNextKey(char key);
};

#endif