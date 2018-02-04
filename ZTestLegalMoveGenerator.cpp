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

using namespace std;

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

      if ( curMove->matchedDevices != NULL ) {
        for ( uint32 d = 0; d < curMove->matchedDevices->size(); ++d ) {
          cout << "\t"
               << "(r:" << curMove->matchedDevices->at( d ).row << ",c:"
               << curMove->matchedDevices->at( d ).col << ")" << endl;
        }
      }

      if ( curMove->resultingMatches > curMove->matchedDevices->size()) {
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        return testID;
      }

      puzzleCopy = new Puzzle( *puzzle );
      puzzleCopy->makeMove( *curMove );

      cout << ( *puzzleCopy ) << endl;

      delete puzzleCopy;

      curMove->matchedDevices->clear();
      delete curMove;
    }

    /* Delete dynamic memory */
    delete puzzle;
    delete ret_val;

  }

  /* Return pass */
  return 0;
}
