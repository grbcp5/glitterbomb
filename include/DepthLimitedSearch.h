//
// Created by Grant Broadwater on 2/7/18.
//

#ifndef GLITTERBOMB_ID_DEPTHFIRSTSEARCH_H
#define GLITTERBOMB_ID_DEPTHFIRSTSEARCH_H

#include "Searcher.h"

class DepthLimitedSearch : public Searcher {
private:
    const uint32 m_max_depth;

public:

    DepthLimitedSearch( const uint32 max_depth );

    PuzzleSolution *search( Puzzle *puzzle ) const;

};


#endif //GLITTERBOMB_ID_DEPTHFIRSTSEARCH_H
