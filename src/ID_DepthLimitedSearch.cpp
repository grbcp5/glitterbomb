/******************************************************************************
 *
 * File:
 *   ID_DepthLimitedSearch
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   glitterbomb
 *
 ******************************************************************************/

#include "ID_DepthLimitedSearch.h"

#include <iostream>

#include "GlitterbombConstants.h"
#include "DepthLimitedSearch.h"

using namespace std;

PuzzleSolution *ID_DepthLimitedSearch::search( Puzzle *puzzle ) const {

  PuzzleSolution *solution = NULL;
  Puzzle *puzzleCopy;
  DepthLimitedSearch *depthLimitedSearch = NULL;

  for ( uint32 depth = 0; depth < puzzle->m_num_swaps; ++depth ) {

#if DEBUG_OUTPUT

    cout << "Increasing max depth to " << depth << "." << endl;

#endif

    depthLimitedSearch = new DepthLimitedSearch( depth );
    puzzleCopy = new Puzzle( *puzzle );

    solution = depthLimitedSearch->search( puzzleCopy );

    delete puzzleCopy;
    delete depthLimitedSearch;

    if ( solution->solutionExists ) {
      return solution;
    }

    delete solution;
  }

  return NULL;
}
