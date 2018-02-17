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

#define ERR_CMD_FLAG 1u

#define TEST_CMD_FLAG 2u

#define BFS_CMD_FLAG 4u
#define ID_DFS_CMD_FLAG 8u
#define SEARCH_CMD_FLAGS ( BFS_CMD_FLAG | ID_DFS_CMD_FLAG )

extern "C" {
extern const char *DEFAULT_PUZZLE_FILE_NAME[];
}

#define DEFAULT_SEARCH_ALGORITHM ID_DFS_CMD_FLAG

/* Function Declarations ******************************************************/

CmdArgs *getCommandLineArguments( const int argc, const char **argv );

#endif //GLITTERBOMB_CMD_H
