#include "head.h"
#include "AI.h"

AI_Class::AI_Class(int Fol, BN *board)
	: first_or_latter(Fol)
{
	//Initialize copy_board
	for (int i = 0; i < HandL; i++)
	{
		for (int j = 0; j < HandL; j++)
		{
			copy_board[i][j].value = (board + i * HandL + j)->value;
			copy_board[i][j].order = (board + i * HandL + j)->order;
		}
	}

	for (int i = 0; i <= (HandL - 1) / 2; i++)
	{
		for (int x = i; x < HandL - i; x++)
		{
			valueofposition[i][x] = i;
			valueofposition[x][i] = i;
			valueofposition[HandL - 1 - i][x] = i;
			valueofposition[x][HandL - 1 - i] = i;
		}
	}
}

AI_Class::~AI_Class()
{
	//Do nothing
}

int AI_Class::score(BN *temp_board)
{
	int human = (first_or_latter == 1) ? 2 : 1;
	int AI = first_or_latter;

	int score_human = 0;
	int score_AI = 0;

	for (int i = 0; i < HandL; i++)
	{
		for (int j = 0; j < HandL; j++)
		{
			// 水平向右
			int arr1[6] = { (temp_board + i * HandL + j)->value };
			for (int k = 1; k < 6; k++)
			{
				if (j + k < HandL) arr1[k] = (temp_board + i * HandL + j + k)->value;
				else arr1[k] = -1;
			}
			MatchBoard(arr1, AI, score_AI);
			MatchBoard(arr1, human, score_human);

			// 垂直向下
			int arr2[6] = { (temp_board + i * HandL + j)->value };
			for (int k = 1; k < 6; k++)
			{
				if (i + k < HandL) arr2[k] = (temp_board + (i + k) * HandL + j)->value;
				else arr2[k] = -1;
			}
			MatchBoard(arr2, AI, score_AI);
			MatchBoard(arr2, human, score_human);

			// 斜下向右
			int arr3[6] = { (temp_board + i * HandL + j)->value };
			for (int k = 1; k < 6; k++)
			{
				if (i + k < HandL && j + k < HandL) arr3[k] = (temp_board + (i + k) * HandL + j + k)->value;
				else arr3[k] = -1;
			}
			MatchBoard(arr3, AI, score_AI);
			MatchBoard(arr3, human, score_human);

			// 斜下向左
			int arr4[6] = { (temp_board + i * HandL + j)->value };
			for (int k = 1; k < 6; k++)
			{
				if (i + k < HandL && j - k >= 0) arr4[k] = (temp_board + (i + k) * HandL + j - k)->value;
				else arr4[k] = -1;
			}
			MatchBoard(arr4, AI, score_AI);
			MatchBoard(arr4, human, score_human);
		}
	}
	int s = score_AI - score_human;
	return s;
}

int AI_Class::get_score(BN *original_board, int h, int l, int Player)
{
	//Initialize
	int scores;
	BN cb[HandL][HandL];

	for (int i = 0; i < HandL; i++)
	{
		for (int j = 0; j < HandL; j++)
		{
			cb[i][j].value = (original_board + i * HandL + j)->value;
			cb[i][j].order = (original_board + i * HandL + j)->order;
		}
	}

	if ((original_board + h * HandL + l)->value != 0)
	{
		cout << "ERROR";
		cout << endl;
	}

	cb[h][l].value = Player;
	cb[h][l].order = Find_Biggest(original_board) + 1;
	scores = score(*cb) + valueofposition[h][l];
	return scores;
}

AI_Class::Attention AI_Class::attention(BN *temp_board)
{
	static Attention tempAttention;
	tempAttention.h_max = (HandL + 1) / 2 - 1;
	tempAttention.h_min = (HandL + 1) / 2 - 1;
	tempAttention.l_max = (HandL + 1) / 2 - 1;
	tempAttention.l_min = (HandL + 1) / 2 - 1;
	for (int x = 0; x < HandL; x++)
	{
		for (int y = 0; y < HandL; y++)
		{
			if ((temp_board + x * HandL + y)->value != 0)
			{
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

vector<AI_Class::coor> AI_Class::generator(BN *temp_board)
{
	//Initial
	Attention temp_a = attention(temp_board);
	static vector<coor> coor_string;
	coor_string.clear();
	//cout << coor_string.size() << endl;

	for (int q = temp_a.h_min; q < temp_a.h_max; q++)
	{
		for (int w = temp_a.l_min; w < temp_a.l_max; w++)
		{
			if ((temp_board + q * HandL + w)->value == 0)
			{
				coor temp;
				temp.x = q;
				temp.y = w;

				coor_string.push_back(temp);
			}
		}
	}

	return coor_string;
}

int AI_Class::maxmin(BN *temp_board, int depth, int player, int alpha, int beta)
{
	if (depth == 0)
	{
		//int t1 = clock();
		int s = score(temp_board);
		return s;
	}

	if (player == first_or_latter)
	{
		//Initial
		int best = fOO;
		vector<coor> temp_coor = generator(temp_board);

		int size = temp_coor.size();
		for (int i = 0; i < size; i++)
		{
			int x_t = temp_coor[i].x;
			int y_t = temp_coor[i].y;
			(temp_board + x_t * HandL + y_t)->value = player;

			int other = 3 - player;
			int new_score = maxmin(temp_board, depth - 1, other, alpha, beta);
			if (new_score > best)
			{
				best = new_score;
			}
			beta = best;

			(temp_board + x_t * HandL + y_t)->value = 0;

			if (beta <= alpha) {
				return beta;
			}
		}

		return best;
	}
	else
	{
		//Initial
		int best = zOO;
		vector<coor> temp_coor = generator(temp_board);

		int size = temp_coor.size();
		for (int i = 0; i < size; i++)
		{
			int x_t = temp_coor[i].x;
			int y_t = temp_coor[i].y;
			(temp_board + x_t * HandL + y_t)->value = player;

			int other = 3 - player;
			int new_score = maxmin(temp_board, depth - 1, other, alpha, beta);
			if (new_score < best)
			{
				best = new_score;
			}
			alpha = best;

			(temp_board + x_t * HandL + y_t)->value = 0;

			if (alpha >= beta) {
				return alpha;
			}
		}

		return best;
	}
}

void AI_Class::decision(BN *board, int &X, int &Y, int depth)
{
	//Update copy_board
	update_cb(board);

	//Think begin
	//Initial
	int FB = Find_Biggest((*copy_board));
	Attention temp_attention = attention((*copy_board));

	int h_min = temp_attention.h_min;
	int h_max = temp_attention.h_max;
	int l_min = temp_attention.l_min;
	int l_max = temp_attention.l_max;

	int best = fOO;
	int best_h = HandL / 2 - 1;
	int best_l = HandL / 2 - 1;

	//Search
	for (int i = h_min; i < h_max; i++)
	{
		for (int j = l_min; j < l_max; j++)
		{
			if (copy_board[i][j].value == 0)
			{
				copy_board[i][j].value = first_or_latter;
				copy_board[i][j].order = FB + 1;

				//Initial
				BN temp_board[HandL][HandL];
				for (int u = 0; u < HandL; u++)
				{
					for (int v = 0; v < HandL; v++)
					{
						temp_board[u][v] = copy_board[u][v];
					}
				}

				int value_cur;
				int h = 3 - first_or_latter;
				value_cur = maxmin((*temp_board), depth, h, fOO, zOO);
				value_cur += valueofposition[i][j];

				if (value_cur > best)
				{
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

void AI_Class::update_cb(BN *board)
{
	for (int i = 0; i < HandL; i++)
	{
		for (int j = 0; j < HandL; j++)
		{
			copy_board[i][j].value = (board + i * HandL + j)->value;
			copy_board[i][j].order = (board + i * HandL + j)->order;
		}
	}
}

void AI_Class::MatchBoard(int *arr, int Player, int &score)
{
	if (arr[0] == Player && arr[1] == Player && arr[2] == Player
		&& arr[3] == Player && arr[4] == Player)
	{
		score += 100000;
		return;
	} // 活五

	if (arr[0] == 0 && arr[1] == Player && arr[2] == Player
		&& arr[3] == Player && arr[4] == Player && arr[5] == 0)
	{
		score += 10000;
		return;
	} // 活四

	if (arr[0] == 0 && arr[1] == Player && arr[2] == Player
		&& arr[3] == Player && arr[4] == 0)
	{
		score += 1000;
		return;
	} // 活三

	if (arr[0] == 3 - Player && arr[1] == Player && arr[2] == Player
		&& arr[3] == Player && arr[4] == Player && arr[5] == 0)
	{
		score += 1000;
		return;
	} // 死四

	if (arr[0] == 0 && arr[1] == Player && arr[2] == Player
		&& arr[3] == Player && arr[4] == Player && arr[5] == 3 - Player)
	{
		score += 1000;
		return;
	} // 死四

	if (arr[0] == 0 && arr[1] == Player && arr[2] == Player && arr[3] == 0)
	{
		score += 100;
		return;
	} // 活二

	if (arr[0] == 3 - Player && arr[1] == Player && arr[2] == Player
		&& arr[3] == Player && arr[4] == 0)
	{
		score += 100;
		return;
	} // 死三

	if (arr[0] == 0 && arr[1] == Player && arr[2] == Player
		&& arr[3] == Player && arr[4] == 3 - Player)
	{
		score += 100;
		return;
	} // 死三

	if (arr[0] == 0 && arr[1] == Player && arr[2] == 0)
	{
		score += 10;
		return;
	} // 活一

	if (arr[0] == 3 - Player && arr[1] == Player && arr[2] == Player
		&& arr[3] == 0)
	{
		score += 10;
		return;
	} // 死二

	if (arr[0] == 0 && arr[1] == Player && arr[2] == Player
		&& arr[3] == 3 - Player)
	{
		score += 10;
		return;
	} // 死二
}
