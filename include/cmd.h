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
    uint32 numFiles;
    const char **puzzleFileNames;
    const char **solutionFileNames;

    CmdArgs() :
        flags( 0 ),
        numFiles( 0 ),
        puzzleFileNames( NULL ),
        solutionFileNames( NULL ) {}

    ~CmdArgs() {
      if ( puzzleFileNames != NULL ) {

        for ( int i = 0; i < numFiles; ++i ) {
          delete[] puzzleFileNames[ i ];
          delete[] solutionFileNames[ i ];
        }

        delete[] puzzleFileNames;
        delete[] solutionFileNames;
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

#define DEFAULT_SEARCH_ALGORITHM ASGS_CMD_FLAG

#define SHOW_DEFAULTS_CMD_FLAG (1u << 6)
#define SHOW_HELP_CMD_FLAG (1u << 7)

#define PUZZLE_LIST_ARG "-p"
#define SOLUTION_LIST_ARG "-s"
#define TEST_ARG "--test"
#define SHOW_DEFAULTS_ARG "--showdefaults"
#define SHOW_HELP_ARG "--help"
#define BFS_ARG_FULL "--breadthfirstsearch"
#define BFS_ARG_SHORT "--bfs"
#define IDDFS_ARG_FULL "--iterativedeepeningdepthfirstsearch"
#define IDDFS_ARG_SHORT "--iddfs"
#define GBFGS_ARG_FULL "--greedybestfirstgraphsearch"
#define GBFGS_ARG_SHORT "--gbfgs"
#define ASGS_ARG_FULL "--a*graphsearch"
#define ASGS_ARG_SHORT "--a*gs"

/* Function Declarations ******************************************************/

CmdArgs *getCommandLineArguments( const int argc, const char **argv );

std::ostream &showDefaultsArguments( std::ostream &out = std::cout );

void displayHelp();

#endif //GLITTERBOMB_CMD_H
