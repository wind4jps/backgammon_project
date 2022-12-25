#include <vector>
#include <algorithm>

#include "Chess.h"

void putimagePNG(int x, int y, IMAGE* picture);

void Chess::updateGameMap(ChessPos* pos)
{
	ChessPos lastPos = *pos;
	chessMap[pos->row][pos->col] = playerFlag ? 1 : -1;
	playerFlag = !playerFlag;
}

Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chessSize = chessSize;
	playerFlag = CHESS_BLACK;

	for (int i = 0; i < gradeSize; i++) {
		std::vector<int> row;
		for (int j = 0; j < gradeSize; j++) {
			row.push_back(0);
		}

		chessMap.push_back(row);
	}
}

void Chess::init()
{
	//TODO:对棋盘进行数据初始化，使得能够看到实际棋盘
	//TODO:添加头文件和相关库，使得能够播放落子音效
}

bool Chess::clickBorad(int x, int y, ChessPos* pos)
{
	//计算点击处距离两个边界存在多少个棋子的大小
	int col = (x - margin_x) / chessSize;
	int row = (y - margin_y) / chessSize;
	
	//根据存在的间隔棋子数计算点击处左上角的坐标
	int leftTopPosX = margin_x + chessSize * col;
	int leftTopPosY = margin_y + chessSize * row;

	//鼠标点击的模糊距离上限
	int offset = chessSize * 0.4;

	int len;
	bool selectPos = false;

	//以下判断建立在每两个点间的距离即为棋子大小（半径）的条件下
	while (1) {
		//到左上角的距离
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < offset) {
			pos->row = row;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0) {
				selectPos = true;
			}
			break;
		}
		//到右上角的距离，算式实为(x - (left + chessSize))^2，(left + chessSize)为右上角横坐标
		len = sqrt((x - leftTopPosX - chessSize) * (x - leftTopPosX - chessSize) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < offset) {
			pos->row = row;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) {
				selectPos = true;
			}
			break;
		}
		//到左下角的距离
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - chessSize) * (y - leftTopPosY - chessSize));
		if (len < offset) {
			pos->row = row + 1;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) {
				selectPos = true;
			}
			break;
		}
		//到右下角的距离
		len = sqrt((x - leftTopPosX - chessSize) * (x - leftTopPosX - chessSize) + (y - leftTopPosY - chessSize) * (y - leftTopPosY - chessSize));
		if (len < offset) {
			pos->row = row + 1;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) {
				selectPos = true;
			}
			break;
		}
	}
	return selectPos;
}

void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
	mciSendString("play res/down7.WAV", 0, 0, 0);

	int x = margin_x + pos->col * chessSize - 0.5 * chessSize;
	int y = margin_y + pos->row * chessSize - 0.5 * chessSize;

	if (kind == CHESS_WHITE) {
		putimagePNG(x, y, &chessWhiteImg);
	}
	else {
		putimagePNG(x, y, &chessBlackImg);
	}

	updateGameMap(pos);
}

void putimagePNG(int x, int y, IMAGE* picture) {
	//TODO:编写自定义图形渲染接口
}