//#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <math.h>
#include "grapho.h"
//#include "searches.h"

using namespace std;

#define KEY_ESC 27
#define KEY_X 120
#define KEY_Y 121
#define KEY_Z 122

void ini() {
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-20, 20, -20, 20);
	glClearColor(0.0, 1.0, 0.0, 0.0);
}

void DrawGraph() {
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(3);
	glBegin(GL_POINTS);
	glColor3d(255, 0, 0);
	for (unsigned i = 0; i<Dpoints.size(); i++)
		glVertex2d(Dpoints[i].first, Dpoints[i].second);
		//glVertex2d(0.5, 0.5);
	glEnd();
	glFlush();
	
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	//glVertex2f(-0.3, 0.2);	glVertex2f(0.4, 0.3);
	for (unsigned i = 0; i < Dedges.size(); i++) {
		glVertex2d(Dedges[i].first.first, Dedges[i].first.second);
		glVertex2d(Dedges[i].second.first, Dedges[i].second.second);
	}
	glEnd();
	glFlush();
}
/*/
GLvoid window_key(unsigned char key, int x, int y)
{
	switch (key) {
	case KEY_ESC:
		exit(1);
		break;
	case KEY_X:
		DFS_ORG();
		break;
	case KEY_Y:
		hill_climbing(grap);
		break;
	case KEY_Z:
		a_asterisco(grap);
		break;
	default:
		printf("Pressing %d doesn't do anything.\n", key);
		break;
	}
}
*/
int main(int argc, char** argv)
{
	int c, r, d;
	r = 1000; c = 1000; d = 10;
	Cgrafo <float, float> grap(r, c, d);
	//grap.createVertex();
	//grap.createEdges();
	//grap.collectToDraw();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(c,r);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Hello!");
	ini();
	//cout << "hiiiii"<<endl;
	//glutDisplayFunc(DrawGraph);
	//cout << "hiiiii" << endl;
	//glutDisplayFunc(&window_key);
	glutMainLoop();
	return 0;
}

/*
#include <GL/glut.h>

void displayMe(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glVertex3f(0.5, 0.0, 0.5);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(0.0, 0.5, 0.0);
	glVertex3f(0.0, 0.0, 0.5);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hello world!");
	glutDisplayFunc(displayMe);
	glutMainLoop();
	return 0;
}
*/