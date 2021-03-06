#include <GL/glut.h>
#include <iostream>
#include "tetris.h"
#define window_width  640
#define window_height 480

GameBoard gameBoard;

// Main loop
void main_loop_function() {
	// And depth (used internally to block obstructed objects)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Load identity matrix
	gameBoard.draw();
	glutSwapBuffers();
}
// Initialze OpenGL perspective matrix
void GL_Setup(int width, int height) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, width, height);
	gluPerspective(100, (float) width / height, .1, 100);
	glMatrixMode(GL_MODELVIEW);
}

void onKeyDown(unsigned char key, int x, int y) {
	switch (key) {
	case 033: // octal equivalent of the Escape key
		exit(0);
		break;
	case 'a':
		gameBoard.moveShapeLeft();
		break;
	case 'd':
		gameBoard.moveShapeRight();
		break;
	}
}

// Initialize GLUT and start main loop
int main(int argc, char** argv) {
	std::cout << "Hello gl";
	glutInit(&argc, argv);
	glutInitWindowSize(window_width, window_height);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Hello GL");
	glutIdleFunc(main_loop_function);
	GL_Setup(window_width, window_height);
	glutKeyboardFunc(onKeyDown);
	glutMainLoop();
}

