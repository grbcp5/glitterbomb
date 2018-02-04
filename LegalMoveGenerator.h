//
// Created by Grant Broadwater on 1/25/18.
//

#ifndef GLITTERBOMB_LEGALMOVEGENERATOR_H
#define GLITTERBOMB_LEGALMOVEGENERATOR_H

#include <vector>
#include "Puzzle.h"

std::vector< Move * > *getLegalMoves( const Puzzle *p );

#endif // GLITTERBOMB_LEGALMOVEGENERATOR_H
