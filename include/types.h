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

#include <iostream>
#include <vector>
#include <cstddef>

typedef unsigned int uint32;
typedef unsigned char uint8;

enum Direction {
    DIR_MIN = 0,
    UP = DIR_MIN,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

struct Point {
    uint32 row;
    uint32 col;

    Point() : row( 0 ), col( 0 ) {}

    Point( const uint32 r, const uint32 c ) : row( r ), col( c ) {}

    Point( const Point &cpy )
        : row( cpy.row ),
          col( cpy.col ) {}

    bool operator==( const Point &rhs ) {
      return row == rhs.row && col == rhs.col;
    }

};

inline std::ostream &operator<<( std::ostream &o, const Point &p ) {
  o << "(" << p.col << "," << p.row << ")";
  return o;
}

struct Move {
    Point from;
    Point to;
    uint32 resultingMatches;
    std::vector< Point > *matchedDevices;

    Move() :
        from(),
        to(),
        resultingMatches( 0 ),
        matchedDevices( NULL ) {
   
      matchedDevices = new std::vector< Point >(); 
    }

    Move( Point f, Point t, uint32 points ) :
        from( f ),
        to( t ),
        resultingMatches( points ),
        matchedDevices( NULL ) {
    
      matchedDevices = new std::vector< Point >();
    }

    Move( Point f, Point t, uint32 points, std::vector< Point > *locations ) :
        from( f ),
        to( t ),
        resultingMatches( points ),
        matchedDevices( NULL ) {
        
      matchedDevices = new std::vector< Point >();

      for( uint32 i = 0; i < locations->size(); i++ ) {
        matchedDevices->push_back( locations->at( i ));
      }

    }

    Move( const Move &cpy ) :
        from( cpy.from ),
        to( cpy.to ),
        resultingMatches( cpy.resultingMatches ),
        matchedDevices( NULL ) {

      matchedDevices = new std::vector< Point >();

      if ( cpy.matchedDevices != NULL ) {
        for ( uint32 i = 0; i < cpy.matchedDevices->size(); ++i ) {
          matchedDevices->push_back( cpy.matchedDevices->at( i ));
        }
      }
    }

   const Move &operator=( const Move &rhs ) {
     
     from = rhs.from;
     to = rhs.to;
     resultingMatches = rhs.resultingMatches;

     matchedDevices->clear();
     for( uint32 i = 0; i < rhs.matchedDevices->size(); i++ ) {
       matchedDevices->push_back( rhs.matchedDevices->at( i ));
     }

     return ( *this );
   }

    ~Move() {
      if ( matchedDevices != NULL ) {
        matchedDevices->clear();
        delete matchedDevices;
      }
    }
};

inline std::ostream &operator<<( std::ostream &o, const Move &m ) {
  o << m.from << "," << m.to;

  return o;
}

#endif //GLITTERBOMB_TYPES_H
