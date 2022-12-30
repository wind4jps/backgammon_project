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
	//��������������������
	int jumpPersonNum1 = 0;
	int jumpPersonNum2 = 0;
	int jumpBotNum1 = 0;
	int jumpBotNum2 = 0;
	int jumpEmptyNum1 = 0;
	int jumpEmptyNum2 = 0;

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
						jumpPersonNum1 = 0;
						jumpPersonNum2 = 0;
						jumpBotNum1 = 0;
						jumpBotNum2 = 0;
						jumpEmptyNum1 = 0;
						jumpEmptyNum2 = 0;
						//�Ժ���������֣�������������ÿ�����������ĸ��ӣ����Է����ж�
						if (row + y >= 0 && row + y < size && col + x >= 0 && col + x < size && chess->getChessData(row + y, col + x) == 0) {
							emptyNum++;
							jumpEmptyNum1++;
							for (int i = 2; i <= 4; i++) {
								int curRow = row + y * i;
								int curCol = col + x * i;
								if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 1) {
									jumpPersonNum1++;
								}
								else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0) {
									jumpEmptyNum1++;
									break;
								}
								//���Է����Ӷϵ���Խ��
								else {
									break;
								}
							}
						}
						else if (row + y >= 0 && row + y < size && col + x >= 0 && col + x < size && chess->getChessData(row + y, col + x) == 1) {
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
						}
						//�޸���������ǰ�������ж�
						/*
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
						*/
						if (row - y >= 0 && row - y < size && col - x >= 0 && col - x < size && chess->getChessData(row - y, col - x) == 0) {
							emptyNum++;
							jumpEmptyNum2++;
							for (int i = 2; i <= 4; i++) {
								int curRow = row - y * i;
								int curCol = col - x * i;
								if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 1) {
									jumpPersonNum2++;
								}
								else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0) {
									jumpEmptyNum2++;
									break;
								}
								//���Է����Ӷϵ���Խ��
								else {
									break;
								}
							}
						}
						else if (row - y >= 0 && row - y < size && col - x >= 0 && col - x < size && chess->getChessData(row - y, col - x) == 1) {
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
						}
						//�޸���������ǰ�������ж�
						/*
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
						}*/
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

						//�����������������ĵĵ����ж�
						//����
						if (jumpPersonNum1 == 2) {
							if (jumpEmptyNum1 == 1) {
								scoreMap[row][col] += 30;
							}
							else if (jumpEmptyNum1 == 2) {
								scoreMap[row][col] += 40;
							}
						}

						//����
						else if (jumpPersonNum1 == 3) {
							if (jumpEmptyNum1 == 1) {
								scoreMap[row][col] += 60;
							}
							else if (jumpEmptyNum1 == 2) {
								scoreMap[row][col] += 5000;
							}
						}

						//����
						if (jumpPersonNum2 == 2) {
							if (jumpEmptyNum2 == 1) {
								scoreMap[row][col] += 30;
							}
							else if (jumpEmptyNum2 == 2) {
								scoreMap[row][col] += 40;
							}
						}

						//����
						else if (jumpPersonNum2 == 3) {
							if (jumpEmptyNum2 == 1) {
								scoreMap[row][col] += 60;
							}
							else if (jumpEmptyNum2 == 2) {
								scoreMap[row][col] += 5000;
							}
						}

						//�������
						emptyNum = 0;
						jumpEmptyNum1 = 0;
						jumpEmptyNum2 = 0;

						//�԰���������֣����Խ����ж�
						if (row + y >= 0 && row + y < size && col + x >= 0 && col + x < size && chess->getChessData(row + y, col + x) == 0) {
							emptyNum++;
							jumpEmptyNum1++;
							for (int i = 2; i <= 4; i++) {
								int curRow = row + y * i;
								int curCol = col + x * i;
								if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == -1) {
									jumpBotNum1++;
								}
								else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0) {
									jumpEmptyNum1++;
									break;
								}
								//���Է����Ӷϵ���Խ��
								else {
									break;
								}
							}
						}
						else if (row + y >= 0 && row + y < size && col + x >= 0 && col + x < size && chess->getChessData(row + y, col + x) == -1) {
							for (int i = 1; i <= 4; i++) {
								int curRow = row + y * i;
								int curCol = col + x * i;
								if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == -1) {
									botNum++;
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
						}
						if (row - y >= 0 && row - y < size && col - x >= 0 && col - x < size && chess->getChessData(row - y, col - x) == 0) {
							emptyNum++;
							jumpEmptyNum2++;
							for (int i = 2; i <= 4; i++) {
								int curRow = row - y * i;
								int curCol = col - x * i;
								if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == -1) {
									jumpBotNum2++;
								}
								else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0) {
									jumpEmptyNum2++;
									break;
								}
								//���Է����Ӷϵ���Խ��
								else {
									break;
								}
							}
						}
						else if (row - y >= 0 && row - y < size && col - x >= 0 && col - x < size && chess->getChessData(row - y, col - x) == -1) {
							for (int i = 1; i <= 4; i++) {
								int curRow = row - y * i;
								int curCol = col - x * i;
								if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == -1) {
									botNum++;
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
						}
						//δ������������ǰ���ж�
						/*
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
						*/

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

						//���������ĵĵ����ж�
						//����
						if (jumpBotNum1 == 2) {
							if (jumpEmptyNum1 == 1) {
								scoreMap[row][col] += 25;
							}
							else if (jumpEmptyNum1 == 2) {
								scoreMap[row][col] += 50;
							}
						}
						//����
						if (jumpBotNum1 == 3) {
							if (jumpEmptyNum1 == 1) {
								scoreMap[row][col] += 55;
							}
							else if (jumpEmptyNum1 == 2) {
								scoreMap[row][col] += 10000;
							}
						}

						//����
						if (jumpBotNum2 == 2) {
							if (jumpEmptyNum2 == 1) {
								scoreMap[row][col] += 25;
							}
							else if (jumpEmptyNum2 == 2) {
								scoreMap[row][col] += 50;
							}
						}
						//����
						if (jumpBotNum2 == 3) {
							if (jumpEmptyNum2 == 1) {
								scoreMap[row][col] += 55;
							}
							else if (jumpEmptyNum2 == 2) {
								scoreMap[row][col] += 10000;
							}
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
