// AssignmentFourColors.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>
#include<vector>
#include<math.h>
#include<GL/glut.h>
#include "TransformationController.h"

using namespace std;
#define WIDTH 900
#define HEIGHT 500

struct Point {
	int x;
	int y;
};

struct Color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
}; // Color defined as a class



GLfloat leftTriangle[] = {-200,-200, -100,-200, -150,-100};
GLfloat rightTriangle[] = {200,-200, 300,-200, 250,-100};
GLfloat triangles[] = {-100,-200, 0,-200, -50,-100, 0,-200, 100,-200, 50,-100, 100,-200, 200,-200, 150,-100};
float color[3] = {1.0, 1.0, 1.0};
double alpha = 0.0;
double position = 0;
double scaling = 1;
double adjustScaling = .05;
bool rising = true;
bool leftActive = true;
bool isRotating = false;
int colorCounter = 0;

void keyboard(unsigned char, int, int);

TransformationController* tc;

vector<Point> originPoint;
vector<Point> leftBezierPoints;
vector<Point> rightBezierPoints;
vector<Point> strings;
vector<Point> movingStrings;

vector<Color> colors;

GLfloat r,g,b;

GLfloat verticesOrigin[] = {-25,0, 25,0, 0,25, 0,-25};
GLfloat verticesTriangle[] = {-50, -28.9, 50, -28.9, 0, 57.7};

//input: int h (hue); int s (saturation); int v (value)
//input: return references for r (red), g (green), and b (blue)
void hsv2rgb (int h, double s, double v, GLfloat *r, GLfloat *g, GLfloat *b) {
    
	int ndx = h/60;
	GLfloat f = h/60.0 - h/60;
	GLfloat p = v*(1-s);
	GLfloat q = v*(1-f*s);
	GLfloat t = v*(1-(1-f)*s);
	switch (ndx) {
		case 0:
			*r=v;
			*g=t;
			*b=p;
			break;
		case 1:
			*r=q;
			*g=v;
			*b=p;
			break;
		case 2:
			*r=p;
			*g=v;
			*b=t;
			break;
		case 3:
			*r=p;
			*g=q;
			*b=v;
			break;
		case 4:
			*r=t;
			*g=p;
			*b=v;
			break;
		case 5:
			*r=v;
			*g=p;
			*b=q;
			break;
		default:
			break;
	}
	
}

void timer(int extra) {
	if(leftActive == true)
	{
		if((position < leftBezierPoints.size()-1) && rising == true) 
		{
			position++;
		}
		else if(position == leftBezierPoints.size()-1)
		{
			rising = false;
			position--;
		}
		else if(position > 0 && rising == false) 
		{
			position--;
		}
		else if(position == 0)
		{
			rising = true;
			position++;
			leftActive = false;
			//scaling = scaling - adjustScaling;
			//if(scaling < -2) scaling = 1;
			//if(scaling > 2) adjustScaling = .05;


			//it hit. update color
			colors.clear();
			Color c = Color();
			hsv2rgb(colorCounter, 1, 1, &r, &g, &b);
			c.r = r;
			c.g = g;
			c.b = b;
			for(int i = 0; i < 17; i++)
			{
				colors.push_back(c);
			}
			if(colorCounter == 360) colorCounter = 0;
			colorCounter+=30;


		}
	}
	else
	{
		if((position < rightBezierPoints.size()-1) && rising == true)
		{
			position++;
		}
		else if(position == rightBezierPoints.size()-1)
		{
			rising = false;
			position--;
		}
		else if(position > 0 && rising == false) 
		{
			position--;
		}
		else if(position == 0)
		{
			rising = true;
			position++;
			leftActive = true;
			//scaling = scaling - adjustScaling;
			//if(scaling < -2) scaling = 1;
			//if(scaling > 2) adjustScaling = .05;

			//if hit, update color
			colors.clear();
			Color c = Color();
			hsv2rgb(colorCounter, 1, 1, &r, &g, &b);
			c.r = r;
			c.g = g;
			c.b = b;
			for(int i = 0; i < 17; i++)
			{
				colors.push_back(c);
			}
			if(colorCounter == 360) colorCounter = 0;
			colorCounter+=30;
		}
	}
	
	if(isRotating == true) alpha+=.01;
	glutTimerFunc(extra, timer,extra);
	glutPostRedisplay();
}


void bezier(Point p0, Point p1, Point p2, Point p3, char side) //fills bezier vector every four points
{
	Point newPoint = Point();
	for(double t=0; t<=1.0; t+=.01)
	{
		newPoint.x = (1-t)*(1-t)*(1-t)*p0.x + 3*(1-t)*(1-t)*t*p1.x + 3*(1-t)*t*t*p2.x +
			t*t*t*p3.x;
		newPoint.y = (1-t)*(1-t)*(1-t)*p0.y + 3*(1-t)*(1-t)*t*p1.y + 3*(1-t)*t*t*p2.y +
			t*t*t*p3.y;
		if(side == 'r') rightBezierPoints.push_back(newPoint);
		else if(side == 'l') leftBezierPoints.push_back(newPoint);
	}
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 'q': //q key
	case 27: //escape key
		exit(0);
	case '0': //set scaling level
		scaling = 1;
		break;
	case '1':
		scaling = 1.25;
		break;
	case '2':
		scaling = 1.5;
		break;
	case '3':
		scaling = 1.75;
		break;
	case '4':
		scaling = 2;
		break;
	case 'r':
		if(isRotating == true) isRotating = false;
		else isRotating = true;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}


void display(void)
{

	glPushMatrix();

	//scaling
	tc->scale(scaling, scaling, 0);
	glMultMatrixf(tc->getMatrix());

	tc->rotate(alpha);
	glMultMatrixf(tc->getMatrix());

	glClear(GL_COLOR_BUFFER_BIT);	
	glColor3fv(color);

	Point pt = Point();
	Point leftTip = Point();
	Point rightTip = Point();
	pt.x = 50;
	pt.y = 200;
	movingStrings.push_back(pt);
	if(leftActive == true)
	{
		leftTip.x = -150 + leftBezierPoints[position].x;
		leftTip.y = -100 + leftBezierPoints[position].y;
	}
	else
	{
		leftTip.x = -150;
		leftTip.y = -100;
	}
	movingStrings.push_back(leftTip);
	movingStrings.push_back(pt);
	if(leftActive == false)
	{
		rightTip.x = 250 + rightBezierPoints[position].x;
		rightTip.y = -100 + rightBezierPoints[position].y;
	}
	else
	{
		rightTip.x = 250;
		rightTip.y = -100;
	}
	movingStrings.push_back(rightTip);


	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colors.data());
	glVertexPointer(2, GL_FLOAT, 0, triangles);
	glDrawArrays(GL_TRIANGLES, 0, 9);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colors.data());
	if(leftActive == true) glVertexPointer(2, GL_FLOAT, 0, rightTriangle);
	else glVertexPointer(2, GL_FLOAT, 0, leftTriangle);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glPointSize(5);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_INT, 0, originPoint.data());
	glDrawArrays(GL_POINTS, 0, originPoint.size());
	glDisableClientState(GL_VERTEX_ARRAY);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colors.data());
	glVertexPointer(2, GL_INT, 0, strings.data());
	glDrawArrays(GL_LINES, 0, strings.size());
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, colors.data());
	glVertexPointer(2, GL_INT, 0, movingStrings.data());
	glDrawArrays(GL_LINES, 0, movingStrings.size());
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	 glPushMatrix(); {

        //translate
		if(leftActive == true) tc->translate(leftBezierPoints[position].x, leftBezierPoints[position].y, 0);
		else tc->translate(rightBezierPoints[position].x, rightBezierPoints[position].y, 0);
        glMultMatrixf(tc->getMatrix());

		glEnableClientState(GL_VERTEX_ARRAY);
		if(leftActive == true) glVertexPointer(2, GL_FLOAT, 0, leftTriangle);
		else glVertexPointer(2, GL_FLOAT, 0, rightTriangle);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableClientState(GL_VERTEX_ARRAY);
	 }
	 glPopMatrix();
	 glPopMatrix();
	 movingStrings.clear();
	 glutSwapBuffers();
}

void init(void) {
	/*set clearing color*/

	//initiate points for drawing
	Point left1 = Point();
	Point left2 = Point();
	Point left3 = Point();
	Point left4 = Point();
	Point right1 = Point();
	Point right2 = Point();
	Point right3 = Point();
	Point right4 = Point();
	left1.x = 0;
	left1.y = 0;
	left2.x = -35;
	left2.y = 20;
	left3.x = -135;
	left3.y = 140;
	left4.x = -140;
	left4.y = 150;
	right1.x = 0;
	right1.y = 0;
	right2.x = 35;
	right2.y = 20;
	right3.x = 135;
	right3.y = 140;
	right4.x = 140;
	right4.y = 150;
	bezier(left1, left2, left3, left4, 'l');
	bezier(right1, right2, right3, right4, 'r');
	Point pt = Point();
	pt.x = 50;
	pt.y = 200;
	originPoint.push_back(pt);

	for(int i = 4; i<18; i+=6)
	{
		strings.push_back(pt);
		Point aPoint = Point();
		aPoint.x = triangles[i];
		aPoint.y = triangles[i+1];
		strings.push_back(aPoint);
	}

	Color c = Color();
	hsv2rgb(colorCounter, 1, 1, &r, &g, &b);
	c.r = r;
	c.g = g;
	c.b = b;
	for(int i = 0; i < 17; i++)
	{
		colors.push_back(c);
	}

	glClearColor(0.0, 0.0, 0.0, 0.0); 
	tc = new TransformationController;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-WIDTH, WIDTH, -HEIGHT, HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Newton's Cradle");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(0, timer,2);
	glutMainLoop();
}


