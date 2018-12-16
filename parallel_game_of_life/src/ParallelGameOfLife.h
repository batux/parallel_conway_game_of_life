/*
 * ParallelGameOfLife.h
 *
 *  Created on: Dec 16, 2018
 *      Author: batuhan
 */

#ifndef PARALLELGAMEOFLIFE_H_
#define PARALLELGAMEOFLIFE_H_

#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <omp.h>
#include "chrono"
#include "vector"
#include "./Cell.h"

using namespace std;
using namespace std::chrono;

class ParallelGameOfLife {
public:
	ParallelGameOfLife();
	virtual ~ParallelGameOfLife();
	void run(int stepCount, bool initWithTestCase, bool runParallel);

private:
	const int gridRow = 20;
	const int gridColumn = 20;
	const int LIFE = 1;
	const int DEATH = 0;

	Cell *currentCellGrid[20][20];
	Cell *nextCellGrid[20][20];
	void init(bool initWithTestCase);
	void iterate();
	void parallelIterate();
	void transitionFunction(int i, int j);
	vector<Cell*> findNeighbours(int row, int column);
	void cloneCurrentCellGrid2NextCellGrid();
	void displayCellGrid();
	void prepareCellGridRandomly();
	void prepareCellGridWithTestCase();
};

#endif /* PARALLELGAMEOFLIFE_H_ */
