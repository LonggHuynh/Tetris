#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(int offsetX, int offsetY, int level)
	: Board(offsetX, offsetY), level(level) {

}

void ComputerPlayer::calcBlockDestination() {

}

void ComputerPlayer::actOnNextKey(char key) {
	if (!blockDestination) {
		calcBlockDestination();
	}
}

void ComputerPlayer::step(bool drop) {

}