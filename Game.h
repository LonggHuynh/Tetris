#ifndef _GAME_H_
#define _GAME_H_

#include "io_utils.h"
#include "Board.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Menu.h"

using std::cout;
using std::endl;

class Game {
	enum { ESC = 27, GAME_SPEED = 30 };
	Board* leftBoard = nullptr, * rightBoard = nullptr;
	bool isRunning = false;
	void cleanPlayers();
public:
	~Game() {
		cleanPlayers();
	};
	void init();
	void run();
	void drawBorders();
	void startMenu();
};

#endif