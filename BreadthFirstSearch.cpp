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
#include "LegalMoveGenerator.h"

#include <queue>

using namespace std;


/* Function:
 *   deallocateAll
 *
 * Description:
 *   Recursively deallocate search node and all its children
 */

void deallocateAll( SearchNode *&node ) {

  /* Return if null pointer */
  if ( node == NULL ) {
    return;
  }

  /* Delete all children first */
  for ( int i = 0; i < node->m_children.size(); ++i ) {
    deallocateAll( node->m_children[ i ] );
  }

  /* Deallocate node */
  delete node;
  node = NULL;
}


/* Function:
 *   search
 * Description:
 *   Does breadth first search to find a goal state
 */

PuzzleSolution *BreadthFirstSearch::search( Puzzle *puzzle ) const {

  /* Local Variables */
  PuzzleSolution *result = new PuzzleSolution();
  queue< SearchNode * > frontier;
  vector< Move * > *children;
  Puzzle *state;
  Puzzle *childState;
  SearchNode *initialState;
  SearchNode *curNode;
  SearchNode *child;
  uint32 nodesVisited( 0 );

  /* Initialize */
  initialState = new SearchNode( puzzle );
  frontier.push( initialState );

  /* Search */
  while ( !frontier.empty()) {

    /* Get next on frontier */
    curNode = frontier.front();
    frontier.pop();
    state = curNode->getState();

    nodesVisited++;
    if ( nodesVisited % 10000 == 0 ) {
      cout << "Nodes visited: " << nodesVisited << endl;
      cout << "\t" << "Current Node Depth: " << curNode->getPathCost() << endl;
    }

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

      return result;
    }

    /* Generate children */
    children = getLegalMoves( state );

    for ( uint32 i = 0; i < children->size(); ++i ) {

      childState = new Puzzle( *( state ));
      childState->makeMove( *( children->at( i )));

      /* Format new search node */
      child = new SearchNode(
          childState,       // state
          curNode,          // parent
          children->at( i ) // action
      );

      /* Keep reference */
      curNode->m_children.push_back( child );

      /* Add child to frontier */
      frontier.push( child );

      /* Delete dynamically allocated legal move */
      delete ( children->at( i ) );
    }

    /* Delete dynamic memory */
    delete state;    // Delete copy of curNode's state
    delete children; // Delete dynamically allocated vector from getLegalMove

  } // while frontier not empty

  result->solutionExists = false;
  return result;
}
