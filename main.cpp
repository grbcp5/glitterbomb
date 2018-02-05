#include <iostream>
#include <cstring>

#include "ZTest.h"
#include "LegalMoveGenerator.h"
#include "BreadthFirstSearch.h"

using namespace std;

enum ExecutionType {
    TEST = 0,
    RUN = 1
};

const char *PUZZLE_FILE_NAME = "puzzle1.txt";

ExecutionType getExecutionType( const int argc, const char **argv );


int main( const int argc, const char **argv ) {

  if ( getExecutionType( argc, argv ) == TEST ) {
    return ZTest::executeAllTests();
  }

  /* Local Variables */
  Searcher *bfs = new BreadthFirstSearch();
  Puzzle *p = Puzzle::construct( PUZZLE_FILE_NAME );

  clock_t begin = clock();
  PuzzleSolution *sol = bfs->search( p );
  clock_t end = clock();
  double elapsed_secs = double( end - begin ) / CLOCKS_PER_SEC;

  if ( sol->solutionExists ) {

    p->printFile();

    for ( uint32 i = 0; i < sol->numMovesToSolution; ++i ) {
      cout << sol->moves[ i ] << endl;
    }

    cout << elapsed_secs << endl;

  } else {
    cout << "Solution not found" << endl;
  }

  return 0;
}


ExecutionType getExecutionType( const int argc, const char **argv ) {

  /* Local variables */
  char *firstParameter;

  /* Default to RUN */
  if ( argc == 1 ) {
    return RUN;
  }

  /* Initialize */
  firstParameter = new char[strlen( argv[ 1 ] ) + 1];
  strcpy( firstParameter, argv[ 1 ] );

  /* Convert first parameter to lower case */
  for ( uint32 i = 0; i < strlen( firstParameter ); ++i ) {
    firstParameter[ i ] = ( char ) tolower( firstParameter[ i ] );
  }

  /* Check for test parameter */
  if ( strcmp( firstParameter, "test" ) == 0 ) {
    delete[] firstParameter;
    return TEST;
  }

  delete firstParameter;

  /* Default to RUN */
  return RUN;
}
