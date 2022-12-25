#include <vector>
#include <graphics.h>


typedef enum {
	CHESS_WHITE = -1,	//白棋
	CHESS_BLACK = 1		//黑棋
} chess_kind_t;

struct ChessPos {
	int row;
	int col;
};

class Chess
{
private:
	//棋盘尺寸
	int gradeSize;
	int margin_x;	//49
	int margin_y;	//49
	//棋子大小
	float chessSize;

	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;
	
	//存储当前棋局中的棋盘上的棋子状态，其中0为空白，1为黑子，-1为白子
	std::vector<std::vector<int>> chessMap;
	
	//true:黑棋方	false:白棋方
	bool playerFlag;

	//更新棋子数据
	void updateGameMap(ChessPos* pos);

public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	void init();

	//判断在指定坐标(x,y)位置是否为有效点击，若为有效点击，则存入参数pos中
	bool clickBorad(int x, int y, ChessPos* pos);

	void chessDown(ChessPos* pos, chess_kind_t kind);

	int getGradeSize();

	int getChessDate(ChessPos* pos);
	int getChessDate(int row, int col);

	//用于判断棋局是否结束
	bool checkOver();
};

