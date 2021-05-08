#include "Game.h"

void Game::init()
{
	this->isRunning = true;
	system("cls");
	drawBorders();
}

void Game::cleanPlayers() {
	if (leftBoard) 
		delete leftBoard;
	if(rightBoard)
		delete rightBoard;
}

void Game::startMenu()
{
	cleanPlayers();
	Menu::showMenu(isRunning);

	int userInput = 0;
	cin >> userInput;

	switch (userInput)
	{
	case 1: //start the game
		this->leftBoard = new HumanPlayer({ 1, 0, true });
		this->rightBoard = new HumanPlayer({ 14, 0, false });
		this->init();
		this->run();
		break;
	case 2: //start the game
		this->leftBoard = new HumanPlayer({ 1, 0, true });
		this->rightBoard = new ComputerPlayer({ 14, 0, 1 });
		this->init();
		this->run();
		break;
	case 3: //start the game
		this->leftBoard = new ComputerPlayer({ 1, 0, 1 });
		this->rightBoard = new ComputerPlayer({ 14, 0, 1 });
		this->init();
		this->run();
		break;
	case 4:
		if (this->isRunning) {
			this->init();
			this->run();
		}
		break;
	case 8: {
		Menu::showInstructions();
		this->startMenu();
		break;
	}
	case 9:
		cout << "GOOD BYE !";
		break;
	default:
		this->startMenu();
		break;
	}
}

void Game::run()
{
	char key = 0;
	int stepsCounter = 0;

	do {
		key = 0;

		if (_kbhit())
		{
			key = _getch();
			if (key == ESC)
			{
				this->startMenu();
				return;
			}
		}
		
		leftBoard->actOnNextKey(key);
		rightBoard->actOnNextKey(key);

		if (!stepsCounter) {
			leftBoard->step();
			rightBoard->step();
		}

		stepsCounter = (++stepsCounter) % 20;
		Sleep(GAME_SPEED);
	} while (key != ESC && !leftBoard->isLost() && !rightBoard->isLost());

	setTextColor(Color::WHITE);
	clear_screen();

	if (!leftBoard->isLost() && rightBoard->isLost()) {
		Menu::declareLeftWinner();
		this->isRunning = false;
		char key = _getch();
		this->startMenu();
	}

	if (leftBoard->isLost() && !rightBoard->isLost()) {
		Menu::declareRightWinner();
		this->isRunning = false;
		char key = _getch();
		this->startMenu();
	}
}

void Game::drawBorders()
{
	for (int i = 0; i < 27; i++) {
		for (int j = 0; j <= 18; j++) {
			if (j == 18 || i == 0 || i == 13 || i == 26) {
				gotoxy(i, j);
				cout << '*' << endl;
			}
		}
	}
}