#define _USE_MATH_DEFINES

#include<bits/stdc++.h>
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <cmath>
using namespace std;

#define pi acos(-1)

class point {
public: 
        double x, y, z;
        double n;
    
    point() {
        x = 0;
        y = 0;
        z = 0;
        n = 1;
    }

    point(double _x, double _y, double _z) {
        x = _x;
        y = _y;
        z = _z;
        n = 1;
    }

    point(double _x, double _y, double _z, double _n) {
        x = _x;
        y = _y;
        z = _z;
        n = _n;
    }

    point(const point& p) {
        x = p.x;
        y = p.y;
        z = p.z;
        n = p.n;
    }

    point operator+(const point& p) {
        return point(x + p.x, y + p.y, z + p.z);
    }

    point operator-(const point& p) {
        return point(x - p.x, y - p.y, z - p.z);
    }

    point operator*(const double& d) {
        return point(x * d, y * d, z * d);
    }

    point operator/(const double& d) {
        return point(x / d, y / d, z / d);
    }

    double operator*(const point& p) {
        return x * p.x + y * p.y + z * p.z;
    }

    point operator-() {
        return point(-x, -y, -z);
    }

    point operator^(const point& p) {
        return point(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
    }
    
    double find_len() {
        double len = sqrt(x * x + y * y + z * z);
        return len;
    }

    void normalize() {
        double len = sqrt(x * x + y * y + z * z);
        x /= len;
        y /= len;
        z /= len;
    }
};


double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;

int recursionLevel;
int imageHeight,imageWidth;
// position of camera
// point pos(200,0,10);
point pos(200,0,10);

// up, right and look direction
point up(0,0,1);
point rightV(-1 / sqrt(2), 1 / sqrt(2), 0);
point look(-1 / sqrt(2), -1 / sqrt(2), 0);

double ROT_ANG = pi/180;

int numSegments;



// draw axes
void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}
		glEnd();
	}
}

// draws grid
void drawGrid()
{
	int i;

    double cell_width = 1;

	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);
		{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}
		glEnd();
	}

    // if(drawGrid) {
    //     for(int i = 0; i <= 40; i++) {
    //         for(int j = 0; j <= 40; j++) {
    //             if((i + j) % 2 == 0) {
    //                 glColor3f(0, 0, 0);
    //             } else {
    //                 glColor3f(1, 1, 1);
    //             }
    //             glBegin(GL_QUADS);
    //             {
    //                 glVertex3f(-100 + i * cell_width, -100 + j * cell_width, 0);
    //                 // glVertex3f(i * cell_width, (j + 1) * cell_width, 0);
    //                 // glVertex3f((i + 1) * cell_width, (j + 1) * cell_width, 0);
    //                 // glVertex3f((i + 1) * cell_width, j * cell_width, 0);
    //                 glVertex3f(-100 + (i + 1) * cell_width, -100 + j * cell_width, 0);
    //                 glVertex3f(-100 + (i + 1) * cell_width, -100 + (j + 1) * cell_width, 0);
    //                 glVertex3f(-100 + i * cell_width, -100 + (j + 1) * cell_width, 0);
                
    //             }
    //             glEnd();
    //         }
    //     }
    // }
}


void rotate3D(point &vec,point &axis,double ang) {
	// vec = vec*cos(ang)+(vec*axis)*sin(ang);
	vec = vec * cos(ang)+(axis ^ vec) * sin(ang);
}
void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	//  gluLookAt(0,0,200,	0,0,0,	0,1,0);
	//gluLookAt(0,100,0,	0,0,0,	0,0,1);

	gluLookAt(pos.x, pos.y, pos.z, 
			pos.x + look.x, pos.y + look.y, pos.z + look.z, 
			up.x, up.y, up.z);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawGrid();

	glutSwapBuffers();
}
void init(){
	//codes for initialization
	drawgrid=1;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;
	numSegments = 36;

	// loadData();
	// image = bitmap_image(imageWidth, imageHeight);

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}


void keyboardListener(unsigned char key, int x,int y){
	switch(key){
		case '0':
			// capture();
			break;
		case '1':
			// rotate LEFT 
			rotate3D(rightV,up,ROT_ANG);
			rotate3D(look,up,ROT_ANG);
			break;
		case '2':
			// rotate right
			rotate3D(rightV,up,-ROT_ANG);
			rotate3D(look,up,-ROT_ANG);
			break;
		case '3':
			// rotate UP
			rotate3D(up,rightV,ROT_ANG);
			rotate3D(look,rightV,ROT_ANG);
			break;
		case '4':
			// rotate DOWN
			rotate3D(up,rightV,-ROT_ANG);
			rotate3D(look,rightV,-ROT_ANG);
			break;
		case '5':
			// tilt CLKWISE
			rotate3D(rightV,look,ROT_ANG);
			rotate3D(up,look,ROT_ANG);
			break;
		case '6':
			// tilt COUNTER CLKWISE
			rotate3D(rightV,look,-ROT_ANG);
			rotate3D(up,look,-ROT_ANG);
			break;
		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			pos = pos - look * 3;
			break;
		case GLUT_KEY_UP:		// up arrow key
			pos = pos + look * 3;
			break;
		case GLUT_KEY_RIGHT:
			pos = pos + rightV * 3;
			break;
		case GLUT_KEY_LEFT:
			pos = pos - rightV * 3;
			break;
		case GLUT_KEY_PAGE_UP:
			pos = pos + up * 3;
			break;
		case GLUT_KEY_PAGE_DOWN:
			pos = pos - up * 3;
			break;
		case GLUT_KEY_INSERT:
			break;
		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;
		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}

int main(int argc, char** argv) {
    glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Ray Tracing");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	// glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL
}