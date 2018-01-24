//
// Created by Grant Broadwater on 1/23/18.
//

#ifndef GLITTERBOMB_PUZZLE_H
#define GLITTERBOMB_PUZZLE_H

#include "types.h"
#include <iostream>

class Puzzle {

private:
    uint8 **m_grid;

public:
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

    /* Static functions */
    static Puzzle *construct(std::istream &in);
    static Puzzle *construct(const char *fileName);

    /* Friend functions */
    friend std::ostream &operator<<(std::ostream &out, const Puzzle &p);
};


#endif //GLITTERBOMB_PUZZLE_H
