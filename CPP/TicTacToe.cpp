//Crappy tic tac toe made on visual studio 2012
#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>

enum Tile {Cross, Circle, Nothing};
Tile** board;

int boardWidth, boardHeight;
int inRowToWin;

bool crossTurn;
bool gameOver;

void SetUpGame();
void DrawBoard();
void CheckInput();
void CheckForWin(int y, int x);
void CheckStraight(int posY, int posX, bool searchFromTop);
void CheckDiagonally(int posY, int posX, bool searchFromTopLeft);
void RevealWinner();

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	SetUpGame();
	while (!gameOver){
		CheckInput();
	}
	system("pause");
	return 0;
}

void SetUpGame()
{
	crossTurn = false;
	gameOver = false;

	boardWidth = 3;
	boardHeight = 3;

	inRowToWin = 3;

	board = new Tile*[boardHeight];
	for (int i = 0; i < boardHeight; i++){
		board[i] = new Tile[boardWidth];
	}

	for (int y = 0; y < boardHeight; y++)
		for (int x = 0; x < boardWidth; x++)
			board[y][x] = Nothing;

	DrawBoard();
}

void DrawBoard(){
	system("cls");

	map<int, string> table;
	table[1] = "1"; table[2] = "2"; table[3] = "3"; table[4] = "4"; table[5] = "5"; table[6] = "6";
	table[7] = "7"; table[8] = "8"; table[9] = "9"; table[10] = "a"; table[11] = "b"; table[12] = "c";
	table[13] = "d"; table[14] = "e"; table[15] = "f"; table[16] = "g"; table[17] = "h"; table[18] = "i";
	table[19] = "j"; table[20] = "k"; table[21] = "l"; table[22] = "m"; table[23] = "n"; table[24] = "o";
	table[25] = "p"; table[26] = "q"; table[27] = "r"; table[28] = "s"; table[29] = "t"; table[30] = "u";
	table[31] = "v"; table[32] = "w"; table[33] = "x"; table[34] = "y"; table[35] = "z"; table[36] = "*";

	int num = 0;
	for (int y = 0; y < boardHeight; y++){
		cout << "|";
		for (int x = 0; x < boardWidth; x++){
			num++;
			if (board[y][x] == Cross){
				cout << "X";
				system("color 7");
			} else if (board[y][x] == Circle){
				cout << "O";
			} else {
				cout << table[num];
			}
			cout << "|";
		}
		cout << endl;
		if (y < boardHeight-1){
			for (int i = 0; i < 2 * boardWidth + 1; i++){
				cout << "=";
			}
		}
		cout << endl;
	}
}

void CheckInput(){
	int numInput;
	bool validInput = false;
	while (!validInput){
		DrawBoard();
		if (crossTurn)
			cout << "Cross' Turn (X),\nEnter TileNumber: ";
		else
			cout << "Circle's Turn (O),\nEnter Tile Number: ";
		cin >> numInput;
		cout << numInput;
		if (numInput >= 1 && numInput <= boardWidth * boardHeight 
			&& numInput == (int)numInput){

			int selectedX = (int)(numInput - 1) % boardWidth;
			int selectedY = (int) floor((numInput-1)/boardWidth);

			if (board[selectedY][selectedX] == Nothing){
				board[selectedY][selectedX] = (crossTurn) ? Cross : Circle;
				CheckForWin(selectedY, selectedX);
				crossTurn = !crossTurn;
				validInput = true;
			}
		}
		else{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
}

void CheckForWin(int y, int x){
	//Check Straight
	CheckStraight(y, x, true);
	CheckStraight(y, x, false);

	//CheckDiagonally
	CheckDiagonally(y, x, true);
	CheckDiagonally(y, x, false);

	//CheckForDraw
	bool isDraw = true;
	for (int y = 0; y < boardHeight; y++){
		if (!isDraw){
			break;
		}
		for (int x = 0; x < boardWidth; x++){
			if (board[y][x] == Nothing){
				isDraw = false;
			}
		}
	}
	if (isDraw && !gameOver){
		gameOver = true;
		DrawBoard();
		cout << "Draw! No one wins!" << endl;
	}
}

void CheckStraight(int posY, int posX, bool seachFromTop){
	Tile checkingTitle = (crossTurn) ? Cross : Circle;
	if (seachFromTop){
		for (int i = 0; i <= boardHeight - inRowToWin; i++){
			int countInRow = 0;
			for (int j = 0; j < inRowToWin; j++){
				if (board[i+j][posX] == checkingTitle){
					countInRow++;
				}
			}
			if (countInRow == inRowToWin){
				RevealWinner();
			}
		}
	} else {
		for (int i = 0; i <= boardWidth - inRowToWin; i++){
			int countInRow = 0;
			for (int j = 0; j < inRowToWin; j++){
				if (board[posY][i+j] == checkingTitle){
					countInRow++;
				}
			}
			if (countInRow == inRowToWin){
				RevealWinner();
			}
		}
	}
}

void CheckDiagonally(int posY, int posX, bool searchFromTopLeft){
	Tile checkingTitle = (crossTurn) ? Cross : Circle;
	if (searchFromTopLeft){
		int highX = posX;
		int highY = posY;
		while (highX != 0 && highY != 0){
			highX--;
			highY--;
		}
		for (int i = 0; i < boardHeight; i++){
			int countInRow = 0;
			for (int j = 0; j < inRowToWin; j++){
				if (highY + i + j <= boardHeight - 1 && highX + i + j <= boardHeight){
					if (board[highY+i+j][highX+i+j] == checkingTitle){
						countInRow++;
					}
				}
			}
			if (countInRow == inRowToWin){
				RevealWinner();
			}
		}
	}
	else {
		int highX = posX;
		int highY = posY;
		while (highX != boardWidth - 1 && highY != 0){
			highX++;
			highY--;
		}
		for (int i = 0; i < boardHeight; i++){
			int countInRow = 0;
			for (int j = 0; j < inRowToWin; j++){
				if (highY + i + j <= boardHeight - 1 && highX - i -i >= 0)
				{
					if (board[highY+i+j][highX-i-j] == checkingTitle){
						countInRow++;
					}
				}
			}
			if (countInRow == inRowToWin){
				RevealWinner();
			}
		}
	}
}

void RevealWinner(){
	gameOver = true;
	DrawBoard();
	if (crossTurn)
		cout << "Cross Wins!" << endl;
	else
		cout << "Circle Wins!" << endl;
}


