#ifndef _HUMAN_PLAYER_H_
#define _HUMAN_PLAYER_H_

#include "io_utils.h"
#include "Board.h"

using std::cout;
using std::endl;

class HumanPlayer : public Board {
	bool isLeftSide;
	bool shouldDropBlock = false;
	void checkLeftPlayerKeyHit(char key);
	void checkRightPlayerKeyHit(char key);
public:
	HumanPlayer(int offsetX, int offsetY, bool isLeftSide);
	virtual void actOnNextKey(char key);
	virtual void step(bool drop);
};

#endif