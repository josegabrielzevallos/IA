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
#define KEY_ESC 27
using namespace std;

class Point;

class Edge 
{
public:
	Edge(Point* a, Point* b) 
	{
		VertexA = a;
		VertexB = b;
	};
	Point* VertexA;
	Point* VertexB;
};

class Point 
{
public:
	vector<Edge*>Edges;
	float x;
	float y;
	bool visited;
	bool added;
	float cost;
	Point()
	{
		x = 0;
		y = 0;
		visited = false;
		added = false;
	}
	Point(float x_, float y_)
	{
		x = x_;
		y = y_;
		visited = false;
		added = false;
	}
	Point operator =  (const Point& P) 
	{
		this->x = P.x;
		this->y = P.y;
		return *this;
	}
	bool operator ==  (const Point& P) {
		if (this->x == P.x && this->y == P.y) {
			return true;
		}
		return false;
	}
};

float Euclidean_distance(Point *P, Point *N)
{
	return sqrt(pow(abs(N->x - P->x), 2) + pow(abs(N->y - P->y), 2));
}
float Euclidean_distance(Point P, Point N)
{
	return sqrt(pow(abs(N.x - P.x), 2) + pow(abs(N.y - P.y), 2));
}

vector<Point> Puntos;
int numberPointsT = 0;

void createPoints()
{
	for (int i = 0; i < numberPointsT; i++)
	{
		float xtemp = rand() % 101;
		float ytemp = rand() % 101;
		Puntos.push_back(Point(xtemp, ytemp));
	}
}

void drawPoints()
{
	for (size_t i = 0; i < numberPointsT; i++)
	{
		glPointSize(3.5);
		glBegin(GL_POINTS);
		glColor3d(250, 0, 0);
		glVertex3f(Puntos[i].x, Puntos[i].y, 0.0);
		glEnd();
	}
}

vector<Edge*> EdgesGlob;

void getEdgesKNN()
{
	float minDist = 10;
	for (size_t i = 0; i < Puntos.size(); i++)
	{
		while (Puntos[i].Edges.size() < 5)
		{
			for (size_t j = 0; j < Puntos.size(); j++)
			{
				float ED = Euclidean_distance(&Puntos[i], &Puntos[j]);
				if (ED < minDist && ED != 0 && Puntos[i].Edges.size() < 5 && Puntos[j].Edges.size() < 5)
				{

					Edge* nuevo1 = new Edge(&Puntos[i], &Puntos[j]);
					Edge* nuevo2 = new Edge(&Puntos[j], &Puntos[i]);
					
					Puntos[i].Edges.push_back(nuevo1);
					Puntos[j].Edges.push_back(nuevo2);
					EdgesGlob.push_back(nuevo1);
					EdgesGlob.push_back(nuevo2);
				}
			}
			if (Puntos[i].Edges.size() < 5)
			{
				cout << "test" << endl;
				minDist = minDist + 5;
			}
		}
	}
}

void drawEDGES()
{
	for (size_t i = 0; i < EdgesGlob.size(); i++)
	{
		glBegin(GL_LINES);
		glColor3d(0, 1, 0);
		glVertex3d(EdgesGlob[i]->VertexA->x, EdgesGlob[i]->VertexA->y, 0);
		glVertex3d(EdgesGlob[i]->VertexB->x, EdgesGlob[i]->VertexB->y, 0);
		glEnd();
	}
}

float printPath(vector<Point*> Path, Point *A, Point *B)
{
	float answ = 0;
	for (size_t i = 0; i < Path.size(); i++)
	{
		if (i+1 != Path.size())
		{
			glBegin(GL_LINES);
			glColor3d(1.00000f, 0.20000f, 0.80000f);
			glVertex3d(Path[i]->x, Path[i]->y, 0);
			glVertex3d(Path[i + 1]->x, Path[i + 1]->y, 0);
			glEnd();
			answ = answ + Euclidean_distance(Path[i],Path[i+1]);
		}
	}
	cout << "Distancia Recorrida: " << answ << endl;
	return answ;
}

void drawPointsFromPath(vector<Point*> Path, Point* A, Point* B)
{
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3d(0.000, 0.980, 0.604);
	glVertex3f(A->x, A->y, 0.0);
	glEnd();
	for (size_t i = 0; i < Path.size(); i++)
	{
		glPointSize(5.0);
		glBegin(GL_POINTS);
		glColor3d(0.000, 0.980, 0.604);
		glVertex3f(Path[i]->x, Path[i]->y, 0.0);
		glEnd();
	}
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3d(0.000, 0.980, 0.604);
	glVertex3f(B->x, B->y, 0.0);
	glEnd();
}

class BusquedaCiegaP 
{
public:
	stack<Point*>_Stack;
	vector<Point*> Path;
	BusquedaCiegaP() {}
	bool Run(Point& P, Point& N) 
	{
		_Stack.push(&P);
		Point* V;
		while (!_Stack.empty())
		{
			V = _Stack.top();
			V->visited = true;
			Path.push_back(V);
			_Stack.pop();
			if (*V == N) 
			{
				return true;
			}
			else 
			{
				for (unsigned int i = 0; i < V->Edges.size(); i++) 
				{
					if (V->Edges[i]->VertexB->visited == false &&
						V->Edges[i]->VertexB->added == false) 
					{
						_Stack.push(V->Edges[i]->VertexB);
						V->Edges[i]->VertexB->added = true;
					}
				}

			}
		}
		return false;
	}
};

class AStar 
{
public:
	struct compare
	{
		bool operator()(Point*& P, Point*& Q)
		{
			return P->cost > Q->cost;
		}
	};
	priority_queue<Point*, vector<Point* >, compare > PrioQu;
	vector<Point*> Path;
	AStar(){}
	bool Run(Point& StartPoint, Point& FinalPoint) 
	{
		float G, H;
		Point* WorkPoint;
		PrioQu.push(&StartPoint);
		while (!PrioQu.empty())
		{
			WorkPoint = PrioQu.top();
			WorkPoint->visited = true;
			Path.push_back(WorkPoint);
			PrioQu = priority_queue<Point*, vector<Point* >, compare>();
			if (*WorkPoint == FinalPoint)
			{
				return true;
			}
			else 
			{
				for (unsigned int i = 0; i < WorkPoint->Edges.size(); i++)
				{
					if (WorkPoint->Edges[i]->VertexB->visited == false)
					{
						G = Euclidean_distance(*WorkPoint->Edges[i]->VertexA, *WorkPoint->Edges[i]->VertexB);
						H = Euclidean_distance(*WorkPoint->Edges[i]->VertexB, FinalPoint);
						WorkPoint->Edges[i]->VertexB->cost = G + H;
						PrioQu.push(WorkPoint->Edges[i]->VertexB);
					}
				}
			}
		}
		return false;
	}
};

BusquedaCiegaP IA1;
AStar IA2;

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

Point* p1;
Point* p2;

//funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();

	drawEDGES();
	drawPoints();
	//printPath(IA1.Path, p1, p2);
	printPath(IA2.Path, p1, p2);
	//drawPointsFromPath(IA1.Path, p1, p2);
	drawPointsFromPath(IA2.Path, p1, p2);

	glPointSize(8.0);
	glBegin(GL_POINTS);
	glColor3d(1.000, 0.894, 0.882);
	glVertex3f(p1->x, p1->y, 0.0);
	glVertex3f(p2->x, p2->y, 0.0);
	glEnd();

	//dibuja el gizmo
	displayGizmo();

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

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;

	default:
		break;
	}

}
//
//el programa principal
//

int getFar_Right_bot(vector<Point> Puntes)
{
	int pos = 0;
	float x_max = Puntes[0].x;
	float y_max = Puntes[0].y;
	for (size_t i = 0; i < Puntes.size(); i++)
	{
		if (Puntes[i].x > x_max && Puntes[i].y < y_max)
		{
			x_max = Puntes[i].x;
			y_max = Puntes[i].y;
			pos = i;
		}
	}
	return pos;
}

int getFar_Left_top(vector<Point> Puntes)
{
	int pos = 0;
	float x_max = Puntes[0].x;
	float y_max = Puntes[0].y;
	for (size_t i = 0; i < Puntes.size(); i++)
	{
		if (Puntes[i].x < x_max&& Puntes[i].y > y_max)
		{
			x_max = Puntes[i].x;
			y_max = Puntes[i].y;
			pos = i;
		}
	}
	return pos;
}

int main(int argc, char** argv) {
	numberPointsT = 200;
	createPoints();
	getEdgesKNN();
	
	p1 = &Puntos[getFar_Left_top(Puntos)];
	p2 = &Puntos[getFar_Right_bot(Puntos)];

	//IA1.Run(*p1, *p2);
	IA2.Run(*p1, *p2);

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

	glutMainLoop(); //bucle de rendering

	return 0;
}