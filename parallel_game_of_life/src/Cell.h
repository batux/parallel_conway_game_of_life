/*
 * Cell.h
 *
 *  Created on: Dec 16, 2018
 *      Author: batuhan
 */

#ifndef CELL_H_
#define CELL_H_

#include <iostream>

using namespace std;

class Cell {
public:
	Cell();
	virtual ~Cell();
	int getState();
	void setState(int state);
	Cell* clone();

private:
	int state;
};

#endif /* CELL_H_ */
