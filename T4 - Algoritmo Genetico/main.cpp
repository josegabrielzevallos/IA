#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <algorithm>    // std::random_shuffle
#include <math.h>
#include "GL/glut.h"
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <queue>
#include <stack>
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#define KEY_ESC 27
#define KEY_G 71
#define KEY_H 72
using namespace std;

class Point
{
public:
	float x;
	float y;
	bool visited;
	Point()
	{
		x = 0;
		y = 0;
		visited = false;
	}
	Point(float x_, float y_)
	{
		x = x_;
		y = y_;
		visited = false;
	}
};



float Euclidean_distance(Point P, Point N)
{
	return sqrt(pow(abs(N.x - P.x), 2) + pow(abs(N.y - P.y), 2));
}

vector<Point> TSMCountries;
int numberTSMCountries = 0;

//genera las ciudades globales
void createTSMCountries()
{
	for (int i = 0; i < numberTSMCountries; i++)
	{
		float xtemp = rand() % 101;
		float ytemp = rand() % 101;
		TSMCountries.push_back(Point(xtemp, ytemp));
	}
}

//dibuja las ciudades globales
void drawTSMCountries()
{
	for (size_t i = 0; i < numberTSMCountries; i++)
	{
		glPointSize(1);
		glBegin(GL_POINTS);
		glColor3d(250, 0, 0);
		glVertex3f(TSMCountries[i].x, TSMCountries[i].y, 0.0);
		glEnd();
	}
}

vector<Point> TSMcountriesPrincipal;
int munofpnts = 0;
int poblationNumber = 0;

//dibuja los puntos a tomar en el TSM
void drawTSMCountriesPrincipal()
{
	for (size_t i = 0; i < munofpnts; i++)
	{
		glPointSize(4);
		glBegin(GL_POINTS);
		glColor3d(1.000, 0.271, 0.000);
		glVertex3f(TSMcountriesPrincipal[i].x, TSMcountriesPrincipal[i].y, 0.0);
		glEnd();
	}
}

bool isInTMScountries(Point ToFind) //busca si ya esta en la lista del TSMcountriesPrincipal
{
	for (size_t i = 0; i < TSMcountriesPrincipal.size(); i++)
	{
		if (ToFind.x == TSMcountriesPrincipal[i].x and ToFind.y == TSMcountriesPrincipal[i].y)
		{
			return true;
		}
	}
	return false;
}

void getTenRandomCountries()
{
	for (int i = 0; i < munofpnts; i++)
	{
		int randomico = rand() % TSMCountries.size();
		if (isInTMScountries(TSMCountries[randomico]) == false)
		{
			TSMcountriesPrincipal.push_back(TSMCountries[randomico]);
		}
		else
		{
			i--;
		}
	}
}

//dibuja los caminos entre las ciudades entre el TSM
void drawEdgesFromPrincipal()
{
	for (size_t i = 0; i < TSMcountriesPrincipal.size(); i++)
	{
		for (size_t j = 0; j < TSMcountriesPrincipal.size(); j++)
		{
			glBegin(GL_LINES);
			glColor3d(1.000, 1.000, 0.000);
			glVertex3d(TSMcountriesPrincipal[i].x, TSMcountriesPrincipal[i].y, 0);
			glVertex3d(TSMcountriesPrincipal[j].x, TSMcountriesPrincipal[j].y, 0);
			glEnd();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////

vector<vector<Point>> Poblacion;
vector<Point> BestoPath;

void printPoint(Point Pnt)
{
	cout << "(" << Pnt.x << "," << Pnt.y << ")";
}
	
void printPath(vector<Point> path)
{
	for (size_t i = 0; i < path.size(); i++)
	{
		printPoint(path[i]); cout << " - ";
	}
	cout << endl;
}

void printPoblation(vector<vector<Point>> Pobla)
{
	for (size_t i = 0; i < Pobla.size(); i++)
	{
		for (size_t j = 0; j < Pobla[i].size(); j++)
		{
			printPoint(Pobla[i][j]); cout << " - ";
		}
		cout << endl;
	}
	cout << endl;
}

vector<vector<Point>> genRandomInicialPoblation()
{
	vector<vector<Point>> anw;
	vector<Point> tempo = TSMcountriesPrincipal;
	for (size_t i = 0; i < poblationNumber; i++)
	{
		random_shuffle(tempo.begin()+1, tempo.end());
		anw.push_back(tempo);
	}
	return anw;
}

float CalculateAptitude(vector<Point> Ruta)
{
	float anw = 0.0;
	for (size_t i = 0; i < Ruta.size() - 1; i++)
	{
		anw = anw + Euclidean_distance(Ruta[i], Ruta[i + 1]);
	}
	anw = anw + Euclidean_distance(Ruta[Ruta.size() - 1], Ruta[0]);
	return anw;
}

vector<int> genRandomPair(int maxVal)
{
	vector<int> PseudoPair;
	PseudoPair.push_back(rand() % (maxVal + 1)); //de 0 a maxval, if maxval = 10 then 0 - 11 in rand 0 - 10
	PseudoPair.push_back(rand() % (maxVal + 1));
	while (PseudoPair[0] == PseudoPair[1])
	{
		PseudoPair[1] = rand() % (maxVal + 1);
	}
	return PseudoPair;
}

bool findInPath(vector<Point> son, Point toF)
{
	for (size_t i = 0; i < son.size(); i++)
	{
		if (son[i].x == toF.x and son[i].y == toF.y)
		{
			return true;
		}
	}
	return false;
}

vector<Point> OXCrossover(vector<int> PsPair, vector<vector<Point>> winners)
{
	// se usaran substring de los padres de tamaño 3
	cout << "Pair: " << PsPair[0] << "-" << PsPair[1] << endl;
	int max = munofpnts - 2; //numero de ciudades maxima - 2
	int min = 2; // posicion 0 - (1) para
	int randNum = rand() % (max - min + 1) + min; //max min
	vector<int> subpath = { randNum - 1, randNum, randNum + 1 };
	cout << "subpath del camino: " << subpath[0] << "-" << subpath[1] << "-" << subpath[2] << endl;
	vector<Point> Parent1 = winners[PsPair[0]];
	//cout << "Parent1: ";
	//printPath(Parent1);
	vector<Point> Parent2 = winners[PsPair[1]];
	//cout << "Parent2: ";
	//printPath(Parent2);
	vector<Point> Son(munofpnts,Point()); //lena vector con puntos 0,0
	//example
	//subpath : 3 4 5
	//Parent 1: 8 4 7 (3 6 2) 5 1 9 0
	//Parent 2: 0 1 2 3 4 5 6 7 8 9
	//son :     $ $ $ $ $ $ $ $ $ $
	for (size_t i = 0; i < subpath.size(); i++)
	{
		Son[subpath[i]] = Parent1[subpath[i]];
	}
	//cout << "default Son: ";
	//printPath(Son);
	//son : $ $ $ 3 6 2 $ $ $ $
	vector<Point> temporal;
	for (size_t i = 0; i < Parent2.size(); i++)
	{
		if (findInPath(Son, Parent2[i]) == false)
		{
			temporal.push_back(Parent2[i]);
		}
	}
	int ind = 0;
	for (size_t i = 0; i < Son.size(); i++)
	{
		if (Son[i].x == 0 and Son[i].y == 0)
		{
			Son[i] = temporal[ind];
			ind++;
		}
	}
	//cout << "final Son: ";
	//printPath(Son);
	//son : 0 1 4 3 6 2 5 7 8 9
	return Son;
}

vector<vector<Point>> TournamentSelectionAndCrossing(vector<vector<Point>> poblationX)
{
	cout << "Empezara el torneo ..." << endl;
	vector<vector<Point>> Result;
	vector<int> myvector;
	for (int i = 0; i < munofpnts; ++i) myvector.push_back(i); // 0 1 2 3 4 5 6 7 8 ... munofpnts
	//recomendado un numero par porq estos caminos se enfrentara a otro, recomendado numero par de poblacion
	random_shuffle(myvector.begin(), myvector.end());
	///////////////////////////////////////////////////
	cout << "Posiciones de los caminos shuffleados :";
	for (size_t i = 0; i < myvector.size(); i++)
	{
		cout << myvector[i] << ", ";
	}
	cout << endl;
	///////////////////////////////////////////////////
	int a = 0;
	int b = 1;
	for (int i = 0; i < (poblationX.size()) / 2; i++)
	{
		if (CalculateAptitude(poblationX[myvector[a]]) < CalculateAptitude(poblationX[myvector[b]]))
		{
			Result.push_back(poblationX[myvector[a]]);
		}
		else
		{
			Result.push_back(poblationX[myvector[b]]);
		}
		a = (a + 2);
		b = (b + 2);

	}
	cout << "Ganadores: " << endl;
	printPoblation(Result);
	cout << "Empezara el Crossing ..." << endl;
	
	//vector Result contiene el resultado de la seleccion por torneo
	int poblacionFaltante = poblationX.size() - Result.size();
	//cout << "poblacionFaltante: " << poblacionFaltante << endl;
	int poblacionFaltanteEstatica = poblationX.size() - Result.size();
	//cout << "poblacionFaltanteEstatica: " << poblacionFaltanteEstatica << endl;
	while (poblacionFaltante != poblationX.size())
	{
		vector<int> pseudoPair = genRandomPair(poblacionFaltanteEstatica-1);
		vector<Point> newSon = OXCrossover(pseudoPair, Result);
		//Mutacion aleatoria
		if ((rand() % 2 + 1) % 2 == 0)
		{
			vector<int>RndPair = genRandomPair(munofpnts-1);
			Point temporal = newSon[RndPair[1]];
			newSon[RndPair[1]] = newSon[RndPair[0]];
			newSon[RndPair[0]] = temporal;
		}
		Result.push_back(newSon);
		poblacionFaltante++;
		//cout << "poblacion añadida <<<<<<<<<<<<<<<" << endl;
		//printPoblation(Result);
	}
	return Result;
}

vector<vector<Point>> geneticAlgorithm(vector<vector<Point>> P)
{
	vector<pair<int, float>> PositionOfAPoblacion_and_Aptitude;
	for (size_t i = 0; i < P.size(); i++)
	{
		PositionOfAPoblacion_and_Aptitude.push_back(pair<int, float>(i, CalculateAptitude(P[i])));
	}
	float minval = 9999999.9;
	float media = 0.0;
	for (int i = 0; i < PositionOfAPoblacion_and_Aptitude.size(); i++)
	{
		if (PositionOfAPoblacion_and_Aptitude[i].second < minval)
		{
			minval = PositionOfAPoblacion_and_Aptitude[i].second;
		}
		media = media + PositionOfAPoblacion_and_Aptitude[i].second;
	}
	media = media / PositionOfAPoblacion_and_Aptitude.size();
	cout << "Min val finded : " << minval << endl;
	cout << "Media val: " << media << endl;
	//printPoblation(P);

	cout << "Empezara el Torneo para la seleccion y el cruzamiento ..." << endl;
	vector<vector<Point>> NuevaPoblacion;
	NuevaPoblacion = TournamentSelectionAndCrossing(P);
	return NuevaPoblacion;
}

vector<Point> BestPath(vector<vector<Point>> pobla)
{
	vector<pair<int, float>> PositionOfAPoblacion_and_Aptitude;
	for (size_t i = 0; i < pobla.size(); i++)
	{
		PositionOfAPoblacion_and_Aptitude.push_back(pair<int, float>(i, CalculateAptitude(pobla[i])));
	}
	float minval = 9999999.9;
	float media = 0.0;
	for (int i = 0; i < PositionOfAPoblacion_and_Aptitude.size(); i++)
	{
		if (PositionOfAPoblacion_and_Aptitude[i].second < minval)
		{
			minval = PositionOfAPoblacion_and_Aptitude[i].second;
		}
		media = media + PositionOfAPoblacion_and_Aptitude[i].second;
	}
	media = media / PositionOfAPoblacion_and_Aptitude.size();
	//cout << "Min val finded : " << minval << endl;
	//cout << "Media val: " << media << endl;
	int positoprint = 0;
	for (size_t i = 0; i < PositionOfAPoblacion_and_Aptitude.size(); i++)
	{
		if (PositionOfAPoblacion_and_Aptitude[i].second == minval)
		{
			positoprint = PositionOfAPoblacion_and_Aptitude[i].first;
		}
	}
	cout << "mejor camino de la generacion: "; printPath(pobla[positoprint]);
	BestoPath = pobla[positoprint];
	return pobla[positoprint];
}

void drawBestoPath()
{
	for (size_t i = 0; i < BestoPath.size()-1; i++)
	{
		glBegin(GL_LINES);
		glColor3d(1.000, 0.000, 0.000);
		glVertex3d(BestoPath[i].x, BestoPath[i].y, 0);
		//cout << "from:"; printPoint(BestoPath[i]);
		glVertex3d(BestoPath[i + 1].x, BestoPath[i + 1].y, 0);
		//cout << " to: "; printPoint(BestoPath[i + 1]); cout << endl;
		glEnd();
	}
	glBegin(GL_LINES);
	glColor3d(1.000, 0.000, 0.000);
	glVertex3d(BestoPath[BestoPath.size() - 1].x, BestoPath[BestoPath.size() - 1].y, 0);
	//cout << "from:"; printPoint(BestoPath[BestoPath.size() - 1]);
	glVertex3d(BestoPath[0].x, BestoPath[0].y, 0);
	//cout << " to: "; printPoint(BestoPath[0]); cout << endl;
	//cout << "/*/" << endl;
	glEnd();
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

//funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();

	drawTSMCountries();
	drawTSMCountriesPrincipal();
	drawBestoPath();

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
GLvoid window_redraw(GLsizei width, GLsizei height) 
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//drawBestoPath();
	glOrtho(-20.0, 120.0, -20.0, 120.0, -1.0, 1.0);
	// todas la informaciones previas se aplican al la matrice del ModelView
	glMatrixMode(GL_MODELVIEW);
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;
	case KEY_G:
		Poblacion = geneticAlgorithm(Poblacion);
		BestoPath = BestPath(Poblacion);
		break;

	}

}
//
//el programa principal
//


int main(int argc, char** argv)
{
	srand(time(NULL));
	numberTSMCountries = 100;
	cout << "numero de ciudades: ";
	cin >> munofpnts;

	cout << "numero de caminos en una generacion: ";
	cin >> poblationNumber;

	createTSMCountries();
	getTenRandomCountries();

	Poblacion = genRandomInicialPoblation();
	Poblacion = geneticAlgorithm(Poblacion);
	BestoPath = BestPath(Poblacion);

	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800); //tamaño de la ventana
	glutInitWindowPosition(0, 0); //posicion de la ventana
	glutCreateWindow("Genetic Algorithm"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);

	glutMainLoop(); //bucle de rendering

	return 0;
}
