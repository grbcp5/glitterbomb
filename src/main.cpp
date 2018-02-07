#include <iostream>
#include <fstream>
#include <cstring>

#include "ZTest.h"
#include "LegalMoveGenerator.h"
#include "BreadthFirstSearch.h"
#include "cmd.h"

using namespace std;

/* Constants ******************************************************************/


const char *DEFAULT_PUZZLE_FILE_NAME = "puzzle1.txt";


/* Function Declarations ******************************************************/

void printLine( const uint32 length = 80u, const char c = '*' );

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

  /* Local Variables */
  ifstream puzzleFileStream;
  Searcher *searcher = new BreadthFirstSearch();
  Puzzle *p;

  /* Greet User */
  printLine( 80u, '*' );
  cout << "*\n* Welcome to Glitterbomb.\n*\n"
       << "* A Mechanical Match artificial intelligence.\n*\n"
       << "* Assignment Document:\n*\t"
       << "http://web.mst.edu/~tauritzd/courses/cs5400/sp2018/puzzle.html\n*\n"
       << "* Repository:\n*\thttps://github.com/grbcp5/glitterbomb\n*\n";
  printLine( 80u, '*' );
  cout << endl;

  /* Branch to test environment */
  if ( getExecutionType( argc, argv ) == TEST ) {
    return ZTest::executeAllTests();
  }

  /* Get puzzle file */
  if ( argc > 1 ) {
    puzzleFileStream.open( argv[ 1 ] );

    cout << "Using program argument \"" << argv[ 1 ] << "\" as puzzle file."
         << endl;

  } else {
    puzzleFileStream.open( DEFAULT_PUZZLE_FILE_NAME );

    cout << "Using default value \"" << DEFAULT_PUZZLE_FILE_NAME
         << "\" as puzzle file." << endl;
  }

  /* Check valid file */
  if ( !puzzleFileStream.good()) {
    cout << "Error, invalid puzzle file." << endl;
    return 1;
  }

  /* Construct puzzle */
  cout << "Reading in puzzle from file." << endl;
  p = Puzzle::construct( puzzleFileStream );
  cout << "Puzzle file read successfully." << endl;
  puzzleFileStream.close();

  /* Execute search */
  cout << "Beginning search." << endl;
  clock_t begin = clock();
  PuzzleSolution *sol = searcher->search( p );
  clock_t end = clock();
  double elapsed_secs = double( end - begin ) / CLOCKS_PER_SEC;
  cout << "Search completed.\n" << endl;

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

  /* Delete dynamic memory */
  delete p;
  delete sol;
  delete searcher;

  return 0;
}


/* Function Definitions *******************************************************/


void printLine( const uint32 length, const char c ) {

  for ( uint32 i = 0; i < length; i++ ) {
    cout << c;
  }
  cout << endl;

  return;
}
