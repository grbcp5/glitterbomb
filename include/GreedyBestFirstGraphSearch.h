//
// Created by Grant Broadwater on 2/17/18.
//

#ifndef ASSIGNMENT3_GREEDYBESTFIRSTGRAPHSEARCH_H
#define ASSIGNMENT3_GREEDYBESTFIRSTGRAPHSEARCH_H

#include "Searcher.h"

class GreedyBestFirstGraphSearch : public Searcher {
public:
    PuzzleSolution *search( Puzzle *puzzle ) const;
};


#endif //ASSIGNMENT3_GREEDYBESTFIRSTGRAPHSEARCH_H
