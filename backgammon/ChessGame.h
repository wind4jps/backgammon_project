#pragma once

#include "AI.h"
#include "Man.h"
#include "Chess.h"


class ChessGame
{
private:
	Man* man;
	AI* ai;
	Chess* chess;

public:
	//�������캯��
	ChessGame(Man* man, AI* ai, Chess* chess);
	void play();
};

