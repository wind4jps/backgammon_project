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
	ChessGame(Man* man, AI* ai, Chess* chess);		//�������캯��
	void play();
};

