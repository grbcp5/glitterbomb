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
    uint8 **m_grid;

    void fallDown( const uint32 row, const uint32 col, const uint32 n );

public:
    static const uint8 NO_DEVICE = 0;

    uint32 m_score;
    uint32 m_swaps_used;

    const uint32 m_quota;
    const uint32 m_num_swaps;
    const uint32 m_num_device_types;
    const uint32 m_grid_width;
    const uint32 m_grid_height;
    const uint32 m_pool_height;
    const uint32 m_bonus_rules;

    /* No grid initializer */
    Puzzle(
        const uint32 quota,
        const uint32 num_swaps,
        const uint32 num_device_types,
        const uint32 grid_width,
        const uint32 grid_height,
        const uint32 pool_height,
        const uint32 bonus_rules
    );

    /* Deep grid copy */
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

    /* Deep copy constructor */
    Puzzle( const Puzzle &cpy );

    /* Safe destructor */
    ~Puzzle();

    /* Member functions */
    void swap( const Point from, const Point to );

    void makeMove( const Move &m );

    uint8 getDeviceType( Point p ) const;

    uint8 getDeviceType( uint32 r, uint32 c ) const;

    uint8 **getCopyOfGrid() const;

    uint8 getReplacement( const uint32 x, const uint32 devRepl );

    void removeMatches( const std::vector< Point > &matchedPoints );

    void fillEmptyPoints();

    bool isSolved() const;

    /* Static functions */
    static Puzzle *construct(std::istream &in);

    static Puzzle *construct( const char *fileName );

    /* Friend functions */
    friend std::ostream &operator<<(std::ostream &out, const Puzzle &p);
};

void swap( uint8 **grid, Point from, Point to );

uint8 **copyGrid(
    const uint8 **const m_grid,
    const uint32 m_grid_height,
    const uint32 m_grid_width
);


#endif //GLITTERBOMB_PUZZLE_H
