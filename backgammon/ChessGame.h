#include "AI.h"
#include "Man.h"
#include "Chess.h"


class ChessGame
{
public:
	ChessGame(Man*, AI*, Chess*);		//�������캯��
	void play();

private:
	Man* man;
	AI* ai;
	Chess* chess;
};

