#pragma once
#include "head.h"

class AI_Class
{
public:
	explicit AI_Class(int Fol, BN *board);
	~AI_Class();

	//计算分数
	int score(BN *temp_board);

	//计算可能落子点对应的分数
	int get_score(BN *original_board, int h, int l, int Player);

	//坐标
	struct coor
	{
		int x;
		int y;
	};
	typedef struct coor coor;

	//生成器（用来提供可以落子的点）
	vector<coor> generator(BN *temp_board);

	//极大极小值搜索
	int maxmin(BN *temp_board, int depth, int player, int alpha, int beta);

	//判断
	void decision(BN *board, int &X, int &Y, int depth = 1);

private:
	int first_or_latter;
	BN copy_board[HandL][HandL];
	int valueofposition[HandL][HandL];

	const int zOO = 234322;
	const int fOO = -zOO;

	//Define score
	int ChengWu = 100000;  //成五
	int HuoSi = 10000;  //活四
	int HuoSan = 1000;  //活三
	int HuoEr = 100;  //活二
	int HuoYi = 10;  //活一

	int SiSi = 1000;  //死四
	int SiSan = 100;  //死三
	int SiEr = 10;  //死二

	void update_cb(BN *board);

	//具体计算不同形式的分数
	void MatchBoard(int *arr, int Player, int &score);

	//Attention：用来限定思考的范围
	//For Attention
	struct Attention
	{
		int h_min;
		int l_min;
		int h_max;
		int l_max;
	};
	typedef struct Attention Attention;

	Attention attention(BN *temp_board);
};
