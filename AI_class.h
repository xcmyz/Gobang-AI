#pragma once
#include "head.h"

class AI_Class {
public:
	explicit AI_Class(int Fol, BN *board);
	~AI_Class();

	//Score
	int score(BN *temp_board);

	//Get scores of one point
	int get_score(BN *original_board, int h, int l, int Player);

	//Generator


	//Decision
	void decision(BN *board, int &X, int &Y);

private:
	int first_or_latter;
	BN copy_board[HandL][HandL];
	int valueofposition[HandL][HandL];

	//Define score
	//Huo means two sides have nothing
	int ChengWu = 100000;
	int HuoSi = 10000;
	int HuoSan = 1000;
	int HuoEr = 100;
	int HuoYi = 10;
	//Si means one sides have a chess piece
	int SiSi = 1000;
	int SiSan = 100;
	int SiEr = 10;

	//Update copy_board
	void update_cb(BN *board);

	//Match board
	void MatchBoard(vector<int>tempArr, int Player, int &score);
};
