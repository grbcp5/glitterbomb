/******************************************************************************
 *
 * File:
 *   Searcher
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   glitterbomb
 *
 ******************************************************************************/

#include "Searcher.h"

/* Default Constructor */
PuzzleSolution::PuzzleSolution()
    : initialState( NULL ),
      numMovesToSolution( 0 ),
      moves( NULL ) {}

/* De-constructor */
PuzzleSolution::~PuzzleSolution() {

  delete initialState;
  delete moves;

}