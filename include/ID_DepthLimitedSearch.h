//
// Created by Grant Broadwater on 2/10/18.
//

#ifndef GLITTERBOMB_ID_DEPTHLIMITEDSEARCH_H
#define GLITTERBOMB_ID_DEPTHLIMITEDSEARCH_H

#include "Searcher.h"

class ID_DepthLimitedSearch : public Searcher {

public:
    PuzzleSolution *search( Puzzle *puzzle ) const;

};


#endif //GLITTERBOMB_ID_DEPTHLIMITEDSEARCH_H
