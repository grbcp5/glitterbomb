//
// Created by Grant Broadwater on 2/3/18.
//

#ifndef GLITTERBOMB_BREADTHFIRSTSEARCH_H
#define GLITTERBOMB_BREADTHFIRSTSEARCH_H

#include "Searcher.h"

class BreadthFirstSearch : public Searcher {

private:

public:

    PuzzleSolution *search( Puzzle *puzzle ) const;

};


#endif //GLITTERBOMB_BREADTHFIRSTSEARCH_H
