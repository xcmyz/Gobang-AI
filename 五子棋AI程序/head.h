#pragma once
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