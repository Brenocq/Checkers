#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

#include "Classes/board.h"

//----- Parameters -----//
int windowWidth = 800;
int windowHeight = 800;
int screenWidth = 1920;
int screenHeight = 1080;

//----- Functions -----//
void draw();
void timer(int);
void mouse(int button, int state, int x, int y);

//----- Objects -----//
Board board;

//----- Main -----//
int main(int argc, char** argv)
{
 	//----- Create window -----//
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((screenWidth/2)-(windowWidth/2), (screenHeight/2)-(windowHeight/2));
	glutCreateWindow("Dame Game");
	glClearColor(1,1,1, 1.0);// Clear window
	glutMouseFunc(mouse);// Allow to add points
	glutDisplayFunc(draw);// Set the draw function
	glutMainLoop();
                
	return 0;
}

void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  board.draw();
  glutSwapBuffers();
}
void timer(int)
{
 	glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
}
void mouse(int button, int state, int x, int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && x>0 && y>0)
	{
		int posX = x/(windowWidth/board.getSize());
		int posY = y/(windowHeight/board.getSize());
		vector<int> point = {posX, board.getSize()-posY-1};
		board.setClick(point);
	}
 	glutPostRedisplay();
}
