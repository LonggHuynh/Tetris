#ifndef _GAME_H_
#define _GAME_H_

#include "io_utils.h"
#include "Board.h"

using std::cout;
using std::endl;

class Game {
	enum { ESC = 27, GAME_SPEED = 20};
	Board boards[2] = { {1,0}, {14,0} };
public:	
	void init();
	void run();
	void drawBorders();
};

#endif