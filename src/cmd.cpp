/******************************************************************************
 *
 * File:
 *   cmd
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   glitterbomb
 *
 ******************************************************************************/

#include "cmd.h"

#include <cstring>

const char *DEFAULT_PUZZLE_FILE_NAMES[] = {
    "puzzle1.txt",
    "puzzle2.txt",
    "puzzle3.txt"
};

const uint32 NUM_DEFAULT_PUZZLE_FILES = 3;

CmdArgs *getCommandLineArguments( const int argc, const char **argv ) {

  /* Local variables */
  CmdArgs *result = new CmdArgs();
  size_t arg_len;
  char *arg;
  bool argHandled;
  std::vector< char * > puzzleFiles;
  std::vector< char * > solutionFiles;
  size_t newFileLength;
  char *newFile;
  std::string solutionFileName;
  bool inPuzzleFileList = false;
  bool inSolutionFileList = false;

  /* Loop over each argument */
  for ( uint32 i = 1; i < argc; ++i ) {

    /* Initialize  */
    argHandled = false;
    arg_len = strlen( argv[ i ] );
    arg = new char[arg_len + 1];
    strcpy( arg, argv[ i ] );
    for ( int c = 0; c < strlen( argv[ i ] ); ++c ) {
      /* Make each char lower case */
      arg[ c ] = ( char ) tolower( argv[ i ][ c ] );
    }

    /* If test flag not already set */
    if ( !( result->flags & TEST_CMD_FLAG)) {

      /* Check if arg equals test arg */
      if ( strcmp( arg, TEST_ARG ) == 0 ) {

        /* Mark test command line arg */
        result->flags |= TEST_CMD_FLAG;

        /* Mark arg already handled */
        inPuzzleFileList = false;
        inSolutionFileList = false;
        argHandled = true;
      }
    }

    /* Handle show defaults flag */
    if ( !argHandled && !( result->flags & SHOW_DEFAULTS_CMD_FLAG)) {

      /* Check for flag */
      if ( strcmp( arg, SHOW_DEFAULTS_ARG ) == 0 ) {

        /* Mark flag */
        result->flags |= SHOW_DEFAULTS_CMD_FLAG;
        inPuzzleFileList = false;
        inSolutionFileList = false;
        argHandled = true;
      }

    }

    /* If search flag has not yet been set */
    if ( !argHandled && !( result->flags & SEARCH_CMD_FLAGS)) {

      /* Check for Breadth First Search */
      if ( strcmp( arg, BFS_ARG_FULL ) == 0 ||
           strcmp( arg, BFS_ARG_SHORT ) == 0 ) {

        /* Mark BFS Flag */
        result->flags |= BFS_CMD_FLAG;
        inPuzzleFileList = false;
        inSolutionFileList = false;
        argHandled = true;

        /* Check for Iterative Deepening Depth First Search */
      } else if ( strcmp( arg, IDDFS_ARG_FULL ) == 0 ||
                  strcmp( arg, IDDFS_ARG_SHORT ) == 0 ) {

        result->flags |= ID_DFS_CMD_FLAG;
        inPuzzleFileList = false;
        inSolutionFileList = false;
        argHandled = true;

        /* Check for Greedy Best First Graph Search */
      } else if ( strcmp( arg, GBFGS_ARG_FULL ) == 0 ||
                  strcmp( arg, GBFGS_ARG_SHORT ) == 0 ) {

        result->flags |= GBFGS_CMD_FLAG;
        inPuzzleFileList = false;
        inSolutionFileList = false;
        argHandled = true;

        /* Check for A* */
      } else if ( strcmp( arg, ASGS_ARG_FULL ) == 0 ||
                  strcmp( arg, ASGS_ARG_SHORT ) == 0 ) {

        result->flags |= ASGS_CMD_FLAG;
        inPuzzleFileList = false;
        inSolutionFileList = false;
        argHandled = true;
      }
    }

    /* Check for start puzzle list arg */
    if ( !argHandled && strcmp( arg, PUZZLE_LIST_ARG ) == 0 ) {

      argHandled = true;
      inPuzzleFileList = true;
      inSolutionFileList = false;
    }


    /* Check for start solution list arg */
    if ( !argHandled && strcmp( arg, SOLUTION_LIST_ARG ) == 0 ) {

      argHandled = true;
      inPuzzleFileList = false;
      inSolutionFileList = true;
    }

    /* Check for help flag */
    if ( !argHandled && strcmp( arg, SHOW_HELP_ARG ) == 0 ) {

      result->flags |= SHOW_HELP_CMD_FLAG;
      argHandled = true;
      inPuzzleFileList = false;
      inSolutionFileList = false;
    }

    if ( !argHandled ) {

      /* Check if expecting puzzle file */
      if ( inPuzzleFileList ) {

        /* Add it to list of puzzle files */
        newFileLength = strlen( arg ) + 1;
        newFile = new char[newFileLength]; // Allocate new memory
        strcpy( newFile, arg );                    // Copy arg into memory

        /* Check to make sure not an argument */
        if ( newFileLength > 2 && newFile[ 0 ] == '-'
             && newFile[ 0 ] == newFile[ 1 ] ) {

          result->flags |= ERR_CMD_FLAG;
          delete[] newFile;
          return result;

        } else {

          puzzleFiles.push_back( newFile ); // Add to vector

        }

        /* Check if expecting solution file */
      } else if ( inSolutionFileList ) {

        /* Add it to list of solution files */
        newFileLength = strlen( arg ) + 1;
        newFile = new char[newFileLength]; // Allocate new memory
        strcpy( newFile, arg );            // Copy arg into memory

        /* Check to make sure not an argument */
        if ( newFileLength > 2 && newFile[ 0 ] == '-'
             && newFile[ 0 ] == newFile[ 1 ] ) {

          result->flags |= ERR_CMD_FLAG;
          delete[] newFile;
          return result;

        } else {

          solutionFiles.push_back( newFile ); // Add to vector

        }

        /* If not reading in list of strings */
      } else {
        result->flags |= ERR_CMD_FLAG;
        return result;
      }

    }

    /* Deallocate dynamic memory */
    delete[] arg;

  }

  /* Check for at least one search algorithm */
  if ( !( result->flags & SEARCH_CMD_FLAGS)) {
    result->flags |= DEFAULT_SEARCH_ALGORITHM;
  }

  /* Put in default puzzle files */
  if ( puzzleFiles.empty()) {

    /* For each default puzzle file */
    for ( int i = 0; i < NUM_DEFAULT_PUZZLE_FILES; ++i ) {

      /* Create new memory */
      newFile = new char[strlen( DEFAULT_PUZZLE_FILE_NAMES[ i ] ) + 1];
      strcpy( newFile, DEFAULT_PUZZLE_FILE_NAMES[ i ] );

      /* Add default to puzzle files */
      puzzleFiles.push_back( newFile );
    }
  }

  /* Use default solution files */
  if ( solutionFiles.empty()) {

    /* For each default puzzle file */
    for ( int i = 0; i < puzzleFiles.size(); ++i ) {

      /* Create new memory */
      newFile = new char[strlen( "solution***.txt" ) + 1];
      solutionFileName = std::string( "solution" ) +
                         (( char ) ( '1' + ( char ) i )) +
                         std::string( ".txt" );
      strcpy( newFile, solutionFileName.c_str());

      /* Add default to puzzle files */
      solutionFiles.push_back( newFile );
    }
  } else if ( solutionFiles.size() != puzzleFiles.size()) {
    result->flags |= ERR_CMD_FLAG;
    return result;
  }

  /* Copy all puzzle and solution files */
  result->puzzleFileNames = new const char *[puzzleFiles.size()];
  result->solutionFileNames = new const char *[solutionFiles.size()];
  for ( int i = 0; i < puzzleFiles.size(); ++i ) {
    result->puzzleFileNames[ i ] = puzzleFiles[ i ];
    result->solutionFileNames[ i ] = solutionFiles[ i ];
    result->numFiles++;
  }

  return result;
}

std::ostream &showDefaultsArguments( std::ostream &out ) {

  /* Show default search algorithm */
  out << "Default Search Algorithm:\n\t";

  if ( DEFAULT_SEARCH_ALGORITHM & BFS_CMD_FLAG) {
    out << BFS_NAME << std::endl;
  } else if ( DEFAULT_SEARCH_ALGORITHM & ID_DFS_CMD_FLAG) {
    out << ID_DFS_NAME << std::endl;
  } else if ( DEFAULT_SEARCH_ALGORITHM & GBFGS_CMD_FLAG) {
    out << GBFGS_NAME << std::endl;
  } else if ( DEFAULT_SEARCH_ALGORITHM & ASGS_CMD_FLAG) {
    out << ASGS_NAME << std::endl;
  }

  /* Show Puzzle Files */
  out << "Default Puzzle Files:\n";
  for ( int i = 0; i < NUM_DEFAULT_PUZZLE_FILES; ++i ) {
    out << "\t" << DEFAULT_PUZZLE_FILE_NAMES[ i ] << std::endl;
  }

  return out;
}

void displayHelp() {

  using namespace std;

  cout << "Available Arguments:" << endl

       << "\n\tFile Lists:" << endl
       << "\t\t-p: Begin list of puzzle files." << endl
       << "\t\t-s: Begin list of solution files." << endl
       << "\n\tPuzzle and solution file lists must be equal length." << endl

       << "\n\tSearch Algorithms:" << endl
       << "\t\t--breadthFirstSearch (-bfs)." << endl
       << "\t\t--iterativeDeepeningDepthFirstSearch (-iddfs)." << endl
       << "\t\t--greedyBestFirstGraphSearch (-gbfgs)." << endl

       << "\n\tOther Arguments" << endl
       << "\t\t--test: Run test protocol." << endl
       << "\t\t--help: Display this help message." << endl
       << "\t\t--showDefaults: Show default values." << endl

       << "\nExamples:"

       << "\n\t./glitterbomb --bfs" << endl
       << "\t\tRun breadth first search on all default puzzle files " << endl
       << "\t\tand use the default solution files." << endl

       << "\n\t./glitterbomb -p p1.txt p2.txt" << endl
       << "\t\tRun the default search algorithm on \"p1.txt\" and \"p2.txt\""
       << "\n\t\tand use the default solution files." << endl

       << "\n\t./glitterbomb -p puzzle1.txt -s sol1.txt" << endl
       << "\t\tRun the default search algorithm on \"puzzle1.txt\"" << endl
       << "\t\tand output the solution to \"sol1.txt\"." << endl

       << endl;

}

