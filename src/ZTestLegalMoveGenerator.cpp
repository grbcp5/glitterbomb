/******************************************************************************
 *
 * File:
 *   ZTestLegalMoveGenerator
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   glitterbomb
 *
 ******************************************************************************/

#include "ZTestLegalMoveGenerator.h"

#include <iostream>

#include "Puzzle.h"
#include "LegalMoveGenerator.h"
#include "GreedyBestFirstGraphSearch.h"

using namespace std;

Puzzle *makePuzzle( const uint32 quota, const uint32 score ) {
  Puzzle *p = new Puzzle(
      quota,
      0,
      0,
      0,
      0,
      0,
      0
  );
  p->m_score = score;
  return p;
}

int ZTestLegalMoveGenerator::test( uint32 testID ) const {

  /* Test case type */
  typedef struct {
      const char *description;
      const char *puzzle_file;
  } test_case_t;

  /* Test cases */
  const test_case_t test_cases[] = {
      {
          "Test puzzle 1",
          "puzzles/puzzle1.txt"
      }
  };
  const uint32 NUM_TEST_CASES = 1;

  /* Local Variables */
  Puzzle *puzzle;
  Puzzle *puzzleCopy;
  vector< Move * > *ret_val;
  Move *curMove;
  uint32 moveScore;

  /* Execute each test case */
  for ( const test_case_t *cur_test = test_cases;
        cur_test != test_cases + NUM_TEST_CASES;
        ++cur_test ) {

    /* Output test description */
    cout << "Test: " << cur_test->description << endl;

    /* Create test from file */
    puzzle = Puzzle::construct( cur_test->puzzle_file );
    cout << "Puzzle:\n" << ( *puzzle ) << endl;

    /* Call FUT */
    ret_val = getLegalMoves( puzzle );

    /* Return error if no legal moves found */
    if ( !ret_val->size()) {
      return testID;
    }

    /* Print out all legal moves */
    for ( uint32 i = 0; i < ret_val->size(); ++i ) {
      curMove = ret_val->at( i );

      cout << i << ": "
           << "(r:" << curMove->from.row << ",c:" << curMove->from.col << ") "
           << "(r:" << curMove->to.row << ",c:" << curMove->to.col << ") "
           << "devices matched: " << curMove->resultingMatches << ": " << endl;

      if ( curMove->resultingMatches != curMove->matchedDevices->size()) {
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        return testID;
      }

      puzzleCopy = new Puzzle( *puzzle );
      moveScore = puzzleCopy->makeMove( *curMove );

      cout << "Score: " << moveScore << endl;
      cout << ( *puzzleCopy ) << endl;

      delete puzzleCopy;

      delete curMove;
    }

    /* Delete dynamic memory */
    delete puzzle;
    delete ret_val;

  }

  cout << "\n\n\n-- Test Heap--\n" << endl;

  vector< SearchNode * > frontier;

  frontier.push_back( new SearchNode( makePuzzle( 10, 4 ))); // 6 / 3 = 2
  frontier.push_back( new SearchNode( makePuzzle( 10, 6 ))); // 4 / 3 = 1.33
  frontier.push_back( new SearchNode( makePuzzle( 10, 3 ))); // 7 / 3 = 2.33
  frontier.push_back( new SearchNode( makePuzzle( 10, 5 ))); // 5 / 3 = 1.66
  frontier.push_back( new SearchNode( makePuzzle( 10, 1 )));
  frontier.push_back( new SearchNode( makePuzzle( 10, 8 )));
  frontier.push_back( new SearchNode( makePuzzle( 10, 9 ))); // 1 / 3 = 0.33
  frontier.push_back( new SearchNode( makePuzzle( 10, 7 )));
  frontier.push_back( new SearchNode( makePuzzle( 10, 0 ))); // 10 / 3 = 3.33
  frontier.push_back( new SearchNode( makePuzzle( 10, 2 )));
  f_function *heuristic = new GreedyBestFirstHeuristic1();
  MinHeapComparator comp( heuristic );

  make_heap( frontier.begin(), frontier.end(), comp );

  for ( int i = 0; i < frontier.size(); i++ ) {
    cout << ( i + 1 ) << ": " << frontier[ i ]->getState()->m_score << " ("
         << (( *heuristic )( *( frontier[ i ]->getState()))) << ")" << endl;
  }

  for ( int j = 0; j < 8; ++j ) {

    cout << "Current Heap Val: " << frontier[ 0 ]->getState()->m_score << endl;
    pop_heap( frontier.begin(), frontier.end(), comp );
    frontier.pop_back();
    cout << "\nPop heap" << endl;

    for ( int i = 0; i < frontier.size(); i++ ) {
      cout << ( i + 1 ) << ": " << frontier[ i ]->getState()->m_score << " ("
           << (( *heuristic )( *( frontier[ i ]->getState()))) << ")" << endl;
    }

    cout << "\n\n";
  }

  delete comp.m_eval;

  /* Return pass */
  return 0;
}
