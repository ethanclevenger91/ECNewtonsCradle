//
//  main.cpp
//  MatrixExample
//
//  Created by Timothy Urness on 9/24/12.
//  Copyright (c) 2012 Timothy Urness. All rights reserved.
//

#if defined(__APPLE__)
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif

#include<iostream>

#include "TransformationController.h"

using namespace std;

#define WIDTH 500
#define HEIGHT 400
double alpha = 0.0;
TransformationController* tc;

GLfloat verticesOrigin[] = {-25,0, 25,0, 0,25, 0, -25};
GLfloat verticesTriangle[] = {-50, -28.9, 50, -28.9, 0, 57.7};


void display(void) {
	/*clear all pixels*/
	glClear(GL_COLOR_BUFFER_BIT);
	//glLoadIdentity();
    glPushMatrix(); {
        glColor3f(1, 1, 1);
 
        //draw origin
        glEnableClientState(GL_VERTEX_ARRAY);
        /*set pointer to vertices array*/
        glVertexPointer(2, GL_FLOAT, 0, verticesOrigin);
        glDrawArrays(GL_LINES, 0, 4);
        glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays

        
        //rotate (slow)
        tc->rotate(alpha);
        glMultMatrixf(tc->getMatrix());
        
        //translate
        tc->translate(250, 0, 0);
        glMultMatrixf(tc->getMatrix());
        
        //rotate (fast)
        tc->rotate(30*alpha);
        glMultMatrixf(tc->getMatrix());
        
        //draw Triangle
        glColor3f(1.0, 0, 0);
        
        glEnableClientState(GL_VERTEX_ARRAY);
        
        /*set pointer to vertices array*/
        glVertexPointer(2, GL_FLOAT, 0, verticesTriangle);
        glDrawArrays(GL_POLYGON, 0, 3); //draw the three points
        
        glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
    }
	glPopMatrix();
	/*process buffered OpenGL routines*/
	glutSwapBuffers();
}

void init(void) {
	/*set clearing (background) color*/
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	tc = new TransformationController();
	
	/*initialize viewing values*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-WIDTH, WIDTH, -HEIGHT, HEIGHT);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int extra) {
	alpha+=.25;
	glutTimerFunc(extra, timer,extra);
	glutPostRedisplay();
}


/*
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGB).  Open window with "Drake CS 147" in
 *  title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutCreateWindow("Drake CS 147");
	init();
	glutDisplayFunc(display);
	glutTimerFunc(0, timer,33);
	glutMainLoop();
}

