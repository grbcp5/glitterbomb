//
// Created by Grant Broadwater on 2/17/18.
//

#ifndef ASSIGNMENT3_GREEDYBESTFIRSTGRAPHSEARCH_H
#define ASSIGNMENT3_GREEDYBESTFIRSTGRAPHSEARCH_H

#include <vector>

#include "Searcher.h"
#include "Puzzle.h"

class GreedyBestFirstHeuristic1 : public f_function {
public:
    double operator()( const Puzzle &p ) const;
};

class GreedyBestFirstHeuristic2 : public f_function {
public:
    double operator()( const Puzzle &p ) const;
};

class GreedyBestFirstGraphSearch : public Searcher {
private:

    SearchNode *findNodeWithPuzzle(
        const std::vector< SearchNode * > &nodes,
        Puzzle *p
    );

    bool contains(
        const std::vector< SearchNode * > &nodes,
        Puzzle *p
    );

public:

    PuzzleSolution *search( Puzzle *puzzle ) const;
};


#endif //ASSIGNMENT3_GREEDYBESTFIRSTGRAPHSEARCH_H
