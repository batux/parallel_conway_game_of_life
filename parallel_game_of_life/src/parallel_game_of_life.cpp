//============================================================================
// Name        : parallel_game_of_life.cpp
// Author      : Batuhan Duzgun
// Version     :
// Copyright   : GNU
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "ParallelGameOfLife.h"

using namespace std;

int main() {

	// If you set runParallel variable to false, the algorithm will run in a single thread!
	bool runParallel = true;

	// If it is true, we utilize the test case, If it is false, we create a random cell grid.
	bool initWithTestCase = true;

	ParallelGameOfLife *parallelGameOfLife = new ParallelGameOfLife();
	parallelGameOfLife->run(20, initWithTestCase, runParallel);

	return 0;
}
