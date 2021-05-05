#include "Menu.h"

void Menu::showMenu(const bool isRunning)
{
	system("cls");
	if (isRunning) { cout << "WELCOME BACK" << endl; }
	else { cout << "WELCOME !" << endl; }

	cout << "enter your choice and press return :" << endl;
	cout << "(1) Start a new game - Human vs Human" << endl;
	cout << "(2) Start a new game - Human vs Computer" << endl;
	cout << "(3) Start a new game - Computer vs Computer" << endl;

	if (isRunning)
	{
		cout << "(4) Continue a paused game" << endl;
	}
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;
}

void Menu::showInstructions()
{
	system("cls");
	cout << "MOVING INSTRUCTIONS" << endl;
	cout << "For PALAY 1 : D - move right , A - move left , S - rotate clockwise , W - rotate counterclockwise , X - drop" << endl;
	cout << "For PALAY 2 : L - move right , J - move left , K - rotate clockwise , I - rotate counterclockwise , M - drop" << endl;
	cout << "press any key to continue ..." << endl;
	_getch();
}

void Menu::declareLeftWinner() {
	cout << "Left Player Wins" << endl;
	cout << "press any key to continue ..." << endl;
}

void Menu::declareRightWinner() {
	cout << "Right Player Wins" << endl;
	cout << "press any key to continue ..." << endl;
}