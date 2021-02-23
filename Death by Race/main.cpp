#include <windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <color.h>
#include <iostream>
#include <cmath>
#include <mmsystem.h>
// User libraries
#include <shapes.h>
#include <background.h>
#include <hero.h>
#include <enemy.h>
#include <ai.h>
#include <text.h>
#include <controller.h>
#include <particles.h>


using namespace std;
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600
#define SETCOLOR(color) color.Getred(), color.Getgreen(), color.Getblue()

float currentWidth = 1024;
float currentHeight = 600;
Controller control;
Particles pr;
void changeSize(int w, int h) {

    //glClearColor(0.0,0.0,0.0,0.0);
    glutReshapeWindow( SCREEN_WIDTH, SCREEN_HEIGHT);
    glutPositionWindow(50,50);

	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);

    currentWidth = w;
    currentHeight = h;
	gluPerspective(100,ratio,1,100);
	glMatrixMode(GL_MODELVIEW);

}

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glClearColor(0.0,0.0,0.0,0.0);
        //bg animations
    control.renderStart();
    glFlush();
	glutSwapBuffers();
}


void mySpecialKeys(int key, int x, int y) {

	switch(key) {
        case GLUT_KEY_UP:
            control.ai.hero.moveUp();
            break;
        case GLUT_KEY_DOWN:
            control.ai.hero.moveDown();
            break;
        case GLUT_KEY_LEFT:
            control.ai.hero.moveLeft();
            break;
        case GLUT_KEY_RIGHT:
            control.ai.hero.moveRight();
            break;

        default:
            break;

	}
}


void myKeys(unsigned char key, int x, int y){
    if(key == 's' || key == 'S') {
            if(!control.ai.hero.jumper)
                control.ai.hero.shoot = true;
        }
    else if(key == 'q' || key == 'Q'){
        exit(0);
    }
    else if(key == 'p' || key == 'P'){
            glutIdleFunc(NULL);
    }
    else if(key == 'r' || key == 'R'){
            glutIdleFunc(renderScene);
    }
}

void myMouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
           // cout << (float)((x/currentWidth)-1) << " " << (float) ((y/currentHeight)-1) << endl;
			control.clicked((float)((x/currentWidth)-1), (float) ((y/currentHeight)-1));
		}
	}
}


int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(50,50);
	glutCreateWindow("DEATH BY RACE");
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

    //glClearColor(0.0,0.0,0.0,0.0);
    Color bgcolor;
    bgcolor.setColor("ffffff");
    glClearColor(SETCOLOR(bgcolor),0.0);

    glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutKeyboardFunc( myKeys );
    glutSpecialFunc(mySpecialKeys);
    glutMouseFunc(myMouse);

	glutMainLoop();
	return 0;
}
