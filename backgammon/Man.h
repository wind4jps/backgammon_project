#pragma once

#include "Chess.h"

class Man
{
private:
	Chess* chess;
public:
	void init(Chess* chess);
	void go();
};

