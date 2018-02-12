//
// Created by Grant Broadwater on 2/11/18.
//

#ifndef GLITTERBOMB_GREEDYBESTFIRSTSEARCH_H
#define GLITTERBOMB_GREEDYBESTFIRSTSEARCH_H

#include "Searcher.h"

class GreedyBestFirstSearch : public Searcher {

public:
    PuzzleSolution *search( Puzzle *puzzle ) const;

};


#endif //GLITTERBOMB_GREEDYBESTFIRSTSEARCH_H
