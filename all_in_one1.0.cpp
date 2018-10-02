#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <set>
#include <ctime>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#define HandL 15

//Define board node
struct Board_Node
{
	int value;
	int order;
};
typedef Board_Node BN;

using namespace std;

//Function
void Print_Board(BN *board, int *Board_Cursor);
bool Player_Operation(char key, int &X, int &Y, int player, \
	BN *board, int *Board_Cursor, int &Round_Number);
bool judge(BN *board, int X, int Y, int Current_Player);
int Find_Biggest(BN *board);

class AI_Class {
public:
	explicit AI_Class(int Fol, BN *board);
	~AI_Class();

	//Score
	int score(BN *temp_board);

	//Get scores of one point
	int get_score(BN *original_board, int h, int l, int Player);

	//Generator
	//Coordinate
	struct coor {
		int x;
		int y;
	};
	typedef struct coor coor;

	vector<coor> generator(BN *temp_board);

	//MinMax
	int maxmin(BN *temp_board, int depth, int player);

	//Decision
	void decision(BN *board, int &X, int &Y);

private:
	int first_or_latter;
	BN copy_board[HandL][HandL];
	int valueofposition[HandL][HandL];

	const int zOO = 23432232;
	const int fOO = -zOO;

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

	//Attention
	//For Attention
	struct Attention {
		int h_min;
		int l_min;
		int h_max;
		int l_max;
	};
	typedef struct Attention Attention;

	Attention attention(BN *temp_board);
};


//Find biggest
int Find_Biggest(BN *board) {
	int h = 7;
	int l = 7;
	int max_value = (board + 7 * HandL + 7)->order;
	for (int i = 0; i < HandL; i++) {
		for (int j = 0; j < HandL; j++) {
			if ((board + i * HandL + j)->order > max_value) {
				max_value = (board + i * HandL + j)->order;
				h = i;
				l = j;
			}
		}
	}
	/*cout << "[" << h << ", " << l << "]";
	cout << " : " << max_value << endl;*/

	return max_value;
}

//Print board
void Print_Board(BN *board, int *Board_Cursor)
{
	for (int h = 0; h < HandL; h++)
	{
		for (int l = 0; l < HandL; l++)
		{
			if (*(Board_Cursor + h * HandL + l) == 8)
			{
				cout << "�� ";
			}
			else if ((board + h * HandL + l)->value == 0)
			{
				cout << "��";
			}
			else if ((board + h * HandL + l)->value == 1)
			{
				cout << "��";
			}
			else if ((board + h * HandL + l)->value == 2)
			{
				cout << "��";
			}
		}
		cout << endl;
	}

	int h = 7;
	int l = 7;
	int max_value = (board + 7 * HandL + 7)->order;
	for (int i = 0; i < HandL; i++) {
		for (int j = 0; j < HandL; j++) {
			if ((board + i * HandL + j)->order > max_value) {
				max_value = (board + i * HandL + j)->order;
				h = i;
				l = j;
			}
		}
	}

	cout << "[" << h << ", " << l << "]";
	cout << " : " << max_value << endl;
}

//Operation
bool Player_Operation(char key, int &X, int &Y, int player, \
	BN *board, int *Board_Cursor, int &Round_Number)
{
	int ifcontinue = 1;
	//Control
	switch (key)
	{
		//Operation
		//Up
	case 0x48:
		//Let longitudinal coordinate of corsor cut one
		if (Y > 0 && Y <= HandL - 1)
			Y = Y - 1;
		//Write corsor into board
		*(Board_Cursor + Y * HandL + X) = 8;
		//Restore the value of the original location
		*(Board_Cursor + (Y + 1) * HandL + X) = 0;
		break;

		//Down
	case 0x50:
		if (Y >= 0 && Y < HandL - 1)
			Y = Y + 1;
		*(Board_Cursor + Y * HandL + X) = 8;
		*(Board_Cursor + (Y - 1) * HandL + X) = 0;
		break;

		//Left
	case 0x4B:
		if (X > 0 && X <= HandL - 1)
			X = X - 1;
		*(Board_Cursor + Y * HandL + X) = 8;
		*(Board_Cursor + Y * HandL + (X + 1)) = 0;
		break;

		//Right
	case 0x4D:
		if (X >= 0 && X < HandL - 1)
			X = X + 1;
		*(Board_Cursor + Y * HandL + X) = 8;
		*(Board_Cursor + Y * HandL + (X - 1)) = 0;
		break;

		//Chess moves
	case ' ':
		//Prevent to move in the same place again
		if ((board + Y * HandL + X)->value == 0)
		{
			//When player is white hand
			if (player == 1)
			{
				//White hand moves
				(board + Y * HandL + X)->value = 1;
				//After white hand moves, change player
				player = 2;
			}
			//When player is black hand
			else if (player == 2)
			{
				(board + Y * HandL + X)->value = 2;
				player = 1;
			}
			ifcontinue = 0;
			if (Round_Number == -1) {
				int t = Find_Biggest(board);
				(board + Y * HandL + X)->order = t + 1;
			}
			else
				(board + Y * HandL + X)->order = ++Round_Number;

		}
		break;
	}
	if (ifcontinue)
		return true;
	else
		return false;
}

//bool Player_Operation(char key, int &X, int &Y, int player, BN *board, int *Board_Cursor)
//{
//	int ifcontinue = 1;
//	//Control
//	switch (key)
//	{
//		//Operation
//		//Up
//	case 0x48:
//		//Let longitudinal coordinate of corsor cut one
//		if (Y > 0 && Y <= HandL - 1)
//			Y = Y - 1;
//		//Write corsor into board
//		*(Board_Cursor + Y * HandL + X) = 8;
//		//Restore the value of the original location
//		*(Board_Cursor + (Y + 1) * HandL + X) = 0;
//		break;
//
//		//Down
//	case 0x50:
//		if (Y >= 0 && Y < HandL - 1)
//			Y = Y + 1;
//		*(Board_Cursor + Y * HandL + X) = 8;
//		*(Board_Cursor + (Y - 1) * HandL + X) = 0;
//		break;
//
//		//Left
//	case 0x4B:
//		if (X > 0 && X <= HandL - 1)
//			X = X - 1;
//		*(Board_Cursor + Y * HandL + X) = 8;
//		*(Board_Cursor + Y * HandL + (X + 1)) = 0;
//		break;
//
//		//Right
//	case 0x4D:
//		if (X >= 0 && X < HandL - 1)
//			X = X + 1;
//		*(Board_Cursor + Y * HandL + X) = 8;
//		*(Board_Cursor + Y * HandL + (X - 1)) = 0;
//		break;
//
//		//Chess moves
//	case ' ':
//		//Prevent to move in the same place again
//		if ((board + Y * HandL + X)->value == 0)
//		{
//			//When player is white hand
//			if (player == 1)
//			{
//				//White hand moves
//				(board + Y * HandL + X)->value = 1;
//				//After white hand moves, change player
//				player = 2;
//			}
//			//When player is black hand
//			else if (player == 2)
//			{
//				(board + Y * HandL + X)->value = 2;
//				player = 1;
//			}
//			ifcontinue = 0;
//			(board + Y * HandL + X)->order = Find_Biggest(board) + 1;
//		}
//		break;
//	}
//	if (ifcontinue)
//		return true;
//	else
//		return false;
//}

bool judge(BN *board, int X, int Y, int Current_Player)
{
	//Chinese
	int shu = 1, heng = 1, pie = 1, na = 1;

	//Up
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y + i) * HandL + X)->value;
		if (temp_value == (board + Y * HandL + X)->value \
			&& (board + Y * HandL + X)->value != 0)
			shu++;
		else
			break;
	}

	//Down
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y - i) * HandL + X)->value;
		if (temp_value == (board + Y * HandL + X)->value \
			&& (board + Y * HandL + X)->value != 0)
			shu++;
		else
			break;
	}

	//Left
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y)*HandL + X - i)->value;
		if (temp_value == (board + Y * HandL + X)->value \
			&& (board + Y * HandL + X)->value != 0)
			heng++;
		else
			break;
	}

	//Right
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y)*HandL + X + i)->value;
		if (temp_value == (board + Y * HandL + X)->value \
			&& (board + Y * HandL + X)->value != 0)
			heng++;
		else
			break;
	}

	//Left down
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y + i) * HandL + X - i)->value;
		if (temp_value == (board + Y * HandL + X)->value \
			&& (board + Y * HandL + X)->value != 0)
			pie++;
		else
			break;
	}

	//Right up
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y - i) * HandL + X + i)->value;
		if (temp_value == (board + Y * HandL + X)->value \
			&& (board + Y * HandL + X)->value != 0)
			pie++;
		else
			break;
	}

	//Right down
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y + i) * HandL + X + i)->value;
		if (temp_value == (board + Y * HandL + X)->value \
			&& (board + Y * HandL + X)->value != 0)
			na++;
		else
			break;
	}

	//Left up
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y - i) * HandL + X - i)->value;
		if (temp_value == (board + Y * HandL + X)->value \
			&& (board + Y * HandL + X)->value != 0)
			na++;
		else
			break;
	}

	int ifbreak = false;
	if (shu >= 5 || heng >= 5 || pie >= 5 || na >= 5)
	{
		ifbreak = true;
	}
	if (ifbreak)
		return true;
	else
		return false;
}


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


AI_Class::Attention AI_Class::attention(BN *temp_board) {
	static Attention tempAttention;
	tempAttention.h_max = (HandL + 1) / 2 - 1;
	tempAttention.h_min = (HandL + 1) / 2 - 1;
	tempAttention.l_max = (HandL + 1) / 2 - 1;
	tempAttention.l_min = (HandL + 1) / 2 - 1;
	for (int x = 0; x < HandL; x++) {
		for (int y = 0; y < HandL; y++) {
			if ((temp_board + x * HandL + y)->value != 0) {
				if (x < tempAttention.h_min)
					tempAttention.h_min = x;
				if (y < tempAttention.l_min)
					tempAttention.l_min = y;
				if (x > tempAttention.h_max)
					tempAttention.h_max = x;
				if (y > tempAttention.l_max)
					tempAttention.l_max = y;
			}
		}
	}
	if (tempAttention.h_min != 0)
		tempAttention.h_min = tempAttention.h_min - 2;
	if (tempAttention.h_max != 15)
		tempAttention.h_max = tempAttention.h_max + 2;
	if (tempAttention.l_min != 0)
		tempAttention.l_min = tempAttention.l_min - 2;
	if (tempAttention.l_max != 15)
		tempAttention.l_max = tempAttention.l_max + 2;

	return tempAttention;
}


vector<AI_Class::coor> AI_Class::generator(BN *temp_board) {
	//Initial
	Attention temp_a = attention(temp_board);
	static vector<coor> coor_string;
	coor_string.clear();

	for (int q = temp_a.h_min; q < temp_a.h_max; q++) {
		for (int w = temp_a.l_min; w < temp_a.l_max; w++) {
			if ((temp_board + q * HandL + w)->value == 0) {
				coor temp;
				temp.x = q;
				temp.y = w;

				coor_string.push_back(temp);
			}
		}
	}

	return coor_string;
}


int AI_Class::maxmin(BN *temp_board, int depth, int player) {
	if (depth == 0) {
		//int t1 = clock();
		return score(temp_board);
		//int t2 = clock();
		//cout << (t2 - t1) / CLOCKS_PER_SEC;
	}


	if (player == first_or_latter) {
		//Initial
		int best = fOO;
		vector<coor> temp_coor = generator(temp_board);
		//cout << "Done" << endl;
		//cout << temp_coor.size() << endl;

		for (int i = 0; i < temp_coor.size(); i++) {
			int x_t = temp_coor[i].x;
			int y_t = temp_coor[i].y;
			(temp_board + x_t * HandL + y_t)->value = player;
			int other = 3 - player;

			int new_score = maxmin(temp_board, depth - 1, other);
			if (new_score > best) {
				best = new_score;
			}
		}

		return best;
	}
	else {
		//Initial
		int other = 3 - player;
		int best = zOO;
		vector<coor> temp_coor = generator(temp_board);

		for (int i = 0; i < temp_coor.size(); i++) {
			int x_t = temp_coor[i].x;
			int y_t = temp_coor[i].y;
			(temp_board + x_t * HandL + y_t)->value = player;


			int new_score = maxmin(temp_board, depth - 1, other);
			if (new_score < best) {
				best = new_score;
			}
		}

		return best;
	}
}


void AI_Class::decision(BN *board, int &X, int &Y) {
	//Update copy_board
	update_cb(board);
	//cout << "Done" << endl;

	//Think begin
	//Initial
	int FB = Find_Biggest((*copy_board));
	Attention temp_attention = attention((*copy_board));
	int h_min = temp_attention.h_min;
	int h_max = temp_attention.h_max;
	int l_min = temp_attention.l_min;
	int l_max = temp_attention.l_max;
	/*cout << h_min << endl;
	cout << h_max << endl;
	cout << l_min << endl;
	cout << l_max << endl;*/

	int best = fOO;
	int best_h = HandL / 2 - 1;
	int best_l = HandL / 2 - 1;

	//Search
	for (int i = h_min; i < h_max; i++) {
		for (int j = l_min; j < l_max; j++) {
			if (copy_board[i][j].value == 0) {
				copy_board[i][j].value = first_or_latter;
				copy_board[i][j].order = FB + 1;

				//Initial
				BN temp_board[HandL][HandL];
				for (int u = 0; u < HandL; u++) {
					for (int v = 0; v < HandL; v++) {
						temp_board[u][v] = copy_board[u][v];
					}
				}

				int value_cur = maxmin((*temp_board), \
					1, first_or_latter) + valueofposition[i][j];
				//cout << "Done";
				//cout << valueofposition[i][j] << endl;

				if (value_cur > best) {
					best = value_cur;
					best_h = i;
					best_l = j;
				}

				copy_board[i][j].value = 0;
				copy_board[i][j].order = 0;
			}
		}
	}

	//Means of living
	(board + best_h * HandL + best_l)->value = first_or_latter;
	(board + best_h * HandL + best_l)->order = FB + 1;
	X = best_h;
	Y = best_l;
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

int main()
{
	//Define a board
	BN board[HandL][HandL];
	for (int i = 0; i < HandL; i++)
	{
		for (int j = 0; j < HandL; j++)
		{
			board[i][j].value = 0;
			board[i][j].order = 0;
		}
	}

	//Define a board for cursor
	int Board_Cursor[HandL][HandL];
	for (int i = 0; i < HandL; i++)
	{
		for (int j = 0; j < HandL; j++)
		{
			Board_Cursor[i][j] = 0;
			if ((i == (HandL - 1) / 2) && j == ((HandL - 1) / 2))
			{
				Board_Cursor[i][j] = 8;
			}
		}
	}

	//Define player
	int Human;
	int AI;

	//Define cursor
	int X = (HandL - 1) / 2;
	int Y = (HandL - 1) / 2;

	//Choose mode
	int mode;
	cin >> mode;

	//Start
	if (mode == 1) {
		//Clear all screen
		system("cls");

		//Let player choose first or latter
		cin >> Human;
		getchar();
		AI = (Human == 1) ? 2 : 1;

		//Clear all screen
		system("cls");
		Print_Board((*board), (*Board_Cursor));

		//Initialize player
		int Current_Player = 1;

		//Initialize AI
		AI_Class levi(AI, (*board));

		//Round number
		int Round_Number = 0;

		while (true)
		{
			if (Current_Player == AI)
			{
				Board_Cursor[Y][X] = 0;
				//AI first
				levi.decision((*board), Y, X);
				//cout << "Done";
				//Board_Cursor[X][Y] = 8;
				system("cls");
				Print_Board((*board), (*Board_Cursor));
				//cout << "Done";
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "AI win !" << endl;
					break;
				}
				Current_Player = Human;

				//Human
				while (true)
				{
					char key = getch();
					int a = -1;
					if (Player_Operation(key, X, Y, Current_Player, (*board), (*Board_Cursor), a))
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor));
					}
					else
					{
						system("cls");
						//board[Y][X].order = Find_Biggest((*board)) + 1;
						Print_Board((*board), (*Board_Cursor));
						break;
					}
				}
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Human win !" << endl;
					break;
				}
				Current_Player = AI;
			}
			else
			{
				//Human first
				while (true)
				{
					char key = getch();
					int a = -1;
					if (Player_Operation(key, X, Y, Current_Player, (*board), (*Board_Cursor), a))
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor));
					}
					else
					{
						system("cls");
						//board[Y][X].order = Find_Biggest((*board)) + 1;
						Print_Board((*board), (*Board_Cursor));
						break;
					}
				}
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Human win !" << endl;
					break;
				}
				Current_Player = AI;

				Board_Cursor[Y][X] = 0;
				//AI latter
				levi.decision((*board), Y, X);
				//cout << "Done";
				//Board_Cursor[X][Y] = 8;
				Print_Board((*board), (*Board_Cursor));
				//cout << "Done";
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "AI win !" << endl;
					break;
				}
				Current_Player = Human;
			}
		}
	}
	else if (mode == 2) {

		int Human_1 = 1;
		int Human_2 = 2;

		//Clear all screen
		system("cls");
		Print_Board((*board), (*Board_Cursor));

		int Current_Player = 1;

		//Round number
		int Round_Number = 0;

		while (true)
		{
			if (Current_Player == Human_1)
			{
				while (true)
				{
					char key = getch();
					if (Player_Operation(key, X, Y, Current_Player, \
						(*board), (*Board_Cursor), Round_Number))
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor));
					}
					else
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor));
						break;
					}
				}
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Win !" << endl;
					break;
				}
				Current_Player = Human_2;

				while (true)
				{
					char key = getch();
					if (Player_Operation(key, X, Y, Current_Player, \
						(*board), (*Board_Cursor), Round_Number))
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor));
					}
					else
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor));
						break;
					}
				}
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Win !" << endl;
					break;
				}
				Current_Player = Human_1;
			}
			else
			{
				while (true)
				{
					char key = getch();
					if (Player_Operation(key, X, Y, Current_Player, \
						(*board), (*Board_Cursor), Round_Number))
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor));
					}
					else
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor));
						break;
					}
				}
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Win !" << endl;
					break;
				}
				Current_Player = Human_1;

				//AI latter
				while (true)
				{
					char key = getch();
					if (Player_Operation(key, X, Y, Current_Player, \
						(*board), (*Board_Cursor), Round_Number))
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor));
					}
					else
					{
						system("cls");
						Print_Board((*board), (*Board_Cursor));
						break;
					}
				}
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Win !" << endl;
					break;
				}
				Current_Player = Human_2;
			}
		}
	}
	else if (mode == 3) {
		int AI1 = 1;
		int AI2 = 2;

		//Clear all screen
		system("cls");
		Print_Board((*board), (*Board_Cursor));

		//Initialize player
		int Current_Player = AI1;

		//Initialize AI
		AI_Class AI_1(AI1, (*board));
		AI_Class AI_2(AI2, (*board));

		//Round number
		int Round_Number = 0;

		while (true)
		{
			if (Current_Player == AI1)
			{
				Board_Cursor[Y][X] = 0;
				AI_1.decision((*board), Y, X);
				//cout << "Done";
				system("cls");
				Print_Board((*board), (*Board_Cursor));
				//cout << "Done";
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Win !" << endl;
					break;
				}
				Current_Player = AI2;

				Board_Cursor[Y][X] = 0;
				AI_2.decision((*board), Y, X);
				//cout << "Done";
				system("cls");
				Print_Board((*board), (*Board_Cursor));
				//cout << "Done";
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Win !" << endl;
					break;
				}
				Current_Player = AI1;
			}
			else
			{
				Board_Cursor[X][Y] = 0;
				AI_2.decision((*board), X, Y);
				//cout << "Done";
				system("cls");
				Print_Board((*board), (*Board_Cursor));
				//cout << "Done";
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Win !" << endl;
					break;
				}
				Current_Player = AI1;

				Board_Cursor[X][Y] = 0;
				AI_1.decision((*board), X, Y);
				//cout << "Done";
				system("cls");
				Print_Board((*board), (*Board_Cursor));
				//cout << "Done";
				if (judge((*board), X, Y, Current_Player))
				{
					cout << "Win !" << endl;
					break;
				}
				Current_Player = AI2;
			}
		}
	}

	system("pause");
	return 0;
}
