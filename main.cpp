#include <iostream>

#include "ZTest.h"
#include "LegalMoveGenerator.h"
#include "BreadthFirstSearch.h"

using namespace std;

/* Local Enumerations *********************************************************/


enum ExecutionType {
    TEST = 0,
    RUN = 1
};


/* Constants ******************************************************************/


const char *DEFAULT_PUZZLE_FILE_NAME = "puzzle1.txt";


/* Function Declarations ******************************************************/


ExecutionType getExecutionType( const int argc, const char **argv );


/**
 * Function:
 *   main
 *
 * Description:
 *   Entry point to program
 *
 * @param argc count of command line arguments
 * @param argv value of command line arguments
 * @return status of execution
 */

int main( const int argc, const char **argv ) {

  /* Branch to test environment */
  if ( getExecutionType( argc, argv ) == TEST ) {
    return ZTest::executeAllTests();
  }

  /* Local Variables */
  Searcher *bfs = new BreadthFirstSearch();
  Puzzle *p;

  /* Get puzzle file */
  if ( argc > 1 ) {
    p = Puzzle::construct( argv[ 1 ] );
  } else {
    p = Puzzle::construct( DEFAULT_PUZZLE_FILE_NAME );
  }

  /* Execute search */
  clock_t begin = clock();
  PuzzleSolution *sol = bfs->search( p );
  clock_t end = clock();
  double elapsed_secs = double( end - begin ) / CLOCKS_PER_SEC;

  /* If solution was found */
  if ( sol->solutionExists ) {

    /* Print solution to standard output */
    p->printFile();
    for ( uint32 i = 0; i < sol->numMovesToSolution; ++i ) {
      cout << sol->moves[ i ] << endl;
    }

    /* Print elapsed time to standard output */
    cout << elapsed_secs << endl;

  } else {

    /* Indicate no solution found */
    cout << "Solution not found" << endl;
  }

  return 0;
}


/* Function Definitions *******************************************************/


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
