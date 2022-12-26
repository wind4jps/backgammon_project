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

	//���˸��������������
	int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
	int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};

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
			if (chess->getChessDate(row, col) == 0) {
				//�Ժ���������֣�������������ÿ�����������ĸ���
				for (int d = 0; d < 8; d++) {
					//�����������
					personNum = 0;
					botNum = 0;
					emptyNum = 0;
					for (int i = 1; i <= 4; i++) {
						int curRow = row + dr[d] * i;
						int curCol = col + dc[d] * i;
						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessDate(curRow, curCol) == 1) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessDate(curRow, curCol) == 0) {
							emptyNum++;
						}
						else {
							break;
						}
					}
					for (int i = 1; i <= 4; i++) {
						int curRow = row - dr[d] * i;
						int curCol = col - dc[d] * i;
						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessDate(curRow, curCol) == 1) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessDate(curRow, curCol) == 0) {
							emptyNum++;
						}
						else {
							break;
						}
					}
					//����ɱ�����
					if (personNum == 1) {
						scoreMap[row][col] += 10;
					}
					//�����������
					else if (personNum == 2) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 30;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 40;
						}
					}
					else if (personNum == 3) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 60;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 200;
						}
					}
					else if (personNum == 4) {
						scoreMap[row][col] += 20000;
					}

					//�������
					emptyNum = 0;
					
					//�԰����������
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * dr[d];
						int curCol = col + i * dc[d];
						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessDate(curRow, curCol) == -1) {
							botNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessDate(curRow, curCol) == 0) {
							emptyNum++;
						}
						else {
							break;
						}
					}
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * dr[d];
						int curCol = col - i * dc[d];
						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessDate(curRow, curCol) == -1) {
							botNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessDate(curRow, curCol) == 0) {
							emptyNum++;
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
