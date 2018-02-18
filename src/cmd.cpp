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
  size_t newPuzzleFileLength;
  char *newPuzzleFile;
  char *newSolutionFile;
  std::string solutionFileName;
  bool inPuzzleFileList = false;

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
        argHandled = true;

        /* Check for Iterative Deepening Depth First Search */
      } else if ( strcmp( arg, IDDFS_ARG_FULL ) == 0 ||
                  strcmp( arg, IDDFS_ARG_SHORT ) == 0 ) {

        result->flags |= ID_DFS_CMD_FLAG;
        inPuzzleFileList = false;
        argHandled = true;

        /* Check for Greedy Best First Graph Search */
      } else if ( strcmp( arg, GBFGS_ARG_FULL ) == 0 ||
                  strcmp( arg, GBFGS_ARG_SHORT ) == 0 ) {

        result->flags |= GBFGS_CMD_FLAG;
        inPuzzleFileList = false;
        argHandled = true;

      }
    }

    /* Check for start puzzle list arg */
    if ( !argHandled && strcmp( arg, PUZZLE_LIST_ARG ) == 0 ) {

      argHandled = true;
      inPuzzleFileList = true;
    }

    if ( !argHandled ) {

      /* Check if expecting puzzle file */
      if ( inPuzzleFileList ) {

        /* Add it to list of puzzle files */
        newPuzzleFileLength = strlen( arg ) + 1;
        newPuzzleFile = new char[newPuzzleFileLength]; // Allocate new memory
        strcpy( newPuzzleFile, arg );                    // Copy arg into memory

        /* Check to make sure not an argument */
        if ( newPuzzleFileLength > 2 && newPuzzleFile[ 0 ] == '-'
             && newPuzzleFile[ 0 ] == newPuzzleFile[ 1 ] ) {

          result->flags |= ERR_CMD_FLAG;
          delete[] newPuzzleFile;

        } else {

          puzzleFiles.push_back( newPuzzleFile ); // Add to vector

        }

        /* If not reading in list of strings */
      } else {
        result->flags |= ERR_CMD_FLAG;
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
      newPuzzleFile = new char[strlen( DEFAULT_PUZZLE_FILE_NAMES[ i ] ) + 1];
      strcpy( newPuzzleFile, DEFAULT_PUZZLE_FILE_NAMES[ i ] );

      /* Add default to puzzle files */
      puzzleFiles.push_back( newPuzzleFile );
    }
  }

  /* Use default solution files */
  if ( solutionFiles.empty()) {

    /* For each default puzzle file */
    for ( int i = 0; i < puzzleFiles.size(); ++i ) {

      /* Create new memory */
      newSolutionFile = new char[strlen( "solution***.txt" ) + 1];
      solutionFileName = std::string( "solution" ) +
                         (( char ) ( '1' + ( char ) i )) +
                         std::string( ".txt" );
      strcpy( newSolutionFile, solutionFileName.c_str());

      /* Add default to puzzle files */
      solutionFiles.push_back( newSolutionFile );
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

