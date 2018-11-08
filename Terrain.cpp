//Name: Zihao Chen
//Student#: 001405956

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Terrain.h"

using namespace std;

setTerrain::setTerrain() {}

//This function builds random numbers which are the terrain height
void setTerrain::setRandom(int a, int b, int number){
	srand((int)time(NULL));
	for (int i = 0; i<number; i++){
		int tx = (rand() % (b - a + 1)) + a;
		int tz = (rand() % (b - a + 1)) + a;
		int size = (rand() % (b - (a + 1) + 1)) + (a + 1);
		int height = (rand() % (15 - 1 + 1)) + 1;
		Circles(tx, tz, size, height);
	}
}

//this function set terrain points array
void setTerrain::setPoints(int size){
	this->size = size;
	points = new float*[size*size];
	for (int i = 0; i < (size*size); ++i){
		points[i] = new float[3];
	}
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			points[i*size + j][0] = i;
			points[i*size + j][1] = 0;
			points[i*size + j][2] = j;
		}
	}
}

//this function draw polygon without height
void setTerrain::drawPolygon(){
	for (int i = 0; i < size - 1; ++i){
		for (int j = 0; j < size - 1; ++j){
			glColor3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_QUADS);
			glVertex3fv(points[i*size + j]);
			glVertex3fv(points[i*size + (j + 1)]);
			glVertex3fv(points[(i + 1)*size + (j + 1)]);
			glVertex3fv(points[(i + 1)*size + j]);
			glEnd();
		}
	}
}

//this function draw polygon wiout height with line loop function
void setTerrain::drawLineLoop(){
	for (int i = 0; i < size - 1; ++i){
		for (int j = 0; j < size - 1; ++j){
			glColor3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_LINE_LOOP);
			glVertex3fv(points[i*size + j]);
			glVertex3fv(points[i*size + (j + 1)]);
			glVertex3fv(points[(i + 1)*size + (j + 1)]);
			glVertex3fv(points[(i + 1)*size + j]);
			glEnd();
		}
	}
}




//this function draw trangle without height, two triangle builds one polygon
void setTerrain::drawTriangle(){
	for (int i = 0; i < size - 1; ++i){
		for (int j = 0; j < size - 1; ++j){
			glBegin(GL_TRIANGLES);
			glVertex3fv(points[size * i + j]);
			glVertex3fv(points[size * i + (j + 1)]);
			glVertex3fv(points[size * (i + 1) + j]);
			glEnd();

			glBegin(GL_TRIANGLES);
			glVertex3fv(points[size * i + (j + 1)]);
			glVertex3fv(points[size * (i + 1) + j]);
			glVertex3fv(points[size * (i + 1) + (j + 1)]);
			glEnd();
		}
	}
}




//this function draw triganle without height with line loop function
void setTerrain::drawTriangleLine(){
	for (int i = 0; i < size - 1; ++i){
		for (int j = 0; j < size - 1; ++j){
			glBegin(GL_LINE_LOOP);
			glVertex3fv(points[size * i + j]);
			glVertex3fv(points[size * i + (j + 1)]);
			glVertex3fv(points[size * (i + 1) + j]);
			glEnd();

			glBegin(GL_LINE_LOOP);
			glVertex3fv(points[size * i + (j + 1)]);
			glVertex3fv(points[size * (i + 1) + j]);
			glVertex3fv(points[size * (i + 1) + (j + 1)]);
			glEnd();
		}
	}
}




//The circles algorithm, referring from the site http://www.lighthouse3d.com/opengl/terrain/index.php?circles
void setTerrain::Circles(int Tx, int Tz, int Size, int height){
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			float pd = (sqrt(powf((points[i*size + j][0] - Tx), 2) + powf((points[i*size + j][2] - Tz), 2))) * 2 / Size;
			if (pd < 1.0){
				points[i*size + j][1] += height / 2 + cos(pd*3.14)*height / 2;
			}
		}
	}
}

setTerrain myTerrain = setTerrain();

float camPos[] = { 100, 50, 100 };	
float camTarget[] = { 0, 0, 0 };

float angle = 0;
int rotateX = 0;
int rotateY = 0;

float sceneScale = 0.8f;

float sceneSize = 0.6f;

float width = 680;
float height = 480;

int toggle = 1;
int quad = 1;

//set initial terain points
void initPoints(int size){
	int number = size / 2.5;
	myTerrain.setPoints(size);
	myTerrain.setRandom(1, size, number);
}

//keyboard function
void keyboard(unsigned char key, int xIn, int yIn){
	int mod = glutGetModifiers();
	switch (key){
	case 'q':
	case 27:	//27 is the esc key
		exit(0);
		break;
	case 'w':
		toggle = toggle + 1;
		break;
	case 'r':
		initPoints(100);
		break;
	case 't':
		quad = quad + 1;
		break;
	case 'i':
		camPos[1] = camPos[1] + 2;
		break;
	case 'k':
		camPos[1] = camPos[1] - 2;
		break;
	case 'j':
		camPos[0] = camPos[0] - 2;
		break;
	case 'l':
		camPos[0] = camPos[0] + 2;
		break;
	}
}

//keyboard function
void special(int key, int xIn, int yIn) {
	switch (key) {
	case GLUT_KEY_DOWN:
		rotateX = 1;
		rotateY = 0;
		angle -= 2;
		break;
	case GLUT_KEY_UP:
		rotateX = 1;
		rotateY = 0;
		angle += 2;
		break;
	case GLUT_KEY_LEFT:
		rotateX = 0;
		rotateY = 1;
		angle -= 2;
		break;
	case GLUT_KEY_RIGHT:
		rotateX = 0;
		rotateY = 1;
		angle += 2;
		break;
	}
}

//init openGL function with texture
void init(void){
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)((width + 0.0f) / height), 1, 50000);

	initPoints(100);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	float ambient[4] = { 0.1f,0.1f,0.1f,1 };
	float diffuse[4] = { 0,1,0,1 };
	float spec[4] = { 0,0,1,1 };
	float pos[4] = { 0,3,0,3 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);


	float m_amb[] = { 0.33, 0.22, 0.03, 1.0 };
	float m_dif[] = { 0.78, 0.57, 0.11, 1.0 };
	float m_spec[] = { 0.99, 0.91, 0.81, 1.0 };
	float m_em[] = { 0,1,0,1 };
	float shiny = 10; 

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
}

//display function
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], camTarget[0], camTarget[1], camTarget[2], 0, 1, 0);
	glPushMatrix();
	glRotatef(angle, rotateX, rotateY, 1);
	glScalef(sceneSize, sceneSize, sceneSize);
	glColor3f(0, 1, 0);
	if (quad % 2 == 1){
		if (toggle % 3 == 1){
			myTerrain.drawPolygon();
		}
		else if (toggle % 3 == 2){
			myTerrain.drawLineLoop();
		}
		else{
			myTerrain.drawPolygon();
			myTerrain.drawLineLoop();
		}
	}
	else{
		if (toggle % 3 == 1){
			myTerrain.drawTriangle();
		}
		else if (toggle % 3 == 2){
			myTerrain.drawTriangleLine();
		}
		else{
			myTerrain.drawTriangle();
			myTerrain.drawTriangleLine();
		}
	}
	glPopMatrix();

	glutSwapBuffers();
}
//This function will reshape the terrain.
void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();;
	gluPerspective(45, (float)((w + 0.0f) / h), 1, 50000);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

//fpstime, draw 17 times per second
void FPSTimer(int value) { 
	glutTimerFunc(17, FPSTimer, 0);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);		
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Terrain");	

	glutDisplayFunc(display);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutReshapeFunc(reshape);
	glutTimerFunc(17, FPSTimer, 0);

	init();
	cout << "This is a random terrain generation progam" << endl;
    cout << "Press 'R' to reset terrain" << endl;
    cout << "Press 'j','k','I','L' to tilt camera" << endl;
    cout << "Press arrow keys to rotate terrain" << endl;
    cout << "Press 'w' to toggle wireframe mode" << endl;
    cout << "Press 't' to switch between the terrain built by triangle or polygon. " << endl;
    cout << "Press 'q' to exit the program" << endl;
	glutMainLoop();				
	return(0);					
}

//Referenes: 1. Circle algorithm, LightHouse3D.com, http://www.lighthouse3d.com/opengl/terrain/index.php?circles
