#include <vector>

#include "AI.h"

void AI::calculateScore()
{
	//��������ӵĸ���
	int personNum = 0;
	//AI�����ӵĸ���
	int botNum = 0;
	//������հ׵ĸ���
	int emptyNum = 0;

	//��ʼ����������
	for (int i = 0; i < scoreMap.size(); i++) {
		for (int j = 0; j < scoreMap[i].size(); j++) {
			scoreMap[i][j] = 0;
		}
	}

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			//���õ�Ϊ�հ׵�
			if (chess->getChessData(row, col) == 0) {
				for (int y = -1; y <= 0; y++) {
					for (int x = -1; x <= 1; x++) {
						if (y == 0 && x == 0) {
							continue;
						}
						if (y == 0 && x != 1) {
							continue;
						}
						//�����������
						personNum = 0;
						botNum = 0;
						emptyNum = 0;
						//�Ժ���������֣�������������ÿ�����������ĸ��ӣ����Է����ж�
						for (int i = 1; i <= 4; i++) {
							int curRow = row + y * i;
							int curCol = col + x * i;
							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 1) {
								personNum++;
							}
							else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0) {
								emptyNum++;
								break;
							}
							//���Է����Ӷϵ���Խ��
							else {
								break;
							}
						}
						for (int i = 1; i <= 4; i++) {
							int curRow = row - y * i;
							int curCol = col - x * i;
							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 1) {
								personNum++;
							}
							else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0) {
								emptyNum++;
								break;
							}
							//���Է����Ӷϵ���Խ��
							else {
								break;
							}
						}
						//�����������
						if (personNum == 1) {
							scoreMap[row][col] += 10;
						}
						//�����������
						else if (personNum == 2) {
							//�������
							if (emptyNum == 1) {
								scoreMap[row][col] += 30;
							}
							//�������
							else if (emptyNum == 2) {
								scoreMap[row][col] += 40;
							}
						}
						else if (personNum == 3) {
							if (emptyNum == 1) {
								scoreMap[row][col] += 60;
							}
							else if (emptyNum == 2) {
								scoreMap[row][col] += 5000;
							}
						}
						//����
						else if (personNum == 4) {
							scoreMap[row][col] += 20000;
						}

						//�������
						emptyNum = 0;

						//�԰���������֣����Խ����ж�
						for (int i = 1; i <= 4; i++) {
							int curRow = row + y * i;
							int curCol = col + y * i;
							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == -1) {
								botNum++;
							}
							else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0) {
								emptyNum++;
								break;
							}
							else {
								break;
							}
						}
						for (int i = 1; i <= 4; i++) {
							int curRow = row - y * i;
							int curCol = col - y * i;
							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == -1) {
								botNum++;
							}
							else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0) {
								emptyNum++;
								break;
							}
							else {
								break;
							}
						}
						//��ͨ
						if (botNum == 0) {
							scoreMap[row][col] += 5;
						}
						//���
						else if (botNum == 1) {
							scoreMap[row][col] += 10;
						}
						else if (botNum == 2) {
							//����
							if (emptyNum == 1) {
								scoreMap[row][col] += 25;
							}
							//����
							else if (emptyNum == 2) {
								scoreMap[row][col] += 50;
							}
						}
						else if (botNum == 3) {
							//����
							if (emptyNum == 1) {
								scoreMap[row][col] += 55;
							}
							//����
							else if (emptyNum == 2) {
								scoreMap[row][col] += 10000;
							}
						}
						//����
						else if (botNum >= 4) {
							scoreMap[row][col] += 30000;
						}
					}
				}
			}
		}
	}
}

ChessPos AI::think()
{
	calculateScore();
	int maxScore = 0;

	std::vector<ChessPos> maxPos;


	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (chess->getChessData(row, col) == 0) {
				if (scoreMap[row][col] > maxScore) {
					maxScore = scoreMap[row][col];
					maxPos.clear();
					maxPos.push_back(ChessPos(row, col));
				}
				else if (scoreMap[row][col] == maxScore) {
					maxPos.push_back(ChessPos(row, col));
				}
			}
		}
	}

	//���ж���㣬�������
	int index = rand() % maxPos.size();
	return maxPos[index];
}

void AI::init(Chess* chess)
{
	this->chess = chess;

	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++) {
		std::vector<int> row;
		for (int j = 0; j < size; j++) {
			row.push_back(0);
		}
		scoreMap.push_back(row);
	}
}

void AI::go()
{
	ChessPos pos = think();
	Sleep(1000);
	chess->chessDown(&pos, CHESS_WHITE);
}
