#include <vector>
#include <GL/glut.h>
#include <math.h>
#include "grapho.h"

using namespace std;

void DrawGraph() {
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(3);
	glBegin(GL_POINTS);
	glColor3d(255, 0, 0);
	for (unsigned i = 0; i<points.size(); i++)
		glVertex2d(points[i].first, points[i].second);
	glEnd();
	glFlush();
	
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	//glVertex2f(-0.3, 0.2);	glVertex2f(0.4, 0.3);
	for (unsigned i = 0; i < edges.size(); i++) {
		glVertex2d(edges[i].first, edges[i].second);
		glVertex2d(edges[i].first, edges[i].second);
	}
	glEnd();
	glFlush();
}

void ini() {
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-2,2,-2,2);
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hello!");
	ini();
	glutDisplayFunc(DrawGraph);
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