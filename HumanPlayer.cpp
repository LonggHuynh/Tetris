#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(int offsetX, int offsetY, bool isLeftSide)
	: Board(offsetX, offsetY), isLeftSide(isLeftSide) {}

void HumanPlayer::actOnNextKey(char key) {
	if (isLeftSide)
		checkLeftPlayerKeyHit(key);
	else
		checkRightPlayerKeyHit(key);
}

void HumanPlayer::checkLeftPlayerKeyHit(char key) {
	if (key == 'W' || key == 'w') {
		rotateCounterClockwise();
	}
	else if (key == 'S' || key == 's') {
		rotateClockwise();
	}
	else if (key == 'D' || key == 'd') {
		moveRight();
	}
	else if (key == 'A' || key == 'a') {
		moveLeft();
	}
	else if (key == 'X' || key == 'x') {
		shouldDropBlock = true;
	}
}

void HumanPlayer::checkRightPlayerKeyHit(char key) {
	if (key == 'I' || key == 'i') {
		rotateCounterClockwise();
	}
	else if (key == 'K' || key == 'k') {
		rotateClockwise();
	}
	else if (key == 'L' || key == 'l') {
		moveRight();
	}
	else if (key == 'J' || key == 'j') {
		moveLeft();
	}
	else if (key == 'M' || key == 'm') {
		shouldDropBlock = true;
	}
}

void HumanPlayer::step(bool drop) {
	Board::step(shouldDropBlock);
	shouldDropBlock = false;
}