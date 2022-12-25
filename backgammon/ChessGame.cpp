#include <iostream>

#include "ChessGame.h"

int main() {
	Chess chess(13, 44, 43, 67.4);
	Man man;
	AI ai;
	ChessGame game(&man, &ai, &chess);

	game.play();

	return 0;
}

//���캯�������ڳ�ʼ�����̡�������AI
ChessGame::ChessGame(Man* man, AI* ai, Chess* chess) {
	this->man = man;
	this->ai = ai;
	this->chess = chess;
	ai->init(chess);
	man->init(chess);
}

void ChessGame::play() {
	chess->init();
	while (1) {
		man->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}

		ai->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}
	}
}