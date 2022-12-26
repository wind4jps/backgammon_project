#include <vector>
#include <graphics.h>


typedef enum {
	CHESS_WHITE = -1,	//����
	CHESS_BLACK = 1		//����
} chess_kind_t;

struct ChessPos {
	int row;
	int col;
	ChessPos(int r = 0, int c = 0) :row(r), col(c){}
};

class Chess
{
private:
	//���̳ߴ�
	int gradeSize;
	int margin_x;	//49
	int margin_y;	//49
	//���Ӵ�С
	float chessSize;

	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;

	ChessPos lastPos;
	
	//�洢��ǰ����е������ϵ�����״̬������0Ϊ�հף�1Ϊ���ӣ�-1Ϊ����
	std::vector<std::vector<int>> chessMap;
	
	//true:���巽	false:���巽
	bool playerFlag;

	//������������
	void updateGameMap(ChessPos* pos);

public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	void init();

	//�ж���ָ������(x,y)λ���Ƿ�Ϊ��Ч�������Ϊ��Ч�������������pos��
	bool clickBorad(int x, int y, ChessPos* pos);

	void chessDown(ChessPos* pos, chess_kind_t kind);

	int getGradeSize();

	//��ȡ����ָ��λ�ô����������
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	//�����ж�����Ƿ����
	bool checkOver();

	bool checkWin();
};

