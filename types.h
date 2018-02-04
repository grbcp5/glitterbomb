/******************************************************************************
 *
 * File:
 *   types
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   glitterbomb
 *
 ******************************************************************************/

#ifndef GLITTERBOMB_TYPES_H
#define GLITTERBOMB_TYPES_H

#include <vector>

typedef unsigned int uint32;
typedef unsigned char uint8;

enum Direction {
    DIR_MIN = 0,
    UP = DIR_MIN,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
};

struct Point {
    uint32 row;
    uint32 col;

    Point() : row( 0 ), col( 0 ) {}

    Point( const uint32 r, const uint32 c ) : row( r ), col( c ) {}

    Point( const Point &cpy )
        : row( cpy.row ),
          col( cpy.col ) {}
};

struct Move {
    const Point from;
    const Point to;
    const uint32 resultingMatches;
    std::vector< Point > *const matchedDevices;

    Move( Point f, Point t, uint32 points ) :
        from( f ),
        to( t ),
        resultingMatches( points ),
        matchedDevices( new std::vector< Point >()) {}

    Move( Point f, Point t, uint32 points, std::vector< Point > *locations ) :
        from( f ),
        to( t ),
        resultingMatches( points ),
        matchedDevices( locations ) {}

    ~Move() {
      if ( matchedDevices != NULL ) {
        delete matchedDevices;
      }
    }
};

#endif //GLITTERBOMB_TYPES_H
