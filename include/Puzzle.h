//
// Created by Grant Broadwater on 1/23/18.
//

#ifndef GLITTERBOMB_PUZZLE_H
#define GLITTERBOMB_PUZZLE_H

#include <iostream>
#include <vector>

#include "types.h"

class Puzzle {

private:
    /* Private member variables ***********************************************/
    uint8 **m_grid;

    /* Private helper functions ***********************************************/
    void fallDown( const uint32 row, const uint32 col, const uint32 n );

public:
    static const uint8 NO_DEVICE = 0;

    /* Public Properties ******************************************************/
    uint32 m_score;
    uint32 m_swaps_used;

    /* Member Constants *******************************************************/
    const uint32 m_quota;
    const uint32 m_num_swaps;
    const uint32 m_num_device_types;
    const uint32 m_grid_width;
    const uint32 m_grid_height;
    const uint32 m_pool_height;
    const uint32 m_bonus_rules;

    /* Constructors ***********************************************************/

    Puzzle(
        const uint32 quota,
        const uint32 num_swaps,
        const uint32 num_device_types,
        const uint32 grid_width,
        const uint32 grid_height,
        const uint32 pool_height,
        const uint32 bonus_rules
    );

    Puzzle(
        const uint32 quota,
        const uint32 num_swaps,
        const uint32 num_device_types,
        const uint32 grid_width,
        const uint32 grid_height,
        const uint32 pool_height,
        const uint32 bonus_rules,
        const uint8 **grid
    );

    Puzzle( const Puzzle &cpy );

    /* Destructor *************************************************************/
    ~Puzzle();

    /* Member Functions *******************************************************/
    void printFile( std::ostream &out = std::cout ) const;

    void swap( const Point from, const Point to );

    uint32 makeMove( Move &m, const bool showWork = false );

    uint8 getDeviceType( Point p, bool check = true ) const;

    uint8 getDeviceType( uint32 r, uint32 c, bool check = true ) const;

    uint8 **getCopyOfGrid() const;

    uint8 getReplacement( const uint32 x, const uint32 devRepl );

    void removeMatches( const std::vector< Point > &matchedPoints );

    void fillEmptyPoints();

    std::vector< Point > *findAllExistingMatches() const;

    bool isSolved() const;

    bool operator==( const Puzzle &rhs ) const;

    bool operator!=( const Puzzle &rhs ) const;


    /* Static Functions *******************************************************/
    static Puzzle *construct( std::istream &in );

    static Puzzle *construct( const char *fileName );

    /* Friend functions *******************************************************/
    friend std::ostream &operator<<( std::ostream &out, const Puzzle &p );
};

/* Function Declarations ******************************************************/

void swap( uint8 **grid, Point from, Point to );

uint8 **copyGrid(
    const uint8 **const m_grid,
    const uint32 m_grid_height,
    const uint32 m_grid_width
);

Point formulatePoint( const uint32 r, const uint32 c, const Direction d );

void addIfNew( std::vector< Point > *v, Point newPoint );

#endif //GLITTERBOMB_PUZZLE_H
