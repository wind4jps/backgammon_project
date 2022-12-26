#include <vector>
#include <algorithm>

#include "Chess.h"
#include "conio.h"

void putimagePNG(int x, int y, IMAGE* picture);

void Chess::updateGameMap(ChessPos* pos)
{
	lastPos = *pos;
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

int Chess::getGradeSize()
{
	return gradeSize;
}

int Chess::getChessData(ChessPos* pos)
{
	return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
	return chessMap[row][col];
}

bool Chess::checkOver()
{
	if (checkWin()) {
		Sleep(1500);
		//���弴���Ӯ����ʱ����ѱ���ת���ֵ���������
		if (playerFlag == false) {
			mciSendString("play res/����.mp3", 0, 0, 0);
			loadimage(0, "res/ʤ��.jpg");
		}
		else {
			mciSendString("play res/ʧ��.mp3", 0, 0, 0);
			loadimage(0, "res/ʧ��.jpg");
		}

		_getch();
		return true;
	}
	return false;
}

bool Chess::checkWin()
{
	int row = lastPos.row;
	int col = lastPos.col;

	//�����ж������ڻ�������
	for (int i = 0; i < 5; i++) {
		//����ֱ�5��������ƥ��4����20�����
		if (col - i >= 0 && col - i + 4 < gradeSize &&
			chessMap[row][col - i] == chessMap[row][col - i + 1] &&
			chessMap[row][col - i] == chessMap[row][col - i + 2] &&
			chessMap[row][col - i] == chessMap[row][col - i + 3] &&
			chessMap[row][col - i] == chessMap[row][col - i + 4]) {
			return true;
		}
	}

	for (int i = 0; i < 5; i++) {
		//��ֱ����
		if (row - i >= 0 && row - i + 4 < gradeSize &&
			chessMap[row - i][col] == chessMap[row - i + 1][col] &&
			chessMap[row - i][col] == chessMap[row - i + 2][col] &&
			chessMap[row - i][col] == chessMap[row - i + 3][col] &&
			chessMap[row - i][col] == chessMap[row - i + 4][col]) {
			return true;
		}
	}

	for (int i = 0; i < 5; i++) {
		//"/"����
		if (row + i < gradeSize && row + i - 4 >= 0 &&
			col - i >= 0 && col - i + 4 < gradeSize &&
			chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
			chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
			chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
			chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4]) {
			return true;
		}
	}

	for (int i = 0; i < 5; i++) {
		//"\"����
		if (row - i >= 0 && row - i + 4 < gradeSize &&
			col - i >= 0 && col - i + 4 < gradeSize &&
			chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
			chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
			chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
			chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4]) {
			return true;
		}
	}
	return false;
}

void putimagePNG(int x, int y, IMAGE* picture) {
	//TODO:��д�Զ���ͼ����Ⱦ�ӿ�
}