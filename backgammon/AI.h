#include <vector>

#include "Chess.h"

class AI
{
private:
	Chess* chess;

	std::vector<std::vector<int>> scoreMap;

	void calculateScore();

public:
	//��ʼ��AI
	void init(Chess* chess);
	void go();
};

