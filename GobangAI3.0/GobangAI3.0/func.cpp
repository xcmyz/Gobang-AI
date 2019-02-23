#include "head.h"

//Find biggest
int Find_Biggest(BN *board)
{
	int h = 7;
	int l = 7;
	int max_value = (board + 7 * HandL + 7)->order;
	for (int i = 0; i < HandL; i++)
	{
		for (int j = 0; j < HandL; j++)
		{
			if ((board + i * HandL + j)->order > max_value)
			{
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
Coor Print_Board(BN *board, int *Board_Cursor, string file_name, bool ifprint)
{
	for (int h = 0; h < HandL; h++)
	{
		for (int l = 0; l < HandL; l++)
		{
			if (*(Board_Cursor + h * HandL + l) == 8)
			{
				cout << "©ï ";
			}
			else if ((board + h * HandL + l)->value == 0)
			{
				cout << "¡¤";
			}
			else if ((board + h * HandL + l)->value == 1)
			{
				cout << "¡ñ";
			}
			else if ((board + h * HandL + l)->value == 2)
			{
				cout << "¡ð";
			}
		}
		cout << endl;
	}

	int h = 7;
	int l = 7;
	int max_value = (board + 7 * HandL + 7)->order;
	for (int i = 0; i < HandL; i++)
	{
		for (int j = 0; j < HandL; j++)
		{
			if ((board + i * HandL + j)->order > max_value)
			{
				max_value = (board + i * HandL + j)->order;
				h = i;
				l = j;
			}
		}
	}

	cout << "[" << h << ", " << l << "]";
	cout << " : " << max_value << endl;

	if (ifprint)
	{
		///*FILE* Temp;
		//Temp = fopen("BetterDenoise.txt", "wb+");
		//fclose(Temp);*/
		//ofstream location_out;
		//location_out.open(file_name, std::ios::out | std::ios::app);
		///*int i = 0, j = 0;
		//for (i = 0; i < 200; i++) {
		//	for (j = 0; j < 200; j++) {
		//		if (RB[i][j] == 1) { location_out << ". "; }
		//		else
		//			location_out << " ";
		//	}
		//	location_out << endl;
		//}*/
		//location_out << "[" << h << ", " << l << "]";
		//location_out << " : " << max_value << endl;

		Coor coor;
		coor.x = h;
		coor.y = l;
		return coor;
	}
	else
	{
		Coor coor_temp;
		coor_temp.x = -1;
		coor_temp.y = -1;
		return coor_temp;
	}
}

//Operation
bool Player_Operation(char key, int &X, int &Y, int player,
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
			if (Round_Number == -1)
			{
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

bool judge(BN *board, int X, int Y, int Current_Player)
{
	//Chinese
	int shu = 1, heng = 1, pie = 1, na = 1;

	//Up
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y + i) * HandL + X)->value;
		if (temp_value == (board + Y * HandL + X)->value && (board + Y * HandL + X)->value != 0)
			shu++;
		else
			break;
	}

	//Down
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y - i) * HandL + X)->value;
		if (temp_value == (board + Y * HandL + X)->value && (board + Y * HandL + X)->value != 0)
			shu++;
		else
			break;
	}

	//Left
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y)*HandL + X - i)->value;
		if (temp_value == (board + Y * HandL + X)->value && (board + Y * HandL + X)->value != 0)
			heng++;
		else
			break;
	}

	//Right
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y)*HandL + X + i)->value;
		if (temp_value == (board + Y * HandL + X)->value && (board + Y * HandL + X)->value != 0)
			heng++;
		else
			break;
	}

	//Left down
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y + i) * HandL + X - i)->value;
		if (temp_value == (board + Y * HandL + X)->value && (board + Y * HandL + X)->value != 0)
			pie++;
		else
			break;
	}

	//Right up
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y - i) * HandL + X + i)->value;
		if (temp_value == (board + Y * HandL + X)->value && (board + Y * HandL + X)->value != 0)
			pie++;
		else
			break;
	}

	//Right down
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y + i) * HandL + X + i)->value;
		if (temp_value == (board + Y * HandL + X)->value && (board + Y * HandL + X)->value != 0)
			na++;
		else
			break;
	}

	//Left up
	for (int i = 1; i <= 4; i++)
	{
		int temp_value = (board + (Y - i) * HandL + X - i)->value;
		if (temp_value == (board + Y * HandL + X)->value && (board + Y * HandL + X)->value != 0)
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

void print_queue(queue<Coor> output)
{
	while (!output.empty())
	{
		Coor temp = output.front();
		output.pop();
		cout << "[";
		cout << temp.x << ", " << temp.y;
		cout << "]" << endl;
	}
	//cout << endl;
}

void pop_back_queue(queue<Coor> &input)
{
	int len = input.size();
	while (true)
	{
		if (len == 0)
		{
			cout << "The length of queue is zero." << endl;
			break;
		}
		if (len == 1)
		{
			input.pop();
			break;
		}
		else
		{
			Coor temp = input.front();
			input.pop();
			input.push(temp);
			len = len - 1;
		}
	}
	//print_queue(input);
}