//
// Created by Grant Broadwater on 2/6/18.
//

#ifndef GLITTERBOMB_CMD_H
#define GLITTERBOMB_CMD_H

#include <vector>

#include "types.h"

/* Types **********************************************************************/

struct CmdArgs {
    uint32 flags;
    uint32 numPuzzleFiles;
    const char **puzzleFileNames;

    CmdArgs() :
        flags( 0 ),
        numPuzzleFiles( 0 ),
        puzzleFileNames( NULL ) {}

    ~CmdArgs() {
      if ( puzzleFileNames != NULL ) {

        for ( int i = 0; i < numPuzzleFiles; ++i ) {
          delete[] puzzleFileNames[ i ];
        }

        delete[] puzzleFileNames;
      }
    }
};

/* Constants ******************************************************************/

#define TEST_CMD_FLAG 1u

const char *DEFAULT_PUZZLE_FILE_NAME = "puzzle1.txt";

/* Function Declarations ******************************************************/

CmdArgs *getCommandLineArguments( const int argc, const char **argv );

#endif //GLITTERBOMB_CMD_H
