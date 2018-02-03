//
// Created by Grant Broadwater on 2/3/18.
//

#ifndef GLITTERBOMB_SEARCHER_H
#define GLITTERBOMB_SEARCHER_H

#include <vector>

#include "types.h"
#include "Puzzle.h"

struct PuzzleSolution {

    const Puzzle *initialState;
    uint32 numMovesToSolution;
    const Move *moves;

    /* Default Constructor */
    PuzzleSolution();

    /* De-constructor */
    ~PuzzleSolution();
};

class Searcher {

private:

public:

    virtual PuzzleSolution *search( Puzzle *puzzle ) const = 0;

};


#endif //GLITTERBOMB_SEARCHER_H
