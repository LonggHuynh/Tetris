#ifndef _COMPUTER_PLAYER_H_
#define _COMPUTER_PLAYER_H_

#include "io_utils.h"
#include "Board.h"

using std::cout;
using std::endl;

class ComputerPlayer : public Board {
	int level;
	Point* blockDestination;
	void calcBlockDestination();
public:
	ComputerPlayer(int offsetX, int offsetY, int level);
	virtual void actOnNextKey(char key);
	virtual void step(bool drop);
};

#endif