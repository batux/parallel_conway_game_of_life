/*
 * Cell.cpp
 *
 *  Created on: Dec 16, 2018
 *      Author: batuhan
 */

#include "Cell.h"

Cell::Cell() {
	this->state = 0;
}

Cell::~Cell() {
	cout << "Cell deleted from memory!" << endl;
}

int Cell::getState() {
	return this->state;
}

void Cell::setState(int state) {
	this->state = state;
}

Cell* Cell::clone() {
	Cell *cloneCell = new Cell();
	cloneCell->setState(this->getState());
	return cloneCell;
}

