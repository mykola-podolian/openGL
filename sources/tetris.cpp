/*
 * tetris.cpp
 *
 *  Created on: Jul 15, 2014
 *      Author: administrator
 */
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "tetris.h"

void drawQuad(float x, float y, float z);
void print(Shape & sh);
void print(GameBoard & board);

GameBoard::GameBoard() {
	bool firstData[6] = { false, true, true, true, false, true };
	bool secondData[6] = { false, true, true, true, true, false };
	bool thirdData[6] = { true, true, true, false, true, false };
	bool fourthData[4] = { true, true, true, true };
	Shape first(firstData, 3, 2);
	Shape second(secondData, 2, 3);
	Shape third(thirdData, 3, 2);
	Shape fourth(fourthData, 4, 1);
	shapes[0] = first;
	shapes[1] = second;
	shapes[2] = third;
	shapes[3] = fourth;
	for (int i = 0; i < SHAPES; i++) {
		print(shapes[i]);
	}
	next = first;

	addShape();
	print(*this);
}

void GameBoard::draw() {
	glLoadIdentity();
	//translate field to center
	glTranslatef(-FIELD_WIDTH / 2, -FIELD_HEIGHT / 2, -10);
	glPushMatrix();

	glBegin(GL_LINE_LOOP);
	glColor3ub(000, 255, 000);
	glVertex3f(0, 0, 0);
	glVertex3f(FIELD_WIDTH, 0, 0);
	glVertex3f(FIELD_WIDTH, FIELD_HEIGHT, 0);
	glVertex3f(0, FIELD_HEIGHT, 0);
	glEnd();
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < fieldSize; i++) {
		if (field[i]) {
			drawQuad(i / 10, i % 10, 0);
		}
	}
	glEnd();

	next.draw();
	glPopMatrix();

	if (std::floor(current.getY() - YSTEP) >= 0) {
		if (canMoveDown(current)) {
			current.moveBy(-YSTEP);
		} else {
			addToField(current);
			addShape();
		}
	} else {
		addToField(current);
		addShape();
	}
	current.draw();
}

void GameBoard::addShape() {
	srand(time(NULL));
	current = next;
	next = shapes[rand() % 4];
	current.setY(FIELD_HEIGHT - current.getHeight());
	current.setX(0);
	next.setX(FIELD_WIDTH + 2);
	next.setY(FIELD_HEIGHT - next.getHeight() - 2);
	if (!canMoveDown(current)) {
		for (int i = 0; i < fieldSize; i++) {
			field[i] = 0;
		}
	}
}

bool GameBoard::canMoveDown(Shape & sh) {
	int y = floor(sh.getY() - YSTEP);
	int x = sh.getX();
	for (int w = 0; w < sh.getWidth(); w++) {
		for (int h = 0; h < sh.getHeight(); h++) {
			if (!sh.getValue(h, w)) {
				continue;
			} else {
				if (getValue(y + h, x + w)) {
					return false;
				} else {
					break;
				}
			}
		}
	}
	return true;
}

void GameBoard::moveShapeRight() {
	int currentX = current.getX();
	if (currentX + current.getWidth() < FIELD_WIDTH) {
		current.setX(currentX + 1);
	}
}

void GameBoard::moveShapeLeft() {
	int currentX = current.getX();
	if (currentX > 0) {
		current.setX(currentX - 1);
	}
}

void GameBoard::addToField(Shape & sh) {
	for (int h = 0; h < sh.getHeight(); h++) {
		for (int w = 0; w < sh.getWidth(); w++) {
			if (sh.getValue(h, w)) {
				int y = std::floor(sh.getY() + 0.5) + h;
				int x = std::floor(sh.getX() + 0.5) + w;
				setValue(y, x, true);
			}
		}
	}
	std::cout.flush();
	print(*this);
}

Shape::Shape(bool * dat, int h, int w) :
		yPosition(11), xPosition(0), height(h), width(w) {
	data = new bool[h * w];
	for (int i = 0; i < h; i++) {
		data[i] = new bool[w];
		for (int j = 0; j < w; j++) {
			int index = i * w + j;
			bool value = dat[index];
			data[i * w + j] = value;
		}
	}
}

void Shape::draw() {
	glTranslatef(xPosition, yPosition, 0);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (data[i * width + j]) {
				drawQuad(i, j, 0);
			}
		}
	}
	glEnd();
}

Shape & Shape::operator=(Shape & sh) {
	xPosition = sh.xPosition;
	yPosition = sh.yPosition;
	height = sh.height;
	width = sh.width;
	int cells = width * height;
	data = new bool[cells];
	for (int i = 0; i < cells; i++) {
		data[i] = sh.data[i];
	}
	return *this;
}
;

void drawQuad(float y, float x, float z) {
	glColor3ub(000, 255, 000);
	glVertex3f(x + 1, y + 1, z);
	glVertex3f(x, y + 1, z);
	glVertex3f(x, y, z);
	glVertex3f(x + 1, y + 1, z);
	glVertex3f(x, y, z);
	glVertex3f(x + 1, y, z);
}

void print(Shape & sh) {
	using std::cout;
	cout << "shape:\n";
	for (int i = 0; i < sh.getHeight(); i++) {
		for (int j = 0; j < sh.getWidth(); j++) {
			if (sh.getValue(i, j)) {
				cout << "*";
			} else {
				cout << " ";
			}
		}
		cout << '\n';
	}
	cout << "shape end\n";
	cout.flush();
}

void print(GameBoard & board) {
	using std::cout;
	cout << "board:\n";
	cout << "************\n";
	for (int h = FIELD_HEIGHT; h >= 0; h--) {
		cout << "*";
		for (int w = 0; w < FIELD_WIDTH; w++) {
			if (!board.getValue(h, w)) {
				cout << " ";
			} else {
				cout << "*";
			}
		}
		cout << "*";
		cout << '\n';
	}
	cout << "************\n";
	cout << "board end\n";
	cout.flush();
}
