/******************************************************************************
 *
 * File:
 *   Puzzle
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   glitterbomb
 *
 ******************************************************************************/

#include "Puzzle.h"
#include <fstream>

/* Constructor with no grid initializer */
Puzzle::Puzzle(
    const uint32 quota,
    const uint32 num_swaps,
    const uint32 num_device_types,
    const uint32 grid_width,
    const uint32 grid_height,
    const uint32 pool_height,
    const uint32 bonus_rules
)
    :
    m_quota( quota ),
    m_num_swaps( num_swaps ),
    m_num_device_types( num_device_types ),
    m_grid_width( grid_width ),
    m_grid_height( grid_height ),
    m_pool_height( pool_height ),
    m_bonus_rules( bonus_rules )
{

  m_grid = new uint8 *[m_grid_height];
  for ( int r = 0; r < m_grid_height; r++ ) {

    m_grid[ r ] = new uint8[m_grid_width];
    for ( int c = 0; c < m_grid_width; c++ ) {

      m_grid[ r ][ c ] = 0;

    }
  }
}

/* Deep copy grid */
Puzzle::Puzzle(
    const uint32 quota,
    const uint32 num_swaps,
    const uint32 num_device_types,
    const uint32 grid_width,
    const uint32 grid_height,
    const uint32 pool_height,
    const uint32 bonus_rules,
    const uint8 **grid
)
    :
    m_quota( quota ),
    m_num_swaps( num_swaps ),
    m_num_device_types( num_device_types ),
    m_grid_width( grid_width ),
    m_grid_height( grid_height ),
    m_pool_height( pool_height ),
    m_bonus_rules( bonus_rules )
{

  m_grid = new uint8 *[m_grid_height];
  for ( int r = 0; r < m_grid_height; r++ ) {

    m_grid[ r ] = new uint8[m_grid_width];
    for ( int c = 0; c < m_grid_width; c++ ) {

      m_grid[ r ][ c ] = grid[ r ][ c ];

    }
  }
}

/* Copy Constructor */
Puzzle::Puzzle( const Puzzle &cpy ) :
    m_quota( cpy.m_quota ),
    m_num_swaps( cpy.m_num_swaps ),
    m_num_device_types( cpy.m_num_device_types ),
    m_grid_width( cpy.m_grid_width ),
    m_grid_height( cpy.m_grid_height ),
    m_pool_height( cpy.m_pool_height ),
    m_bonus_rules( cpy.m_bonus_rules )
{
  m_grid = new uint8 *[m_grid_height];
  for ( int r = 0; r < m_grid_height; r++ ) {

    m_grid[ r ] = new uint8[m_grid_width];
    for ( int c = 0; c < m_grid_width; c++ ) {

      m_grid[ r ][ c ] = cpy.m_grid[ r ][ c ];

    }
  }
}

/* Destructor */
Puzzle::~Puzzle() {
  for( int r = 0; r < m_grid_height; r++ ) {
    delete [] m_grid[ r ];
  }
  delete [] m_grid;
}

Puzzle *Puzzle::construct(std::istream &in) {
  uint32 quota, num_swaps, num_device_types, grid_width, grid_height,
      pool_height, bonus_rules;

  int grid_value;

  in >> quota >> num_swaps >> num_device_types >> grid_width >> grid_height
     >> pool_height >> bonus_rules;

  Puzzle *result = new Puzzle(
      (uint32)quota,
      num_swaps,
      num_device_types,
      grid_width,
      grid_height,
      pool_height,
      bonus_rules
  );

  for( int r = 0; r < result->m_grid_height; r++ ) {
    for( int c = 0; c < result->m_grid_width; c++ ) {
      in >> grid_value;
      result->m_grid[ r ][ c ] = ( uint8 )grid_value;
    }
  }

  return result;
}

Puzzle *Puzzle::construct(const char *fileName) {
  Puzzle *result = NULL;

  std::ifstream fin;
  fin.open(fileName);
  result = construct( fin );
  fin.close();

  return result;
}

std::ostream &operator<<(std::ostream &out, const Puzzle &p) {

  out << "Quota: " << p.m_quota
      << "\nAllowed Swaps: " << p.m_num_swaps
      << "\nNum Device Types: " << p.m_num_device_types
      << "\nGrid (WxH): (" << p.m_grid_width << "x" << p.m_grid_height << ")"
      << "\nPool Height: " << p.m_pool_height
      << "\nPuzzle Values:" << std::endl;

  for( int r = 0; r < p.m_grid_height; r++ ) {
    for( int c = 0; c < p.m_grid_width; c++ ) {
      out << ( ( int ) p.m_grid[ r ][ c ] ) << " ";
    }
    out << std::endl;
  }

  return out;
}