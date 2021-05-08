#ifndef _MENU_H_
#define _MENU_H_

#include "io_utils.h"

using std::cout;
using std::endl;

class Menu {
public:
	static void showMenu(const bool isRunning);
	static int chooseComputerLevel(const char string[]);
	static void showInstructions();
	static void declareLeftWinner();
	static void declareRightWinner();
};

#endif