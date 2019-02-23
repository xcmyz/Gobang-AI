#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <queue>
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

struct Coor
{
	int x;
	int y;
};
typedef Coor Coor;

using namespace std;

//Function
Coor Print_Board(BN *board, int *Board_Cursor, string file_name, bool ifprint = false);
bool Player_Operation(char key, int &X, int &Y, int player,
	BN *board, int *Board_Cursor, int &Round_Number);
bool judge(BN *board, int X, int Y, int Current_Player);
int Find_Biggest(BN *board);
void print_queue(queue<Coor> output);
void pop_back_queue(queue<Coor> &input);