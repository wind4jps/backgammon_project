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
	//TODO:�����̽������ݳ�ʼ����ʹ���ܹ�����ʵ������
	//TODO:���ͷ�ļ�����ؿ⣬ʹ���ܹ�����������Ч
}

bool Chess::clickBorad(int x, int y, ChessPos* pos)
{
	//�����������������߽���ڶ��ٸ����ӵĴ�С
	int col = (x - margin_x) / chessSize;
	int row = (y - margin_y) / chessSize;
	
	//���ݴ��ڵļ�������������������Ͻǵ�����
	int leftTopPosX = margin_x + chessSize * col;
	int leftTopPosY = margin_y + chessSize * row;

	//�������ģ����������
	int offset = chessSize * 0.4;

	int len;
	bool selectPos = false;

	//�����жϽ�����ÿ�������ľ��뼴Ϊ���Ӵ�С���뾶����������
	while (1) {
		//�����Ͻǵľ���
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < offset) {
			pos->row = row;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0) {
				selectPos = true;
			}
			break;
		}
		//�����Ͻǵľ��룬��ʽʵΪ(x - (left + chessSize))^2��(left + chessSize)Ϊ���ϽǺ�����
		len = sqrt((x - leftTopPosX - chessSize) * (x - leftTopPosX - chessSize) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < offset) {
			pos->row = row;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) {
				selectPos = true;
			}
			break;
		}
		//�����½ǵľ���
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - chessSize) * (y - leftTopPosY - chessSize));
		if (len < offset) {
			pos->row = row + 1;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) {
				selectPos = true;
			}
			break;
		}
		//�����½ǵľ���
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
	//TODO:��д�Զ���ͼ����Ⱦ�ӿ�
}