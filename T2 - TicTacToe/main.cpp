#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <math.h>
#include "GL/glut.h"
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <queue>
#include <stack>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <cmath>
#define KEY_ESC 27
#define POS0 48
#define POS1 49
#define POS2 50
#define POS3 51
#define POS4 52
#define POS5 53
#define POS6 54
#define POS7 55
#define POS8 56
#define AIMOVE 65

using namespace std;

template <typename T, size_t N> const T* mybegin(const T(&a)[N]) { return a; }
template <typename T, size_t N> const T* myend(const T(&a)[N]) { return a + N; }

vector<char> board;

vector<int> getSameValuesInAVector(vector<int> values, int pattern) //not used
{
	vector<int> ans;
	for (size_t i = 0; i < values.size(); i++)
	{
		if (values[i]==pattern)
		{
			ans.push_back(i); //pushea el la posisicion en el vector
		}
	}
	return ans;
}

void OnMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		cout << "x: "<< x << endl;
		cout << "y: "<< y << endl;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		
	}
}

void OnMouseMotion(int x, int y)
{
	
}

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

void startBoard()
{
	for (size_t i = 0; i < 9; i++)
	{
		board.push_back('C');
	}
}

class MiniMax
{
public:
	vector<char>internalBoard;
	bool isMax = false;
	int deep;// Profundidad actual
	int RValue;// Valor que resulta de evaluar
	char Player; //Valor de jugador que le toca en ese nodo
	int MinimaxVal;
	vector <MiniMax*> sons;
	int Possitive;
	int Neggative;

	MiniMax(int _deep, bool _isMax, vector<char> Iboard, char _Player)
	{
		isMax = _isMax;
		deep = _deep;
		Player = _Player;
		internalBoard = Iboard;
		//printboardchar(internalBoard);
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
					MiniMax* NewSon = new MiniMax(deep - 1, !isMax, Tboard0, AuxChar);
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
		return Positive - Negative;
	}
};

int getGoodMove(MiniMax* minimaxtree)
{
	if (minimaxtree->sons.size() <= 0)
	{
		return minimaxtree->RValue;
	}
	else
	{
		vector<int> values;
		for (size_t i = 0; i < minimaxtree->sons.size(); i++)
		{
			values.push_back(getGoodMove(minimaxtree->sons[i]));
		}
		
		sort(values.begin(), values.end()); // menor a mayor
		//printVector(values);
		if (minimaxtree->isMax == true)
		{
			minimaxtree->MinimaxVal = values[values.size() - 1];
			return values[values.size() - 1];
		}
		if (minimaxtree->isMax == false)
		{
			minimaxtree->MinimaxVal = values[0];
			return values[0];
		}
	}
}

int deepGlobal = 0;

bool winnerChecker()
{
	bool wincondition = false;
	if (board[2] == 'A' and board[4] == 'A' and board[6] == 'A')
	{	
		cout << "HUMAN WIN !!!" << endl; wincondition = true; return true;
	}
	if (board[2] == 'B' and board[4] == 'B' and board[6] == 'B')
	{
		cout << "AI WIN !!!" << endl; wincondition = true; return true;
	}
	if (board[0] == 'A' and board[4] == 'A' and board[8] == 'A')
	{
		cout << "HUMAN WIN !!!" << endl; wincondition = true; return true;
	}
	if (board[0] == 'B' and board[4] == 'B' and board[8] == 'B')
	{
		cout << "AI WIN !!!" << endl; wincondition = true; return true;
	}
	if (board[0] == 'A' and board[1] == 'A' and board[2] == 'A')
	{
		cout << "HUMAN WIN !!!" << endl; wincondition = true; return true;
	}
	if (board[0] == 'B' and board[1] == 'B' and board[2] == 'B')
	{
		cout << "AI WIN !!!" << endl; wincondition = true; return true;
	}
	if (board[3] == 'A' and board[4] == 'A' and board[5] == 'A')
	{
		cout << "HUMAN WIN !!!" << endl; wincondition = true; return true;
	}
	if (board[3] == 'B' and board[4] == 'B' and board[5] == 'B')
	{
		cout << "AI WIN !!!" << endl; wincondition = true; return true;
	}
	if (board[6] == 'A' and board[7] == 'A' and board[8] == 'A')
	{
		cout << "HUMAN WIN !!!" << endl; wincondition = true; return true;
	}
	if (board[6] == 'B' and board[7] == 'B' and board[8] == 'B')
	{
		cout << "AI WIN !!!" << endl; wincondition = true; return true;
	}
	if (board[0] == 'A' and board[3] == 'A' and board[6] == 'A')
	{
		cout << "HUMAN WIN !!!" << endl; wincondition = true; return true;
	}
	if (board[0] == 'B' and board[3] == 'B' and board[6] == 'B')
	{
		cout << "AI WIN !!!" << endl; wincondition = true; return true;
	}
	if (board[1] == 'A' and board[4] == 'A' and board[7] == 'A')
	{
		cout << "HUMAN WIN !!!" << endl; wincondition = true; return true;
	}
	if (board[1] == 'B' and board[4] == 'B' and board[7] == 'B')
	{
		cout << "AI WIN !!!" << endl; wincondition = true; return true;
	}
	if (board[2] == 'A' and board[5] == 'A' and board[8] == 'A')
	{
		cout << "HUMAN WIN !!!" << endl; wincondition = true; return true;
	}
	if (board[2] == 'B' and board[5] == 'B' and board[8] == 'B')
	{
		cout << "AI WIN !!!" << endl; wincondition = true; return true;
	}
	if (board[0] != 'C' and board[1] != 'C' and board[2] != 'C' and 
		board[3] != 'C' and board[4] != 'C' and board[5] != 'C' and 
		board[6] != 'C' and board[7] != 'C' and board[8] != 'C' and 
		wincondition == false)
	{
		cout << "TIEEEEEE !!!!!!" << endl;
		return true;
	}
	else
	{
		return false;
	}
}

void create_Square(double centerX, double centerY, double longitude)
{
	glBegin(GL_LINE_LOOP);
	glColor3d(0.000, 1.000, 1.000);
	glVertex2f(centerX - (longitude / 2), centerY + (longitude / 2));
	glVertex2f(centerX + (longitude / 2), centerY + (longitude / 2));
	glVertex2f(centerX + (longitude / 2), centerY - (longitude / 2));
	glVertex2f(centerX - (longitude / 2), centerY - (longitude / 2));
	glVertex2f(centerX - (longitude / 2), centerY + (longitude / 2));
	glEnd();
}

void create_circle(double centerX, double centerY, double radius) {
	glBegin(GL_LINE_LOOP);
	glColor3d(0.855, 0.439, 0.839);
	for (int i = 0; i < 100; i++)
	{
		double theta = 2.0 * 3.1415926 * double(i) / 100.0;
		double x = radius * cosf(theta);
		double y = radius * sinf(theta);
		glVertex2f(x + centerX, y + centerY);
	}
	glEnd();
}

//pos0 = 30,70
//pos1 = 50,70
//pos2 = 70,70
//pos3 = 30,50
//pos4 = 50,50
//pos5 = 70,50
//pos6 = 30,30
//pos7 = 50,30
//pos8 = 70,30

void printBoard()
{
	glBegin(GL_LINES);

	glColor3d(1, 1, 1);
	glVertex3d(20, 40, 0);
	glVertex3d(80, 40, 0);

	glColor3d(1, 1, 1);
	glVertex3d(20, 60, 0);
	glVertex3d(80, 60, 0);

	glColor3d(1, 1, 1);
	glVertex3d(40, 20, 0);
	glVertex3d(40, 80, 0);

	glColor3d(1, 1, 1);
	glVertex3d(60, 20, 0);
	glVertex3d(60, 80, 0);

	glEnd();
	for (size_t i = 0; i < board.size(); i++)
	{
		if (board[i] != 'C')
		{
			if (board[i] == 'A')
			{
				if (i == 0)
				{
					create_Square(30, 70, 4);
				}
				if (i == 1)
				{
					create_Square(50, 70, 4);
				}
				if (i == 2)
				{
					create_Square(70, 70, 4);
				}
				if (i == 3)
				{
					create_Square(30, 50, 4);
				}
				if (i == 4)
				{
					create_Square(50, 50, 4);
				}
				if (i == 5)
				{
					create_Square(70, 50, 4);
				}
				if (i == 6)
				{
					create_Square(30, 30, 4);
				}
				if (i == 7)
				{
					create_Square(50, 30, 4);
				}
				if (i == 8)
				{
					create_Square(70, 30, 4);
				}
			}
			else
			{
				if (i == 0)
				{
					create_circle(30, 70, 2);
				}
				if (i == 1)
				{
					create_circle(50, 70, 2);
				}
				if (i == 2)
				{
					create_circle(70, 70, 2);
				}
				if (i == 3)
				{
					create_circle(30, 50, 2);
				}
				if (i == 4)
				{
					create_circle(50, 50, 2);
				}
				if (i == 5)
				{
					create_circle(70, 50, 2);
				}
				if (i == 6)
				{
					create_circle(30, 30, 2);
				}
				if (i == 7)
				{
					create_circle(50, 30, 2);
				}
				if (i == 8)
				{
					create_circle(70, 30, 2);
				}
			}
		}
	}
}

void displayGizmo()
{
	glBegin(GL_LINES);
	glColor3d(255, 0, 0);//x
	glVertex3d(0, 0, 0);
	glVertex3d(100, 0, 0);
	glColor3d(0, 255, 0);//y
	glVertex3d(0, 0, 0);
	glVertex3d(0, 100, 0);
	glColor3d(0, 0, 255);//z
	glVertex3d(0, 0, -30);
	glVertex3d(0, 0, 30);
	glEnd();
}

void glPaint(void) {

	//El fondo de la escena al color initial
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();

	printBoard();
	
	//dibuja el gizmo
	//displayGizmo();

	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-20.0, 120.0, -20.0, 120.0, -1.0, 1.0);
	// todas la informaciones previas se aplican al la matrice del ModelView
	glMatrixMode(GL_MODELVIEW);
}

void printboard() 
{
	for (size_t i = 0; i < board.size(); i++)
	{
		cout << board[i] << "-";
	}
	cout << endl;
}

bool winval = false;

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) 
	{
	case POS0:
		board[0] = 'A';
		printboard();
		printboardchar(board);
		if (winnerChecker() == true)
		{
			cout << "--------------------------END--------------------------" << endl;
		}
		break;
	case POS1:
		board[1] = 'A';
		printboard();
		printboardchar(board);
		if (winnerChecker() == true)
		{
			cout << "--------------------------END--------------------------" << endl;
		}
		break;
	case POS2:
		board[2] = 'A';
		printboard();
		printboardchar(board);
		if (winnerChecker() == true)
		{
			cout << "--------------------------END--------------------------" << endl;
		}
		break;
	case POS3:
		board[3] = 'A';
		printboard();
		printboardchar(board);
		if (winnerChecker() == true)
		{
			cout << "--------------------------END--------------------------" << endl;
		}
		break;
	case POS4:
		board[4] = 'A';
		printboard();
		printboardchar(board);
		if (winnerChecker() == true)
		{
			cout << "--------------------------END--------------------------" << endl;
		}
		break;
	case POS5:
		board[5] = 'A';
		printboard();
		printboardchar(board);
		if (winnerChecker() == true)
		{
			cout << "--------------------------END--------------------------" << endl;
		}
		break;
	case POS6:
		board[6] = 'A';
		printboard();
		printboardchar(board);
		if (winnerChecker() == true)
		{
			cout << "--------------------------END--------------------------" << endl;
		}
		break;
	case POS7:
		board[7] = 'A';
		printboard();
		printboardchar(board);
		if (winnerChecker() == true)
		{
			cout << "--------------------------END--------------------------" << endl;
		}
		break;
	case POS8:
		board[8] = 'A';
		printboard();
		printboardchar(board);
		if (winnerChecker() == true)
		{
			cout << "--------------------------END--------------------------" << endl;
		}
		break;
	case AIMOVE:
		int GM;
		int TheChosenOne;
		cout << "IA move now : " << endl;
		MiniMax* SKYNET;
		SKYNET = new MiniMax(deepGlobal, true, board, 'B');
		cout << "mimimax tree done..." << endl;
		GM = getGoodMove(SKYNET);
		vector<int> posibles;
		for (size_t i = 0; i < SKYNET->sons.size(); i++)
		{
			if (SKYNET->sons[i]->MinimaxVal == GM)
			{
				posibles.push_back(i); //candidatos con el valor mismo valor GM
			}
		}
		int randumm = rand() % 100;
		board = SKYNET->sons[ posibles[randumm % posibles.size()] ]->internalBoard;;
		printboard();
		printboardchar(board);
		if (winnerChecker() == true)
		{
			cout << "--------------------------END--------------------------" << endl;
		}
		delete SKYNET;
		break;
	}

}

void idle() 
{
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	cout << "Insert deep tree: "; cin >> deepGlobal;
	winval = false;
	startBoard();
	printboard();
	printboardchar(board);
	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800); //tamaño de la ventana
	glutInitWindowPosition(0, 0); //posicion de la ventana
	glutCreateWindow("SKYNET"); //titulo de la ventana
	init_GL(); //funcion de inicializacion de OpenGL


	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);
	glutMainLoop(); //bucle de rendering

	return 0;
}