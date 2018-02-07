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

CmdArgs *getCommandLineArguments( const int argc, const char **argv ) {

  /* Local variables */
  CmdArgs *result = new CmdArgs();
  size_t arg_len;
  char *arg;
  bool argHandled;
  std::vector< char * > puzzleFiles;
  char *newPuzzleFile;

  /* Loop over each argument */
  for ( uint32 i = 1; i < argc; ++i ) {

    /* Initialize  */
    argHandled = false;
    arg_len = strlen( argv[ i ] );
    arg = new char[arg_len + 1];
    for ( int c = 0; c < strlen( argv[ i ] ); ++c ) {
      /* Make each char lower case */
      arg[ c ] = ( char ) tolower( argv[ i ][ c ] );
    }

    /* If test flag not already set */
    if ( !( result->flags & TEST_CMD_FLAG )) {

      /* Check if arg equals test arg */
      if ( strcmp( arg, "--test" ) == 0 ) {

        /* Mark test command line arg */
        result->flags |= TEST_CMD_FLAG;

        /* Mark arg already handled */
        argHandled = true;
      }
    }

    /* Check if file has already been set */
    if ( !argHandled ) {

      /* Add it to list of puzzle files */
      newPuzzleFile = new char[strlen( arg )]; // Allocate new memory
      strcpy( newPuzzleFile, arg );              // Copy arg into memory
      puzzleFiles.push_back( newPuzzleFile );    // Add to vector
      result->numPuzzleFiles++;                  // Increment count

    }

    /* Deallocate dynamic memory */
    delete arg;

  }

  /* Copy all puzzle files */
  if ( result->numPuzzleFiles > 0 ) {

    result->puzzleFileNames = new const char *[result->numPuzzleFiles];
    for ( int i = 0; i < puzzleFiles.size(); ++i ) {
      result->puzzleFileNames[ i ] = puzzleFiles[ i ];
    }

  } else {

    /* Create memory for default puzzle file */
    newPuzzleFile = new char[strlen( DEFAULT_PUZZLE_FILE_NAME )];
    strcpy( newPuzzleFile, DEFAULT_PUZZLE_FILE_NAME );

    /* Add default to cmd args */
    result->numPuzzleFiles = 1;
    result->puzzleFileNames = new const char *[result->numPuzzleFiles];
    result->puzzleFileNames[ 0 ] = newPuzzleFile;

  }

  return result;
}
