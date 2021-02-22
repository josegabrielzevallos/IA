#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <cmath>
#include <random>

using namespace std;

template <typename T, size_t N> const T* mybegin(const T(&a)[N]) { return a; }
template <typename T, size_t N> const T* myend(const T(&a)[N]) { return a + N; }

vector<char> board;

bool isValidMove(int pos, vector<char> boardT) //check in board if can move in a empty box
{
	if (boardT[pos] == 'C')
	{
		return true;
	}
	return false;
}

bool isPossibleMove(vector<char> boardw)
{
	for (size_t i = 0; i < boardw.size(); i++)
	{
		if (boardw[i] == 'C')
		{
			return true;
		}
	}
	return false;
}

void printboardchar(vector<char> board)
{
	int count = 0;
	for (size_t i = 0; i < board.size(); i++)
	{
		count++;
		cout << board[i];
		if (count % 3 == 0)
		{
			cout << endl;
		}
		else
		{
			cout << "-";
		}
	}
	//cout << endl;
}

void printVector(vector<int> liste)
{
	for (int i = 0; i < liste.size(); i++)
	{
		cout << liste[i] << ", ";
	}
	cout << endl;
}

class MiniMax
{
public:
	vector<char>internalBoard;
	bool isMax = false;
	bool isMin = false;
	int deep;// Profundidad actual
	int RValue;// Valor que resulta de evaluar
	char Player; //Valor de jugador que le toca en ese nodo
	int MinimaxVal;
	vector <MiniMax*> sons;
	int Possitive;
	int Neggative;

	MiniMax(int _deep, bool _isMax, bool _isMin, vector<char> Iboard, char _Player)
	{
		isMax = _isMax;
		isMin = _isMin;
		deep = _deep;
		Player = _Player;
		internalBoard = Iboard;
		RValue = evaluate();
		if (deep - 1 > 0 and isPossibleMove(internalBoard) == true)
		{
			for (size_t i = 0; i < 9; i++)
			{
				if (isValidMove(i, internalBoard) == true)
				{
					vector<char>Tboard0 = internalBoard;
					Tboard0[i] = Player;
					char AuxChar = 'C';
					if (Player == 'A') { AuxChar = 'B'; }
					else { AuxChar = 'A'; }
					bool MinTemp, MaxTemp;
					if (isMax == true)
					{
						MinTemp = true;
						MaxTemp = false;
					}
					if (isMin == true)
					{
						MinTemp = false;
						MaxTemp = true;
					}
					MiniMax* NewSon = new MiniMax(deep - 1, MaxTemp, MinTemp, Tboard0, AuxChar);
					sons.push_back(NewSon);
				}
			}
		}
		else
		{
			MinimaxVal = RValue;
		}
	}

	int evaluate() // usa internalBoard, ve lo mas favorable para la IA
	{
		//A = square <--- EL HUMANO
		//B = circle <--- LA IA
		int Positive = 0;
		int Negative = 0;
		if ((internalBoard[2] == 'B' or internalBoard[2] == 'C') and (internalBoard[4] == 'B' or internalBoard[4] == 'C') and (internalBoard[6] == 'B' or internalBoard[6] == 'C'))
		{
			Positive++;
		}
		if ((internalBoard[2] == 'A' or internalBoard[2] == 'C') and (internalBoard[4] == 'A' or internalBoard[4] == 'C') and (internalBoard[6] == 'A' or internalBoard[6] == 'C'))
		{
			Negative++;
		}

		if ((internalBoard[0] == 'B' or internalBoard[0] == 'C') and (internalBoard[4] == 'B' or internalBoard[4] == 'C') and (internalBoard[8] == 'B' or internalBoard[8] == 'C'))
		{
			Positive++;
		}
		if ((internalBoard[0] == 'A' or internalBoard[0] == 'C') and (internalBoard[4] == 'A' or internalBoard[4] == 'C') and (internalBoard[8] == 'A' or internalBoard[8] == 'C'))
		{
			Negative++;
		}

		if ((internalBoard[0] == 'B' or internalBoard[0] == 'C') and (internalBoard[1] == 'B' or internalBoard[1] == 'C') and (internalBoard[2] == 'B' or internalBoard[2] == 'C'))
		{
			Positive++;
		}
		if ((internalBoard[0] == 'A' or internalBoard[0] == 'C') and (internalBoard[1] == 'A' or internalBoard[1] == 'C') and (internalBoard[2] == 'A' or internalBoard[2] == 'C'))
		{
			Negative++;
		}

		if ((internalBoard[3] == 'B' or internalBoard[3] == 'C') and (internalBoard[4] == 'B' or internalBoard[4] == 'C') and (internalBoard[5] == 'B' or internalBoard[5] == 'C'))
		{
			Positive++;
		}
		if ((internalBoard[3] == 'A' or internalBoard[3] == 'C') and (internalBoard[4] == 'A' or internalBoard[4] == 'C') and (internalBoard[5] == 'A' or internalBoard[5] == 'C'))
		{
			Negative++;
		}

		if ((internalBoard[6] == 'B' or internalBoard[6] == 'C') and (internalBoard[7] == 'B' or internalBoard[7] == 'C') and (internalBoard[8] == 'B' or internalBoard[8] == 'C'))
		{
			Positive++;
		}
		if ((internalBoard[6] == 'A' or internalBoard[6] == 'C') and (internalBoard[7] == 'A' or internalBoard[7] == 'C') and (internalBoard[8] == 'A' or internalBoard[8] == 'C'))
		{
			Negative++;
		}

		if ((internalBoard[0] == 'B' or internalBoard[0] == 'C') and (internalBoard[3] == 'B' or internalBoard[3] == 'C') and (internalBoard[6] == 'B' or internalBoard[6] == 'C'))
		{
			Positive++;
		}
		if ((internalBoard[0] == 'A' or internalBoard[0] == 'C') and (internalBoard[3] == 'A' or internalBoard[3] == 'C') and (internalBoard[6] == 'A' or internalBoard[6] == 'C'))
		{
			Negative++;
		}

		if ((internalBoard[1] == 'B' or internalBoard[1] == 'C') and (internalBoard[4] == 'B' or internalBoard[4] == 'C') and (internalBoard[7] == 'B' or internalBoard[7] == 'C'))
		{
			Positive++;
		}
		if ((internalBoard[1] == 'A' or internalBoard[1] == 'C') and (internalBoard[4] == 'A' or internalBoard[4] == 'C') and (internalBoard[7] == 'A' or internalBoard[7] == 'C'))
		{
			Negative++;
		}

		if ((internalBoard[2] == 'B' or internalBoard[2] == 'C') and (internalBoard[5] == 'B' or internalBoard[5] == 'C') and (internalBoard[8] == 'B' or internalBoard[8] == 'C'))
		{
			Positive++;
		}
		if ((internalBoard[2] == 'A' or internalBoard[2] == 'C') and (internalBoard[5] == 'A' or internalBoard[5] == 'C') and (internalBoard[8] == 'A' or internalBoard[8] == 'C'))
		{
			Negative++;
		}
		Possitive = Positive;
		Neggative = Negative;
		//cout << "Possitive: " << Positive << "- Negative: " << Negative<<" = "<<Positive-Negative << endl;
		return Positive-Negative;
	}
};

int getGoodMove(MiniMax *minimaxtree)
{
	if (minimaxtree->sons.size() <= 0)
	{
		//cout << "to push: " << minimaxtree->RValue << endl;
		return minimaxtree->RValue;
	}
	else
	{
		vector<int> values;
		for (size_t i = 0; i < minimaxtree->sons.size(); i++)
		{
			values.push_back(getGoodMove(minimaxtree->sons[i]));
		}
		if (minimaxtree->isMax == true and minimaxtree->isMin == false)
		{
			int bruh = *std::max_element(values.begin(), values.end());
			minimaxtree->MinimaxVal = bruh;
			printVector(values);
			cout << "Max answ: " << bruh << endl;
			return bruh;
		}
		if(minimaxtree->isMax == false and minimaxtree->isMin == true)
		{
			int bruh = *std::min_element(values.begin(), values.end());
			minimaxtree->MinimaxVal = bruh;
			printVector(values);
			cout << "Min answ: " << bruh << endl;
			return bruh;
		}
	}
}

int deepGlobal = 0;

void startBoard()
{
	for (size_t i = 0; i < 9; i++)
	{
		board.push_back('C');
	}
}

bool winnerChecker()
{
	if (board[2] == board[4] == board [6] and board[2] != 'C' and board[4] != 'C' and board[6] != 'C')
	{
		if (board[2] == 'A')
		{
			cout << "HUMAN WIN !!!" << endl;
			return true;
		}
		else
		{
			cout << "AI WIN !!!" << endl;
			return true;
		}
		
	}
	else if (board[0] == board[4] == board[8] and board[0] != 'C' and board[4] != 'C' and board[8] != 'C')
	{
		if (board[0] == 'A')
		{
			cout << "HUMAN WIN !!!" << endl;
			return true;
		}
		else
		{
			cout << "AI WIN !!!" << endl;
			return true;
		}
	}
	else if (board[0] == board[1] == board[2] and board[0] != 'C' and board[1] != 'C' and board[2] != 'C')
	{
		if (board[0] == 'A')
		{
			cout << "HUMAN WIN !!!" << endl;
			return true;
		}
		else
		{
			cout << "AI WIN !!!" << endl;
			return true;
		}
	}
	else if (board[3] == board[4] == board[5] and board[3] != 'C' and board[4] != 'C' and board[5] != 'C')
	{
		if (board[3] == 'A')
		{
			cout << "HUMAN WIN !!!" << endl;
			return true;
		}
		else
		{
			cout << "AI WIN !!!" << endl;
			return true;
		}
	}
	else if (board[6] == board[7] == board[8] and board[6] != 'C' and board[7] != 'C' and board[8] != 'C')
	{
		if (board[6] == 'A')
		{
			cout << "HUMAN WIN !!!" << endl;
			return true;
		}
		else
		{
			cout << "AI WIN !!!" << endl;
			return true;
		}
	}
	else if (board[0] == board[3] == board[6] and board[0] != 'C' and board[3] != 'C' and board[6] != 'C')
	{
		if (board[0] == 'A')
		{
			cout << "HUMAN WIN !!!" << endl;
			return true;
		}
		else
		{
			cout << "AI WIN !!!" << endl;
			return true;
		}
	}
	else if (board[1] == board[4] == board[7] and board[1] != 'C' and board[4] != 'C' and board[7] != 'C')
	{
		if (board[1] == 'A')
		{
			cout << "HUMAN WIN !!!" << endl;
			return true;
		}
		else
		{
			cout << "AI WIN !!!" << endl;
			return true;
		}
	}
	else if (board[2] == board[5] == board[8] and board[2] != 'C' and board[5] != 'C' and board[8] != 'C')
	{
		if (board[2] == 'A')
		{
			cout << "HUMAN WIN !!!" << endl;
			return true;
		}
		else
		{
			cout << "AI WIN !!!" << endl;
			return true;
		}
	}
	else
	{
		return false;
	}
}

int main()
{
	cout << "Insert deep tree: "; cin >> deepGlobal;
	bool winval = false;
	string test;
	startBoard();
	printboardchar(board);
	while (winval != true)
	{
		cout << "Write: AI if AI move or HUM if Human move" << endl;
		cin >> test;
		int GM;
		int TheChosenOne;
		if (test == "AI")
		{
			cout << "IA move now : " << endl;
			MiniMax* SKYNET;
			SKYNET = new MiniMax(deepGlobal, true, false, board, 'B');
			cout << "mimimax tree done..." << endl;
			GM = getGoodMove(SKYNET);
			cout << "GM: " << GM << endl;
			for (size_t i = 0; i < SKYNET->sons.size(); i++)
			{
				if (SKYNET->sons[i]->MinimaxVal == GM)
				{
					TheChosenOne = i;
				}
			}
			board = SKYNET->sons[TheChosenOne]->internalBoard;
			cout << "---------Gameplay---------" << endl;
			printboardchar(board);
			winval = winnerChecker();
		}
		else if (test == "HUM")
		{
			cout << "Write pos of move [0-8]" << endl;
			int val; cin >> val;
			board[val] = 'A';
			printboardchar(board);
			winval = winnerChecker();
		}
	}




	

}