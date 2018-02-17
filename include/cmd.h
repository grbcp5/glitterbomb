//
// Created by Grant Broadwater on 2/6/18.
//

#ifndef GLITTERBOMB_CMD_H
#define GLITTERBOMB_CMD_H

#include <iostream>
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

#define ERR_CMD_FLAG (1u << 0)

#define TEST_CMD_FLAG (1u << 1)

#define BFS_CMD_FLAG (1u << 2)
#define ID_DFS_CMD_FLAG (1u << 3)
#define GBFGS_CMD_FLAG (1u << 4)
#define ASGS_CMD_FLAG (1u << 5)
#define SEARCH_CMD_FLAGS ( \
  BFS_CMD_FLAG \
  | ID_DFS_CMD_FLAG \
  | GBFGS_CMD_FLAG \
  | ASGS_CMD_FLAG \
)

#define BFS_NAME "Breadth First Search"
#define ID_DFS_NAME "Iterative Deepening Depth First Search"
#define GBFGS_NAME "Greedy Best First Graph Search"
#define ASGS_NAME "A* Graph Search"

extern "C" {
extern const char *DEFAULT_PUZZLE_FILE_NAMES[];
}

#define DEFAULT_SEARCH_ALGORITHM ID_DFS_CMD_FLAG

#define SHOW_DEFAULTS_CMD_FLAG (1u << 6)

#define TEST_ARG "--test"
#define SHOW_DEFAULTS_ARG "--showdefaults"
#define BFS_ARG_FULL "--breadthfirstsearch"
#define BFS_ARG_SHORT "--bfs"
#define IDDFS_ARG_FULL "--iterativedeepeningdepthfirstsearch"
#define IDDFS_ARG_SHORT "--iddfs"

/* Function Declarations ******************************************************/

CmdArgs *getCommandLineArguments( const int argc, const char **argv );

std::ostream &showDefaultsArguments( std::ostream &out = std::cout );

#endif //GLITTERBOMB_CMD_H
