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

using namespace std;

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
  for ( uint32 r = 0; r < m_grid_height; r++ ) {

    m_grid[ r ] = new uint8[m_grid_width];
    for ( uint32 c = 0; c < m_grid_width; c++ ) {

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
  for ( uint32 r = 0; r < m_grid_height; r++ ) {
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

  for ( uint32 r = 0; r < result->m_grid_height; r++ ) {
    for ( uint32 c = 0; c < result->m_grid_width; c++ ) {
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

  out << "Score: " << p.m_score
      << "\nSwaps: " << p.m_swaps_used
      << "\nQuota: " << p.m_quota
      << "\nAllowed Swaps: " << p.m_num_swaps
      << "\nNum Device Types: " << p.m_num_device_types
      << "\nGrid (WxH): (" << p.m_grid_width << "x" << p.m_grid_height << ")"
      << "\nPool Height: " << p.m_pool_height
      << "\nPuzzle Values:" << std::endl;

  for ( uint32 r = 0; r < p.m_grid_height; r++ ) {

    if ( r == p.m_pool_height ) {
      for ( uint32 i = 0; i < ( 2 * p.m_grid_width ); ++i ) {
        out << "-";
      }
      out << std::endl;
    }

    for ( uint32 c = 0; c < p.m_grid_width; c++ ) {
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

void Puzzle::swap( const Point from, const Point to ) {
  ::swap( m_grid, from, to );
}

uint32 Puzzle::makeMove( Move &m, const bool showWork ) {

  /* Local variables */
  std::vector< Point > *matches;
  uint32 scoreFromMove( 0 );

  /* Initialize */
  matches = m.matchedDevices;
  m.matchedDevices = NULL;

  /* Make swap */
  ::swap( m_grid, m.from, m.to );

  if ( showWork ) {
    cout << "\tWork: " << scoreFromMove << endl << ( *this ) << endl;
  }

  /* While there are matched points */
  while ( matches != NULL && !matches->empty()) {

    /* Increment score */
    scoreFromMove += matches->size();

    /* Remove them */
    removeMatches( *( matches ));

    if ( showWork ) {
      cout << "\tWork: " << scoreFromMove << endl << ( *this ) << endl;
    }

    /* Fall down */
    fillEmptyPoints();

    if ( showWork ) {
      cout << "\tWork: " << scoreFromMove << endl << ( *this ) << endl;
    }

    /* Delete dynamic memeory */
    matches->clear();
    delete matches;

    /* Get subsequent matches */
    matches = findAllExistingMatches();
  }

  delete matches;

  /* Update puzzle variables */
  m_score += scoreFromMove;
  m_swaps_used++;

  return scoreFromMove;
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

bool Puzzle::isSolved() const {
  return m_score >= m_quota;
}


void Puzzle::removeMatches( const std::vector< Point > &v ) {

  /* For each matched points */
  for ( uint32 i = 0; i < v.size(); ++i ) {

    /* Mark device with 0 */
    m_grid[ v[ i ].row ][ v[ i ].col ] = 0;
  }
}


uint8 Puzzle::getReplacement( const uint32 x, const uint32 devRepl ) {
  return ( uint8 ) ((( getDeviceType( 1, x ) + x + devRepl ) %
                     m_num_device_types ) + 1 );
}

void Puzzle::fallDown( const uint32 row, const uint32 col, const uint32 n ) {

  for ( int r = row; r > 0; --r ) {
    m_grid[ r ][ col ] = m_grid[ r - 1 ][ col ];
  }

  m_grid[ 0 ][ col ] = getReplacement( col, n );
}


void Puzzle::fillEmptyPoints() {

  uint32 devRepl = 1u;

  for ( uint32 r = 0; r < m_grid_height; ++r ) {
    for ( uint32 c = 0; c < m_grid_width; ++c ) {

      if ( m_grid[ r ][ c ] == 0 ) {
        fallDown( r, c, devRepl++ );
      }

    }
  }

}

std::vector< Point > *Puzzle::findAllExistingMatches() const {

  const Direction DIRS[] = { RIGHT, DOWN };
  const uint32 NUM_DIRS = 2;

  std::vector< Point > *result = new std::vector< Point >();
  Point here;
  uint8 hereD;
  Point next;
  uint8 nextD;
  Point last;
  uint8 lastD;

  for ( uint32 r = m_pool_height; r < m_grid_height; ++r ) {
    for ( uint32 c = 0; c < m_grid_width; ++c ) {
      for ( uint32 d = 0; d < NUM_DIRS; ++d ) {

        if ( c > m_grid_width - 3 && DIRS[ d ] == RIGHT ) {
          continue;
        }

        if ( r > m_grid_height - 3 && DIRS[ d ] == DOWN ) {
          continue;
        }

        here = Point( r, c );
        hereD = getDeviceType( here );
        next = formulatePoint( r, c, DIRS[ d ] );
        nextD = getDeviceType( next );
        last = formulatePoint( next.row, next.col, DIRS[ d ] );
        lastD = getDeviceType( last );

        if ( hereD != 0 && hereD == nextD && nextD == lastD ) {
          addIfNew( result, here );
          addIfNew( result, next );
          addIfNew( result, last );
        }
      }
    }
  }

  return result;
}

void Puzzle::printFile() const {

  std::cout << m_quota << endl
            << m_num_swaps << endl
            << m_num_device_types << endl
            << m_grid_width << endl
            << m_grid_height << endl
            << m_pool_height << endl;

  for ( uint32 r = 0; r < m_grid_height; r++ ) {
    for ( uint32 c = 0; c < m_grid_width; c++ ) {
      cout << (( int ) m_grid[ r ][ c ] ) << " ";
    }
    cout << std::endl;
  }

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
  for ( uint32 r = 0; r < m_grid_height; ++r ) {

    /* Create new row of equal width */
    result[ r ] = new uint8[m_grid_width];

    /* For each column position in row */
    for ( uint32 c = 0; c < m_grid_width; ++c ) {

      /* Copy value */
      result[ r ][ c ] = m_grid[ r ][ c ];
    }
  }

  return result;
}

Point formulatePoint( const uint32 r, const uint32 c, const Direction d ) {

  switch ( d ) {
    case UP:
      return Point( r - 1, c );
    case DOWN:
      return Point( r + 1, c );
    case LEFT:
      return Point( r, c - 1 );
    case RIGHT:
      return Point( r, c + 1 );
  }

  return Point( r, c );
}

void addIfNew( std::vector< Point > *v, Point newPoint ) {

  if ( v == NULL ) {
    return;
  }

  for ( uint32 i = 0; i < v->size(); ++i ) {
    if ( v->at( i ) == newPoint ) {
      return;
    }
  }

  v->push_back( newPoint );
}
