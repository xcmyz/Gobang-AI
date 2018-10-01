#include "head.h"
#include "AI_Class.h"

AI_Class::AI_Class(int Fol, BN *board)
	:first_or_latter(Fol)
{
	//Initialize copy_board
	for (int i = 0; i < HandL; i++) {
		for (int j = 0; j < HandL; j++) {
			copy_board[i][j].value = (board + i * HandL + j)->value;
			copy_board[i][j].order = (board + i * HandL + j)->order;
		}
	}

	for (int i = 0; i <= (HandL - 1) / 2; i++) {
		for (int x = i; x < HandL - i; x++) {
			valueofposition[i][x] = i;
			valueofposition[x][i] = i;
			valueofposition[HandL - 1 - i][x] = i;
			valueofposition[x][HandL - 1 - i] = i;
		}
	}
}

AI_Class::~AI_Class() {
	//Do nothing
}

int AI_Class::score(BN *temp_board) {
	//Initialize
	int human = (first_or_latter == 1) ? 2 : 1;
	int AI = first_or_latter;

	//Temp score
	int score_human = 0;
	int score_AI = 0;

	//Search the board
	//Horizontal
	for (int i = 0; i < HandL; i++) {
		vector<int> tempArr_1;
		for (int j = 0; j < HandL; j++) {
			tempArr_1.push_back((temp_board + i * HandL + j)->value);
		}

		MatchBoard(tempArr_1, AI, score_AI);
		MatchBoard(tempArr_1, human, score_human);
	}

	//Vertical
	for (int i = 0; i < HandL; i++) {
		vector<int> tempArr_2;
		for (int j = 0; j < HandL; j++) {
			tempArr_2.push_back((temp_board + j * HandL + i)->value);
		}

		MatchBoard(tempArr_2, AI, score_AI);
		MatchBoard(tempArr_2, human, score_human);
	}

	//Left oblique
	//Upper Half part
	for (int i = 0; i < HandL; i++) {
		vector<int> tempArr_3_1;
		for (int j = HandL; j >= i; j--) {
			tempArr_3_1.push_back((temp_board + \
				(HandL - j) * HandL + HandL - j + i)->value);
		}

		MatchBoard(tempArr_3_1, AI, score_AI);
		MatchBoard(tempArr_3_1, human, score_human);
	}
	//Lower half part
	for (int i = 0; i < HandL; i++) {
		vector<int> tempArr_3_2;
		for (int j = HandL; j >= i; j--) {
			tempArr_3_2.push_back((temp_board + \
				(HandL - j + i) * HandL + HandL - j)->value);
		}

		MatchBoard(tempArr_3_2, AI, score_AI);
		MatchBoard(tempArr_3_2, human, score_human);
	}
	//Right oblique
	//Upper Half part
	for (int i = 0; i < HandL; i++) {
		vector<int> tempArr_4_1;
		for (int j = 0; j <= i; j++) {
			tempArr_4_1.push_back((temp_board + j * HandL + i - j)->value);
		}

		MatchBoard(tempArr_4_1, AI, score_AI);
		MatchBoard(tempArr_4_1, human, score_human);
	}
	//Lower half part
	for (int i = 0; i < HandL; i++) {
		vector<int> tempArr_4_2;
		for (int j = 0; j <= HandL - 1 - i; j++) {
			tempArr_4_2.push_back((temp_board + \
				(i + j) * HandL + HandL - 1 - j)->value);
		}

		MatchBoard(tempArr_4_2, AI, score_AI);
		MatchBoard(tempArr_4_2, human, score_human);
	}

	//Get score
	int s = score_AI - score_human;
	return s;
}

int AI_Class::get_score(BN *original_board, int h, int l, int Player) {
	//Initialize
	int scores;
	BN cb[HandL][HandL];

	for (int i = 0; i < HandL; i++) {
		for (int j = 0; j < HandL; j++) {
			cb[i][j].value = (original_board + i * HandL + j)->value;
			cb[i][j].order = (original_board + i * HandL + j)->order;
		}
	}

	if ((original_board + h * HandL + l)->value != 0) {
		cout << "ERROR";
		cout << endl;
	}

	cb[h][l].value = Player;
	cb[h][l].order = Find_Biggest(original_board) + 1;
	scores = score(*cb) + valueofposition[h][l];
	return scores;
}

void AI_Class::decision(BN *board, int &X, int &Y) {
	//Update copy_board
	update_cb(board);
}

void AI_Class::update_cb(BN *board) {
	for (int i = 0; i < HandL; i++) {
		for (int j = 0; j < HandL; j++) {
			copy_board[i][j].value = (board + i * HandL + j)->value;
			copy_board[i][j].order = (board + i * HandL + j)->order;
		}
	}
}

void  AI_Class::MatchBoard(vector<int>tempArr, int Player, int &score) {
	//Get size
	int size = tempArr.size();
	for (int i = 0; i < size;) {
		if (tempArr[i] == Player) {
			int kase = 0;
			int end;
			for (int x = i; x < size; x++) {
				if (tempArr[x] == Player) {
					kase++;
					end = x;
				}
				else {
					end = x - 1;
					break;
				}
			}
			//0 for neither; 1 for one side; 2 for both sides
			int iflive = 0;
			//Front
			if (i == 0)
				iflive++;
			else {
				if (tempArr[i - 1] == 3 - Player)
					iflive++;
				else if (tempArr[i - 1] == Player) {
					//printf("There are some errors in the Levi. \n");
					cout << "ERROR" << endl;
				}

			}
			//Tail
			if (end == size - 1)
				iflive++;
			else {
				if (tempArr[end + 1] == 3 - Player)
					iflive++;
				else if (tempArr[end + 1] == Player) {
					//printf("There are some errors in the Levi. \n");
					cout << "ERROR" << endl;
				}

			}
			//Add score
			if (iflive == 2) {
				//forbid 0 11110
				//???
				if ((kase == 5)) {
					score += ChengWu;
				}
			}
			else if (iflive == 1) {
				switch (kase) {
					//Fuck Fuck Fuck
				case 5:
					score += ChengWu;
					break;
				case 4:
					score += SiSi;
					break;
				case 3:
					score += SiSan;
					break;
				case 2:
					score += SiEr;
					break;
				default:
					break;
				}
			}
			else {
				switch (kase) {
				case 5:
					score += ChengWu;
					break;
				case 4:
					score += HuoSi;
					break;
				case 3:
					score += HuoSan;
					break;
				case 2:
					score += HuoEr;
					break;
				case 1:
					score += HuoYi;
					break;
				default:
					break;
				}
			}
			//Operation of i
			i = end + 1;
		}
		else
			i++;
	}
}
