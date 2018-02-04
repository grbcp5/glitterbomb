/******************************************************************************
 *
 * File:
 *   BreadthFirstSearch
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   glitterbomb
 *
 ******************************************************************************/

#include "BreadthFirstSearch.h"

#include <queue>

using namespace std;

PuzzleSolution *BreadthFirstSearch::search( Puzzle *puzzle ) const {

  /* Local Variables */
  PuzzleSolution *result = new PuzzleSolution();
  queue< SearchNode > frontier;

  /* Initialize */
  frontier.push( SearchNode( puzzle ));

  /* Search */
  while ( !frontier.empty()) {


  }

  result->solutionExists = false;
  return result;
}
