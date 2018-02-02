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
    m_grid( NULL ),
    m_score( 0 ),
    m_swaps_used( 0 ),
    m_quota( quota ),
    m_num_swaps( num_swaps ),
    m_num_device_types( num_device_types ),
    m_grid_width( grid_width ),
    m_grid_height( grid_height ),
    m_pool_height( pool_height ),
    m_bonus_rules( bonus_rules ) {

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
    m_grid( NULL ),
    m_score( 0 ),
    m_swaps_used( 0 ),
    m_quota( quota ),
    m_num_swaps( num_swaps ),
    m_num_device_types( num_device_types ),
    m_grid_width( grid_width ),
    m_grid_height( grid_height ),
    m_pool_height( pool_height ),
    m_bonus_rules( bonus_rules ) {
  m_grid = copyGrid( grid, m_grid_height, m_grid_width );
}


/* Copy Constructor */
Puzzle::Puzzle( const Puzzle &cpy ) :
    m_grid( NULL ),
    m_score( cpy.m_score ),
    m_swaps_used( cpy.m_swaps_used ),
    m_quota( cpy.m_quota ),
    m_num_swaps( cpy.m_num_swaps ),
    m_num_device_types( cpy.m_num_device_types ),
    m_grid_width( cpy.m_grid_width ),
    m_grid_height( cpy.m_grid_height ),
    m_pool_height( cpy.m_pool_height ),
    m_bonus_rules( cpy.m_bonus_rules ) {
  m_grid = cpy.getCopyOfGrid();
}


/* Destructor */
Puzzle::~Puzzle() {
  for ( int r = 0; r < m_grid_height; r++ ) {
    delete[] m_grid[ r ];
  }
  delete[] m_grid;
}


Puzzle *Puzzle::construct( std::istream &in ) {
  uint32 quota, num_swaps, num_device_types, grid_width, grid_height,
      pool_height, bonus_rules;

  int grid_value;

  in >> quota >> num_swaps >> num_device_types >> grid_width >> grid_height
     >> pool_height >> bonus_rules;

  Puzzle *result = new Puzzle(
      ( uint32 ) quota,
      num_swaps,
      num_device_types,
      grid_width,
      grid_height,
      pool_height,
      bonus_rules
  );

  for ( int r = 0; r < result->m_grid_height; r++ ) {
    for ( int c = 0; c < result->m_grid_width; c++ ) {
      in >> grid_value;
      result->m_grid[ r ][ c ] = ( uint8 ) grid_value;
    }
  }

  return result;
}


Puzzle *Puzzle::construct( const char *fileName ) {
  Puzzle *result = NULL;

  std::ifstream fin;
  fin.open( fileName );
  result = construct( fin );
  fin.close();

  return result;
}


std::ostream &operator<<( std::ostream &out, const Puzzle &p ) {

  out << "Quota: " << p.m_quota
      << "\nAllowed Swaps: " << p.m_num_swaps
      << "\nNum Device Types: " << p.m_num_device_types
      << "\nGrid (WxH): (" << p.m_grid_width << "x" << p.m_grid_height << ")"
      << "\nPool Height: " << p.m_pool_height
      << "\nPuzzle Values:" << std::endl;

  for ( int r = 0; r < p.m_grid_height; r++ ) {

    if ( r == p.m_pool_height ) {
      for ( int i = 0; i < ( 2 * p.m_grid_width ); ++i ) {
        out << "-";
      }
      out << std::endl;
    }

    for ( int c = 0; c < p.m_grid_width; c++ ) {
      out << (( int ) p.m_grid[ r ][ c ] ) << " ";
    }
    out << std::endl;
  }

  return out;
}

void swap( uint8 **m_grid, Point from, Point to ) {

  uint8 temp;

  temp = m_grid[ to.row ][ to.col ];
  m_grid[ to.row ][ to.col ] = m_grid[ from.row ][ from.col ];
  m_grid[ from.row ][ from.col ] = temp;

  return;
}

void Puzzle::swap( Point from, Point to ) {
  ::swap( m_grid, from, to );
}

uint8 Puzzle::getDeviceType( Point p ) const {

  /* Return no device if out of bounds */
  if ( p.row < m_pool_height ||
       p.row >= m_grid_height || p.col >= m_grid_width ) {
    return Puzzle::NO_DEVICE;
  }

  return m_grid[ p.row ][ p.col ];
}


uint8 Puzzle::getDeviceType( uint32 r, uint32 c ) const {
  return getDeviceType( Point( r, c ));
}


uint8 **Puzzle::getCopyOfGrid() const {
  return copyGrid(
      ( const uint8 **const ) m_grid,
      m_grid_height,
      m_grid_width
  );
}

uint8 **copyGrid(
    const uint8 **const m_grid,
    const uint32 m_grid_height,
    const uint32 m_grid_width
) {
  /* Local Variables */
  uint8 **result;

  /* Create array of rows for grid of equal length */
  result = new uint8 *[m_grid_height];

  /* For each row index */
  for ( int r = 0; r < m_grid_height; ++r ) {

    /* Create new row of equal width */
    result[ r ] = new uint8[m_grid_width];

    /* For each column position in row */
    for ( int c = 0; c < m_grid_width; ++c ) {

      /* Copy value */
      result[ r ][ c ] = m_grid[ r ][ c ];
    }
  }

  return result;
}