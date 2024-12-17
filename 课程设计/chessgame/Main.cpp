#include <iostream>
#include "ChessGame.h"

int main() {
	Man man;
	Chess chess(13, 44, 43, 67.3);
	AI ai;
	ChessGame game(&man, &chess, &ai);

	game.play();

	return 0;
}