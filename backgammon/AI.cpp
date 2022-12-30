#include <vector>

#include "AI.h"

void AI::calculateScore()
{
	//玩家连成子的个数
	int personNum = 0;
	//AI连成子的个数
	int botNum = 0;
	//各方向空白的个数
	int emptyNum = 0;
	//两个方向跳三跳四特判
	int jumpPersonNum1 = 0;
	int jumpPersonNum2 = 0;
	int jumpBotNum1 = 0;
	int jumpBotNum2 = 0;
	int jumpEmptyNum1 = 0;
	int jumpEmptyNum2 = 0;

	//初始化评分数组
	for (int i = 0; i < scoreMap.size(); i++) {
		for (int j = 0; j < scoreMap[i].size(); j++) {
			scoreMap[i][j] = 0;
		}
	}

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			//若该点为空白点
			if (chess->getChessData(row, col) == 0) {
				for (int y = -1; y <= 0; y++) {
					for (int x = -1; x <= 1; x++) {
						if (y == 0 && x == 0) {
							continue;
						}
						if (y == 0 && x != 1) {
							continue;
						}
						//重置连子情况
						personNum = 0;
						botNum = 0;
						emptyNum = 0;
						jumpPersonNum1 = 0;
						jumpPersonNum2 = 0;
						jumpBotNum1 = 0;
						jumpBotNum2 = 0;
						jumpEmptyNum1 = 0;
						jumpEmptyNum2 = 0;
						//对黑棋进行评分，正反两个方向每个方向延伸四个子，用以防守判断
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
								//被对方棋子断掉或越界
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
								//被对方棋子断掉或越界
								else {
									break;
								}
							}
						}
						//修改跳三跳四前的评分判断
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
							//被对方棋子断掉或越界
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
								//被对方棋子断掉或越界
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
								//被对方棋子断掉或越界
								else {
									break;
								}
							}
						}
						//修改跳三跳四前的评分判断
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
							//被对方棋子断掉或越界
							else {
								break;
							}
						}*/
						//棋谱连二情况
						if (personNum == 1) {
							scoreMap[row][col] += 10;
						}
						//棋谱连三情况
						else if (personNum == 2) {
							//死三情况
							if (emptyNum == 1) {
								scoreMap[row][col] += 30;
							}
							//活三情况
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
						//连五
						else if (personNum == 4) {
							scoreMap[row][col] += 20000;
						}

						//对两个反向跳三跳四的单独判断
						//跳三
						if (jumpPersonNum1 == 2) {
							if (jumpEmptyNum1 == 1) {
								scoreMap[row][col] += 30;
							}
							else if (jumpEmptyNum1 == 2) {
								scoreMap[row][col] += 40;
							}
						}

						//跳四
						else if (jumpPersonNum1 == 3) {
							if (jumpEmptyNum1 == 1) {
								scoreMap[row][col] += 60;
							}
							else if (jumpEmptyNum1 == 2) {
								scoreMap[row][col] += 5000;
							}
						}

						//跳三
						if (jumpPersonNum2 == 2) {
							if (jumpEmptyNum2 == 1) {
								scoreMap[row][col] += 30;
							}
							else if (jumpEmptyNum2 == 2) {
								scoreMap[row][col] += 40;
							}
						}

						//跳四
						else if (jumpPersonNum2 == 3) {
							if (jumpEmptyNum2 == 1) {
								scoreMap[row][col] += 60;
							}
							else if (jumpEmptyNum2 == 2) {
								scoreMap[row][col] += 5000;
							}
						}

						//进行清空
						emptyNum = 0;
						jumpEmptyNum1 = 0;
						jumpEmptyNum2 = 0;

						//对白棋进行评分，用以进攻判断
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
								//被对方棋子断掉或越界
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
								//被对方棋子断掉或越界
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
								//被对方棋子断掉或越界
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
								//被对方棋子断掉或越界
								else {
									break;
								}
							}
						}
						//未加入跳三跳四前的判断
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

						//普通
						if (botNum == 0) {
							scoreMap[row][col] += 5;
						}
						//活二
						else if (botNum == 1) {
							scoreMap[row][col] += 10;
						}
						else if (botNum == 2) {
							//死三
							if (emptyNum == 1) {
								scoreMap[row][col] += 25;
							}
							//活三
							else if (emptyNum == 2) {
								scoreMap[row][col] += 50;
							}
						}
						else if (botNum == 3) {
							//死四
							if (emptyNum == 1) {
								scoreMap[row][col] += 55;
							}
							//活四
							else if (emptyNum == 2) {
								scoreMap[row][col] += 10000;
							}
						}
						//活五
						else if (botNum >= 4) {
							scoreMap[row][col] += 30000;
						}

						//对跳三跳四的单独判断
						//跳三
						if (jumpBotNum1 == 2) {
							if (jumpEmptyNum1 == 1) {
								scoreMap[row][col] += 25;
							}
							else if (jumpEmptyNum1 == 2) {
								scoreMap[row][col] += 50;
							}
						}
						//跳四
						if (jumpBotNum1 == 3) {
							if (jumpEmptyNum1 == 1) {
								scoreMap[row][col] += 55;
							}
							else if (jumpEmptyNum1 == 2) {
								scoreMap[row][col] += 10000;
							}
						}

						//跳三
						if (jumpBotNum2 == 2) {
							if (jumpEmptyNum2 == 1) {
								scoreMap[row][col] += 25;
							}
							else if (jumpEmptyNum2 == 2) {
								scoreMap[row][col] += 50;
							}
						}
						//跳四
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

	//若有多个点，随机落子
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
