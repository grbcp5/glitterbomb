/******************************************************************************
 *
 * File:
 *   LegalMoveGenerator
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   glitterbomb
 *
 ******************************************************************************/

#include "LegalMoveGenerator.h"

using namespace std;


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


uint32 checkHorizontalRange(
    const Puzzle &p,
    const uint32 row,
    const uint32 col_min,
    const uint32 col_max
) {

  /* Local variables */
  uint32 similarDevices( 1 ); // Since all devices are similar to themselves

  /* For each column in range */
  for ( uint32 c = col_min; c < col_max; ++c ) {

    /* If this device is equal to the next device... */
    if ( p.getDeviceType( row, c ) == p.getDeviceType( row, c + 1 )
         && p.getDeviceType( row, c ) != Puzzle::NO_DEVICE ) {

      /* Increase streak of similar devices */
      similarDevices++;

    } else {

      /* If a complete match has already been made or if there is no chance
       * for a complete match to be made then... */
      if ( similarDevices >= 3 || c > ( col_max - 2 )) {
        /* ...Stop looking for matches */
        break;
      }

      /* Reset Similar device streak counter */
      similarDevices = 1;

    } // If this matches next
  } // for each position

  /* If a complete match couldn't be made... */
  if ( similarDevices < 3 ) {
    /* ...Return no devices matched */
    return 0;
  }

  // TODO: Check for subsequent matches

  /* Return the magnitude of the match */
  return similarDevices;
}


uint32 checkVerticalRange(
    const Puzzle &p,
    const uint32 row_min,
    const uint32 row_max,
    const uint32 col
) {

  /* Local variables */
  uint32 similarDevices( 1 ); // Since all devices are similar to themselves

  /* For each row in range */
  for ( uint32 r = row_min; r < row_max; ++r ) {

    /* If this device is equal to the next device... */
    if ( p.getDeviceType( r, col ) == p.getDeviceType( r + 1, col )
         && p.getDeviceType( r, col ) != Puzzle::NO_DEVICE ) {

      /* Increase streak of similar devices */
      similarDevices++;

    } else {

      /* If a complete match has already been made or if there is no chance
       * for a complete match to be made then... */
      if ( similarDevices >= 3 || r > ( row_max - 2 )) {
        /* ...Stop looking for matches */
        break;
      }

      /* Reset Similar device streak counter */
      similarDevices = 1;

    } // If this matches next
  } // for each position

  /* If a complete match couldn't be made... */
  if ( similarDevices < 3 ) {
    /* ...Return no devices matched */
    return 0;
  }

  // TODO: Check for subsequent matches

  /* Return the magnitude of the match */
  return similarDevices;
}


uint32 checkForMatchesRightSwap( const Puzzle &p, Point from ) {

  /* Local Variables */
  uint32 totalDevicesMatched( 0 );
  uint32 potentialMatchOne( 0 );
  uint32 potentialMatchTwo( 0 );
  uint32 potentialMatchThree( 0 );
  uint32 potentialMatchFour( 0 );

  /* Reference diagram under resources/SwapDiagrams.pdf */

  /* Potential match one */
  potentialMatchOne = checkVerticalRange(
      p,
      from.row - 2,
      from.row + 2,
      from.col
  );
  totalDevicesMatched += potentialMatchOne;

  /* Potential match two */
  potentialMatchTwo = checkVerticalRange(
      p,
      from.row - 2,
      from.row + 2,
      from.col + 1
  );
  totalDevicesMatched += potentialMatchTwo;

  /* Potential match three */
  potentialMatchThree = checkHorizontalRange(
      p,
      from.row,
      from.col - 2,
      from.col
  ) - ( potentialMatchOne ? 1 : 0 );
  totalDevicesMatched += ( potentialMatchThree < 6 ? potentialMatchThree : 0 );

  /* Potential match four */
  potentialMatchFour = checkHorizontalRange(
      p,
      from.row,
      from.col + 1,
      from.col + 3
  ) - ( potentialMatchTwo ? 1 : 0 );
  totalDevicesMatched += ( potentialMatchFour < 6 ? potentialMatchFour : 0 );

  return totalDevicesMatched;
}


uint32 checkForMatchesDownSwap( const Puzzle &p, Point from ) {

  /* Local Variables */
  uint32 totalDevicesMatched( 0 );
  uint32 potentialMatchOne( 0 );
  uint32 potentialMatchTwo( 0 );
  uint32 potentialMatchThree( 0 );
  uint32 potentialMatchFour( 0 );

  /* Reference diagram under resources/SwapDiagrams.pdf */

  /* Potential match one */
  potentialMatchOne = checkHorizontalRange(
      p,
      from.row,
      from.col - 2,
      from.col + 2
  );
  totalDevicesMatched += potentialMatchOne;

  /* Potential match two */
  potentialMatchTwo = checkHorizontalRange(
      p,
      from.row + 1,
      from.col - 2,
      from.col + 2
  );
  totalDevicesMatched += potentialMatchTwo;

  /* Potential match three */
  potentialMatchThree = checkVerticalRange(
      p,
      from.row - 2,
      from.row,
      from.col
  ) - ( potentialMatchOne ? 1 : 0 );
  totalDevicesMatched += ( potentialMatchThree < 6 ? potentialMatchThree : 0 );

  /* Potential match four */
  potentialMatchFour = checkVerticalRange(
      p,
      from.row + 1,
      from.row + 3,
      from.col
  ) - ( potentialMatchTwo ? 1 : 0 );
  totalDevicesMatched += ( potentialMatchFour < 6 ? potentialMatchFour : 0 );

  return totalDevicesMatched;
}

uint32 resultingPointsFromMove(
    const Puzzle *puzzle,
    Point from,
    Direction dir
) {

  /* Local Variables */
  Puzzle puzzleCopy( *puzzle );
  uint32 totalPoints( 0 );
  Point to;

  /* Initialize */
  to = formulatePoint( from.row, from.col, dir );

  /* Make swap to check for matches */
  puzzleCopy.swap( from, to );

  /* Check for matches */
  switch ( dir ) {
    case UP:
      totalPoints = checkForMatchesDownSwap( puzzleCopy, to );
      break;
    case DOWN:
      totalPoints = checkForMatchesDownSwap( puzzleCopy, from );
      break;
    case LEFT:
      totalPoints = checkForMatchesRightSwap( puzzleCopy, to );
      break;
    case RIGHT:
      totalPoints = checkForMatchesRightSwap( puzzleCopy, from );
      break;
  }

  /* Return sum of all matches */
  return totalPoints;
}


vector< Move > *getLegalMoves( const Puzzle *p ) {

  /* Local Constants */
  const Direction DIRS[] = { RIGHT, DOWN };
  const uint32 DIR_COUNT = 2;

  /* Local Variables */
  vector< Move > *result = new vector< Move >();
  uint32 points( 0 );

  /* For each row in grid */
  for ( uint32 r = p->m_pool_height; r < ( p->m_grid_height - 1 ); r++ ) {

    /* For each column in grid */
    for ( uint32 c = 0; c < ( p->m_grid_width - 1 ); c++ ) {

      /* For each direction to move a piece */
      for ( uint32 d = 0; d < DIR_COUNT; d++ ) {

        /* Find how many points are generated from swap */
        points = resultingPointsFromMove(
            p,
            Point( r, c ),
            DIRS[ d ]
        );

        /* If swap generates points*/
        if ( points > 0 ) {

          /* Add to list of legal Moves */
          result->push_back(
              Move(
                  Point( r, c ),
                  formulatePoint( r, c, static_cast<Direction>( d )
                  ),
                  points
              )
          );

        } // if points > 0
      }  // d
    } // c
  } // r

  // Return list of legal moves
  return result;
}
