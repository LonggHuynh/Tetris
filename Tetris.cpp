#include <windows.h>
#include <iostream>
using namespace std;

#include "Game.h"

int main() {
	Game game;
	game.init();
	game.run();
}