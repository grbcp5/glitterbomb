//
// Created by Grant Broadwater on 2/20/18.
//

#ifndef ASSIGNMENT3_ASTARGRAPHSEARCH_H
#define ASSIGNMENT3_ASTARGRAPHSEARCH_H

#include "Searcher.h"

class AStarF : public f_function {
public:
    double operator()( const Puzzle &p ) const;
};

class AStarGraphSearch : public Searcher {

public:
    PuzzleSolution *search( Puzzle *puzzle ) const;

};


#endif //ASSIGNMENT3_ASTARGRAPHSEARCH_H
