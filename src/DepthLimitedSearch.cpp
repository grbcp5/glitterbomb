/******************************************************************************
 *
 * File:
 *   DepthLimitedSearch
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   glitterbomb
 *
 ******************************************************************************/

#include "DepthLimitedSearch.h"
#include "LegalMoveGenerator.h"
#include "GlitterbombConstants.h"

#include <vector>
#include <stack>

using namespace std;

DepthLimitedSearch::DepthLimitedSearch( const uint32 max_depth ) :
    m_max_depth( max_depth ) {}


PuzzleSolution *DepthLimitedSearch::search( Puzzle *puzzle ) const {

  /* Local Variables */
  PuzzleSolution *result = new PuzzleSolution();
  stack< SearchNode * > frontier;
  vector< Move * > *children;
  Puzzle *state;
  Puzzle *childState;
  SearchNode *initialState;
  SearchNode *curNode;
  SearchNode *child;
#if DEBUG_OUTPUT
  uint32 nodesVisited( 0 );
#endif

  /* Initialize */
  initialState = new SearchNode( puzzle );
  frontier.push( initialState );

  /* Search */
  while ( !frontier.empty()) {

    /* Get next on frontier */
    curNode = frontier.top();
    frontier.pop();
    state = curNode->getState();

#if DEBUG_OUTPUT
    nodesVisited++;
    if ( nodesVisited % 10000 == 0 ) {
      cout << "Visited " << nodesVisited << " nodes." << endl;
    }
#endif

    /* Check if goal state */
    if ( state->isSolved()) {
      vector< Move > *sol = curNode->getAllActions();

      result->solutionExists = true;
      result->initialState = initialState->getState();
      result->numMovesToSolution = ( uint32 ) sol->size();
      result->moves = new Move[result->numMovesToSolution];

      for ( uint32 i = ( result->numMovesToSolution - 1 ); i != 0; --i ) {
        result->moves[ i ] = sol->at( i );
      }
      result->moves[ 0 ] = sol->at( 0 );

      /* Delete dynamic memory */
      delete sol;
      delete state;

      /* Deallocate search tree */
      deallocateAll( initialState );

      return result;
    }

    /* Generate children */
    children = getLegalMoves( state );

    for ( uint32 i = 0; i < children->size(); ++i ) {

      childState = new Puzzle( *( state ));
      childState->makeMove( *( children->at( i )));

      /* Format new search node */
      child = new SearchNode(
          childState,           // state
          curNode,              // parent
          children->at( i ),    // action
          curNode->m_depth + 1  // depth
      );

      /* Keep reference */
      curNode->m_children.push_back( child );

      /* Add child to frontier */
      if ( child->m_depth <= this->m_max_depth ) {
        frontier.push( child );
      }

      /* Delete dynamically allocated legal move */
      delete ( children->at( i ));
    }

    /* Delete dynamic memory */
    delete state;    // Delete copy of curNode's state
    delete children; // Delete dynamically allocated vector from getLegalMove

  } // while frontier not empty

  /* Deallocate search tree */
  deallocateAll( initialState );

  result->solutionExists = false;
  return result;
}

