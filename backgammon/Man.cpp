#include "Man.h"

void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;
	ChessPos pos;
	while (1) {
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBorad(msg.x, msg.y, &pos)) {
			break;
		}
	}

	//Âä×Ó
	chess->chessDown(&pos, CHESS_BLACK);
}
