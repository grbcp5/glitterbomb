#include <iostream>
#include <fstream>
#include <cstring>
#include <cmd.h>
#include <ctime>

#include "ZTest.h"
#include "LegalMoveGenerator.h"
#include "BreadthFirstSearch.h"
#include "ID_DepthLimitedSearch.h"
#include "GreedyBestFirstGraphSearch.h"
#include "AStarGraphSearch.h"
#include "cmd.h"
#include "GlitterbombConstants.h"

using namespace std;

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
  ofstream solutionFileStream;
  string solutionFileName;
  CmdArgs *cmdArgs;
  Searcher *searcher;
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

  /* Get command line arguments */
  cmdArgs = getCommandLineArguments( argc, argv );

  /* Error Reading in Args */
  if ( cmdArgs->flags & ERR_CMD_FLAG) {
    cout << "Error reading in the command line arguments." << endl;
    cout << "Use ./glitterbomb --help for help on using glitterbomb." << endl;

    delete cmdArgs;

    cout << "\nGlitterbomb terminating." << endl;
    printLine();
    return 0;
  }

  /* User requested help */
  if ( cmdArgs->flags & SHOW_HELP_CMD_FLAG) {

    displayHelp();

    delete cmdArgs;

    cout << "\nGlitterbomb terminating." << endl;
    printLine();
    return 0;
  }

  /* Branch for testing procedure */
  if ( cmdArgs->flags & TEST_CMD_FLAG) {

    int ret_val = ZTest::executeAllTests();

    delete cmdArgs;

    cout << "\nGlitterbomb terminating." << endl;
    printLine();
    return ret_val;
  }

  /* Branch for show defaults */
  if ( cmdArgs->flags & SHOW_DEFAULTS_CMD_FLAG) {

    showDefaultsArguments();

    delete cmdArgs;

    cout << "\nGlitterbomb terminating." << endl;
    printLine();
    return 0;
  }

  /* For each puzzle file */
  for ( int q = 0; q < cmdArgs->numFiles; ++q ) {

    cout << "----- Puzzle file " << ( q + 1 ) << " -----" << endl;

    /* Get puzzle file */
    puzzleFileStream.open( cmdArgs->puzzleFileNames[ q ] );
    cout << "Using \"" << cmdArgs->puzzleFileNames[ q ] << "\" as puzzle file."
         << endl;

    /* Check valid file */
    if ( !puzzleFileStream.good()) {
      cout << "Error, invalid puzzle file." << endl;
      continue;
    }

    /* Construct puzzle */
    cout << "Reading in puzzle from file." << endl;
    p = Puzzle::construct( puzzleFileStream );
    cout << "Puzzle file read successfully." << endl;
    puzzleFileStream.close();

    /* Initialize searcher */
    if ( cmdArgs->flags & BFS_CMD_FLAG) {

      /* Breadth First Search */
      cout << "Using " << BFS_NAME << " algorithm." << endl;
      searcher = new BreadthFirstSearch();

    } else if ( cmdArgs->flags & ID_DFS_CMD_FLAG) {

      /* Iterative Deepening Depth First Search */
      cout << "Using " << ID_DFS_NAME << " algorithm." << endl;
      searcher = new ID_DepthLimitedSearch();

    } else if ( cmdArgs->flags & GBFGS_CMD_FLAG) {

      cout << "Using " << GBFGS_NAME << " algorithm." << endl;
      searcher = new GreedyBestFirstGraphSearch();

    } else if ( cmdArgs->flags & ASGS_CMD_FLAG) {

      cout << "Using " << ASGS_NAME << " algorithm." << endl;
      searcher = new AStarGraphSearch();

    } else {

      /* Default */
      cout << "Using Breadth First Search algorithm." << endl;
      searcher = new BreadthFirstSearch();
    }

    /* Execute search */
    cout << "Beginning search." << endl;
    clock_t begin = clock();
    PuzzleSolution *sol = searcher->search( p );
    clock_t end = clock();
    double elapsed_secs = double( end - begin ) / CLOCKS_PER_SEC;
    cout << "Search completed." << endl;

    /* Construct output stream */
    solutionFileName = string( cmdArgs->solutionFileNames[ q ] );
    cout << "Using \"" << solutionFileName << "\" as solution file." << endl;
    solutionFileStream.open( solutionFileName.c_str());

    cout << endl;

    /* If solution was found */
    if ( sol->solutionExists ) {

#if SHOW_STEPS

      Puzzle *pcopy = new Puzzle( *p );

      for( int i = 0; i < sol->numMovesToSolution; i++ ) {

        Move *m = new Move(
            sol->moves[ i ]
        );

        resultingPointsFromMove(
            p,
            m->from,
            sol->moves[ i ].from.col == sol->moves[ i ].to.col ? DOWN : RIGHT,
            m->matchedDevices
        );

        pcopy->makeMove( *m, true );
      }

      delete ( pcopy );

#endif

      /* Print solution to standard output */
      p->printFile();
      p->printFile( solutionFileStream );
      for ( uint32 i = 0; i < sol->numMovesToSolution; ++i ) {
        cout << sol->moves[ i ] << endl;
        solutionFileStream << sol->moves[ i ] << endl;
      }

      /* Print elapsed time to standard output */
      cout << elapsed_secs << endl;
      solutionFileStream << elapsed_secs << endl;

    } else {

      /* Indicate no solution found */
      cout << "Solution not found" << endl;
      solutionFileStream << "Solution not found" << endl;

    }

#if COUNT_TOTAL_NODES_EXPANDED
    cout << "\nTotal Nodes Expanded: "
         << sol->totalNodesExpanded << endl
         << "Solution Depth: "
         << sol->numMovesToSolution << endl << endl;
    solutionFileStream << "\nTotal Nodes Expanded: "
                       << sol->totalNodesExpanded << endl
                       << "Solution Depth: "
                       << sol->numMovesToSolution;
#endif

    cout << "\n\n" << endl;
    solutionFileStream.close();

    /* Delete dynamic memory */
    delete p;
    delete sol;
    delete searcher;

  }

  delete cmdArgs;

  cout << "\nGlitterbomb terminating." << endl;
  printLine();
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
