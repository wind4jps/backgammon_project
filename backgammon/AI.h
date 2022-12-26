#include <vector>

#include "Chess.h"

class AI
{
private:
	Chess* chess;

	std::vector<std::vector<int>> scoreMap;

	void calculateScore();

	//计算评分并从评分中找到最大分数位置
	ChessPos think();

public:
	//初始化AI
	void init(Chess* chess);
	void go();
};

