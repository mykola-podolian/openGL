/*
 * tetris.h
 *
 *  Created on: Jul 15, 2014
 *      Author: administrator
 */

#ifndef TETRIS_H_
#define TETRIS_H_

#include<iostream>
#include<vector>

const int SHAPES = 4;
const float YSTEP = 0.2f;

const int FIELD_WIDTH = 10;
const int FIELD_HEIGHT = 22;

class Shape {
private:
	float yPosition;
	float xPosition;
	int height;
	int width;
	bool * data;
public:
	Shape(bool * dat = { }, int h = 0, int w = 0);

	inline int getHeight() {
		return height;
	}

	inline int getWidth() {
		return width;
	}

	inline float getY() {
		return yPosition;
	}

	inline float getX() {
		return xPosition;
	}

	inline int setY(float y) {
		return yPosition = y;
	}

	inline int setX(float x) {
		return xPosition = x;
	}

	void draw();

	inline void moveBy(float y) {
		yPosition += y;
	}

	inline bool getValue(int h, int w) {
		return data[h * width + w];
	}

	Shape & operator=(Shape & sh);

	~Shape() {
		delete[] data;
	}
};

class GameBoard {
private:
	int fieldSize = FIELD_HEIGHT * FIELD_WIDTH;
	Shape shapes[SHAPES];
	bool field[FIELD_WIDTH * FIELD_HEIGHT] {0};
	Shape current;
	Shape next;
	void addShape();
	void addToField(Shape & sh);
	bool canMoveDown(Shape & sh);
public:
	GameBoard();

	void draw();

	void moveShapeRight();

	void moveShapeLeft();

	inline bool getValue(int h, int w) {
		return field[h * FIELD_WIDTH + w];
	}

	inline void setValue(int h, int w, bool value){
		field[h * FIELD_WIDTH + w] = value;
	}
};

#endif /* TETRIS_H_ */
