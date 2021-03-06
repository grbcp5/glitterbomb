/******************************************************************************
 *
 * File:
 *   GreedyBestFirstGraphSearch
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   assignment3
 *
 ******************************************************************************/

#include "GreedyBestFirstGraphSearch.h"

#include <algorithm>

#include "LegalMoveGenerator.h"

using namespace std;

/* Heuristic functions ********************************************************/


/* Main heuristic used for standard execution */
double GreedyBestFirstHeuristic1::operator()( const Puzzle &p ) const {
  return (( p.m_quota - p.m_score ) / static_cast<double>(p.m_quota));
}


/* Bonus heuristic used for bonus assignment */
double GreedyBestFirstHeuristic2::operator()( const Puzzle &p ) const {
  return 3.0 / ( p.m_score < 1u ? 1u : p.m_score );
}


/* Bonus heuristic used for bonus assignment */
double GreedyBestFirstHeuristic3::operator()( const Puzzle &p ) const {
  return 1.0;
}


/* Executes search */
PuzzleSolution *GreedyBestFirstGraphSearch::search( Puzzle *puzzle ) const {

  /* Local Variables */
  PuzzleSolution *result = new PuzzleSolution();
  vector< SearchNode * > frontier;
  vector< SearchNode * > explored_set;
  vector< Move * > *children;
  Puzzle *state;
  Puzzle *childState;
  SearchNode *initialState;
  SearchNode *curNode;
  SearchNode *child;
  f_function *heuristic = new GreedyBestFirstHeuristic1();
  MinHeapComparator comp( heuristic );
#if DEBUG_OUTPUT || COUNT_TOTAL_NODES_EXPANDED
  uint32 nodesVisited( 0 );
#endif

  /* Initialize */
  initialState = new SearchNode( puzzle );
  frontier.push_back( initialState );
  make_heap( frontier.begin(), frontier.end(), comp ); // Included for clarity

  /* Search */
  while ( !frontier.empty()) {

    /* Get next on frontier */
    curNode = frontier[ 0 ];
    pop_heap( frontier.begin(), frontier.end(), comp );
    frontier.pop_back();
    state = curNode->getState();

#if DEBUG_OUTPUT
    nodesVisited++;
    if ( nodesVisited % 10000 == 0 ) {
      cout << "Nodes visited: " << nodesVisited << endl;
      cout << "\t" << "Current Node Depth: " << curNode->getPathCost() << endl;
    }
#elif COUNT_TOTAL_NODES_EXPANDED
    nodesVisited++;
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
      delete heuristic;

      /* Deallocate search tree */
      deallocateAll( initialState );

#if COUNT_TOTAL_NODES_EXPANDED
      result->totalNodesExpanded = nodesVisited;
#endif

      return result;
    }

    /* Add this node to explored set */
    explored_set.push_back( curNode );

    /* Generate children */
    children = getLegalMoves( state );

    /* For each child */
    for ( uint32 i = 0; i < children->size(); ++i ) {

      childState = new Puzzle( *( state ));
      childState->makeMove( *( children->at( i )));

      /* If this state is already discovered */
      if ( contains( frontier, childState )
           || contains( explored_set, childState )) {

        /* Delete dynamically allocated legal move */
        delete ( children->at( i ));
        delete childState;

        /* Do not add this node to the frontier */
        continue;
      }

      /* Format new search node with child state */
      child = new SearchNode(
          childState,       // state
          curNode,          // parent
          children->at( i ) // action
      );

      /* Keep reference for deallocate process */
      curNode->m_children.push_back( child );

      /* Add child to frontier */
      frontier.push_back( child );
      push_heap( frontier.begin(), frontier.end(), comp );

      /* Delete dynamically allocated legal move */
      delete ( children->at( i ));
    }

    /* Delete dynamic memory */
    delete state;    // Delete copy of curNode's state
    delete children; // Delete dynamically allocated vector from getLegalMove

  } // while frontier not empty

  /* Deallocate search tree */
  deallocateAll( initialState );
  delete heuristic;

#if COUNT_TOTAL_NODES_EXPANDED
  result->totalNodesExpanded = nodesVisited;
#endif

  result->solutionExists = false;
  return result;
}

