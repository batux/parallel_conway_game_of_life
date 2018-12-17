/*
 * ParallelGameOfLife.cpp
 *
 *  Created on: Dec 16, 2018
 *      Author: batuhan
 */

#include "ParallelGameOfLife.h"

ParallelGameOfLife::ParallelGameOfLife() {

}

ParallelGameOfLife::~ParallelGameOfLife() {
	delete this;
}

void ParallelGameOfLife::prepareCellGridRandomly() {

	srand((int)time(0));

	for(int i=0; i < this->gridRow; i++) {
		for(int j=0; j < this->gridColumn; j++) {

			bool state = (rand() % 2 == 0);

			Cell *cell = new Cell();
			cell->setState(state ? this->LIFE : this->DEATH);
			this->currentCellGrid[i][j] = cell;
		}
	}
}

void ParallelGameOfLife::prepareCellGridWithTestCase() {

	int row1 = 10;
	int col1 = 10;

	int row2 = 11;
	int col2 = 10;

	int row3 = 11;
	int col3 = 9;

	int row4 = 11;
	int col4 = 11;

	for(int i=0; i < this->gridRow; i++) {
		for(int j=0; j < this->gridColumn; j++) {

			int state = this->DEATH;

			if((row1 == i && col1 == j) ||
			   (row2 == i && col2 == j) ||
			   (row3 == i && col3 == j) ||
			   (row4 == i && col4 == j)) {
				state = this->LIFE;
			}

			Cell *cell = new Cell();
			cell->setState(state);
			this->currentCellGrid[i][j] = cell;
		}
	}
}

void ParallelGameOfLife::init(bool initWithTestCase) {

	if(initWithTestCase) {
		this->prepareCellGridWithTestCase();
	}
	else {
		this->prepareCellGridRandomly();
	}
}

void ParallelGameOfLife::run(int stepCount, bool initWithTestCase, bool runParallel) {

	this->init(initWithTestCase);

	milliseconds startTimeInMillis = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	long startTimeAsLong = startTimeInMillis.count();

	for(int stepCounter=0; stepCounter < stepCount; stepCounter++) {
		this->displayCellGrid();
		this->cloneCurrentCellGrid2NextCellGrid();

		if(runParallel) {
			this->parallelIterate();
		}
		else {
			this->iterate();
		}

		cout << "Index: " << stepCounter << endl;
		usleep(10);
	}

	milliseconds runnigTimeInMillis = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	long runnigTimeAsLong = runnigTimeInMillis.count();

	long timeDiffInMillis = runnigTimeAsLong - startTimeAsLong;

	cout << "Runtime in milliseconds: " << timeDiffInMillis << endl;
}

void ParallelGameOfLife::parallelIterate() {

	#pragma omp parallel for
	for(int i=0; i < this->gridRow; i++) {
		for(int j=0; j < this->gridColumn; j++) {
			this->transitionFunction(i,j);
		}
	}
}

void ParallelGameOfLife::iterate() {

	for(int i=0; i < this->gridRow; i++) {
		for(int j=0; j < this->gridColumn; j++) {
			this->transitionFunction(i,j);
		}
	}
}

void ParallelGameOfLife::transitionFunction(int i, int j) {

	int liveCellCount = 0;

	// calculate new state value of the current cell with its neighbors
	vector<Cell*> neighbours = this->findNeighbours(i,j);
	for(unsigned int i=0; i < neighbours.size(); i++) {

		Cell* neighbourCell = neighbours.at(i);

		if(neighbourCell == NULL) continue;

		if(neighbourCell->getState() == this->LIFE) {
			liveCellCount = liveCellCount + 1;
		}
	}

	Cell *currentCell = this->currentCellGrid[i][j];

	// If the current cell is death, check the rule which gives chance to live again
	if(currentCell->getState() == this->DEATH) {
		if(liveCellCount == 3) {
			currentCell->setState(this->LIFE);
		}
	}
	else {
		if(liveCellCount < 2 || liveCellCount > 3) {
			currentCell->setState(this->DEATH);
		}
	}
}

vector<Cell*> ParallelGameOfLife::findNeighbours(int row, int column) {

	vector<Cell*> neighbours;

	for(int i=-1; i <= 1; i++) {
		for(int j=-1; j <= 1; j++) {
			if(!(i == 0 && j == 0)) {
				if( ((row + i) >= 0 && (row + i) < this->gridRow) &&
					((column + j) >=0 && (column + j) < this->gridColumn) ) {
					neighbours.push_back(this->nextCellGrid[(row + i)][(column + j)]);
				}
			}
		}
	}

	return neighbours;
}

void ParallelGameOfLife::cloneCurrentCellGrid2NextCellGrid() {

	for(int i=0; i < this->gridRow; i++) {
		for(int j=0; j < this->gridColumn; j++) {
			Cell *currentCell = this->currentCellGrid[i][j];
			delete this->nextCellGrid[i][j];
			this->nextCellGrid[i][j] = currentCell->clone();
			//currentCell->~Cell();
		}
	}
}

void ParallelGameOfLife::displayCellGrid() {

	for(int i=0; i < this->gridRow; i++) {
		for(int j=0; j < this->gridColumn; j++) {
			cout << " " << this->currentCellGrid[i][j]->getState() << " ";
		}
		cout << endl;
	}
	cout << "--------------------------------------------------" << endl;
}

