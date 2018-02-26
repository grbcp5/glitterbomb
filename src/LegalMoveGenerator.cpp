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


/* Function:
 *   checkHorizontalRange
 * Description:
 *   Determines the number of matched devices between col_min and col_max
 */

uint32 checkHorizontalRange(
    const Puzzle &p,
    const uint32 row,
    const uint32 col_min,
    const uint32 col_max,
    Point *matchedDevices = NULL
) {

  /* Local variables */
  uint32 similarDevices( 1 ); // Since all devices are similar to themselves

  /* For each column in range */
  for ( uint32 c = col_min; c < col_max; ++c ) {

    /* If this device is equal to the next device... */
    if ( p.getDeviceType( row, c ) == p.getDeviceType( row, c + 1 )
         && p.getDeviceType( row, c ) != Puzzle::NO_DEVICE ) {

      /* Add to matched devices */
      if ( matchedDevices != NULL ) {
        matchedDevices[ similarDevices - 1 ] = Point( row, c );
        matchedDevices[ similarDevices ] = Point( row, c + 1 );
      }

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

  /* Return the magnitude of the match */
  return similarDevices;
}


/* Function:
 *   checkVerticalRange
 * Description:
 *   Determines the number of matched devices between row_min and row_max
 */

uint32 checkVerticalRange(
    const Puzzle &p,
    const uint32 row_min,
    const uint32 row_max,
    const uint32 col,
    Point *matchedDevices = NULL
) {

  /* Local variables */
  uint32 similarDevices( 1 ); // Since all devices are similar to themselves

  /* For each row in range */
  for ( uint32 r = row_min; r < row_max; ++r ) {

    /* If this device is equal to the next device... */
    if ( p.getDeviceType( r, col ) == p.getDeviceType( r + 1, col )
         && p.getDeviceType( r, col ) != Puzzle::NO_DEVICE ) {

      /* Add to matched devices */
      if ( matchedDevices != NULL ) {
        matchedDevices[ similarDevices - 1 ] = Point( r, col );
        matchedDevices[ similarDevices ] = Point( r + 1, col );
      }

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

  /* Return the magnitude of the match */
  return similarDevices;
}


/* Function:
 *   checkForMatchesRightSwap
 * Description:
 *   Checks for any possible matched devices as a result of a right swap
 */

uint32 checkForMatchesRightSwap(
    const Puzzle &p,
    Point from,
    vector< Point > *totalMatchPoints
) {

  /* Local Variables */
  uint32 totalDevicesMatched( 0 );
  uint32 potentialMatchOne( 0 );
  uint32 potentialMatchTwo( 0 );
  uint32 potentialMatchThree( 0 );
  uint32 potentialMatchFour( 0 );
  Point *matchedDevices = new Point[5]; // 5 = max range

  /* Reference diagram under resources/SwapDiagrams.pdf */

  /* Potential match one */
  potentialMatchOne = checkVerticalRange(
      p,
      from.row >= 2 ? from.row - 2 : 0,
      from.row + 2,
      from.col,
      matchedDevices
  );
  /* Add matched device position to vector */
  for ( uint32 i = 0; i < potentialMatchOne; ++i ) {
    addIfNew( totalMatchPoints, matchedDevices[ i ] );
  }
  /* Keep running total */
  totalDevicesMatched += potentialMatchOne;

  /* Potential match two */
  potentialMatchTwo = checkVerticalRange(
      p,
      from.row >= 2 ? from.row - 2 : 0,
      from.row + 2,
      from.col + 1,
      matchedDevices
  );
  /* Add matched device position to vector */
  for ( uint32 i = 0; i < potentialMatchTwo; ++i ) {
    addIfNew( totalMatchPoints, matchedDevices[ i ] );
  }
  /* Keep running total */
  totalDevicesMatched += potentialMatchTwo;

  /* Potential match three */
  potentialMatchThree = checkHorizontalRange(
      p,
      from.row,
      from.col >= 2 ? from.col - 2 : 0,
      from.col,
      matchedDevices
  );
  /* Add matched device position to vector */
  for ( uint32 i = 0; i < potentialMatchThree; ++i ) {
    addIfNew( totalMatchPoints, matchedDevices[ i ] );
  }
  /* Keep running total */
  potentialMatchThree -= ( potentialMatchOne ? 1 : 0 );
  totalDevicesMatched += ( potentialMatchThree < 6 ? potentialMatchThree : 0 );

  /* Potential match four */
  potentialMatchFour = checkHorizontalRange(
      p,
      from.row,
      from.col + 1,
      from.col + 3,
      matchedDevices
  );
  /* Add matched device position to vector */
  for ( uint32 i = 0; i < potentialMatchFour; ++i ) {
    addIfNew( totalMatchPoints, matchedDevices[ i ] );
  }
  /* Keep running total */
  potentialMatchFour -= ( potentialMatchTwo ? 1 : 0 );
  totalDevicesMatched += ( potentialMatchFour < 6 ? potentialMatchFour : 0 );

  delete[] matchedDevices;

  return totalDevicesMatched;
}


/* Function:
 *   checkForMatchesDownSwap
 * Description:
 *   Checks for any possible matched devices as a result of a down swap
 */

uint32 checkForMatchesDownSwap(
    const Puzzle &p,
    Point from,
    vector< Point > *totalMatchPoints
) {

  /* Local Variables */
  uint32 totalDevicesMatched( 0 );
  uint32 potentialMatchOne( 0 );
  uint32 potentialMatchTwo( 0 );
  uint32 potentialMatchThree( 0 );
  uint32 potentialMatchFour( 0 );
  Point *matchedDevices = new Point[5]; // 5 = max range

  /* Reference diagram under resources/SwapDiagrams.pdf */

  /* Potential match one */
  potentialMatchOne = checkHorizontalRange(
      p,
      from.row,
      from.col >= 2 ? from.col - 2 : 0,
      from.col + 2,
      matchedDevices
  );
  /* Add matched device position to vector */
  for ( uint32 i = 0; i < potentialMatchOne; ++i ) {
    addIfNew( totalMatchPoints, matchedDevices[ i ] );
  }
  /* Keep running total */
  totalDevicesMatched += potentialMatchOne;

  /* Potential match two */
  potentialMatchTwo = checkHorizontalRange(
      p,
      from.row + 1,
      from.col >= 2 ? from.col - 2 : 0,
      from.col + 2,
      matchedDevices
  );
  /* Add matched device position to vector */
  for ( uint32 i = 0; i < potentialMatchTwo; ++i ) {
    addIfNew( totalMatchPoints, matchedDevices[ i ] );
  }
  /* Keep running total */
  totalDevicesMatched += potentialMatchTwo;

  /* Potential match three */
  potentialMatchThree = checkVerticalRange(
      p,
      from.row >= 2 ? from.row - 2 : 0,
      from.row,
      from.col,
      matchedDevices
  );
  /* Add matched device position to vector */
  for ( uint32 i = 0; i < potentialMatchThree; ++i ) {
    addIfNew( totalMatchPoints, matchedDevices[ i ] );
  }
  /* Keep running total */
  potentialMatchThree -= ( potentialMatchOne ? 1 : 0 );
  totalDevicesMatched += ( potentialMatchThree < 6 ? potentialMatchThree : 0 );

  /* Potential match four */
  potentialMatchFour = checkVerticalRange(
      p,
      from.row + 1,
      from.row + 3,
      from.col,
      matchedDevices
  );
  /* Add matched device position to vector */
  for ( uint32 i = 0; i < potentialMatchFour; ++i ) {
    addIfNew( totalMatchPoints, matchedDevices[ i ] );
  }
  /* Keep running total */
  potentialMatchFour -= ( potentialMatchTwo ? 1 : 0 );
  totalDevicesMatched += ( potentialMatchFour < 6 ? potentialMatchFour : 0 );

  delete[] matchedDevices;

  return totalDevicesMatched;
}


/* Function:
 *   resultingPointsFromMove
 * Description:
 *   Checks if a move results in any matched devices
 */

uint32 resultingPointsFromMove(
    const Puzzle *puzzle,
    Point from,
    Direction dir,
    vector< Point > *matchedPoints
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
      totalPoints = checkForMatchesDownSwap(
          puzzleCopy,
          to,
          matchedPoints
      );
      break;
    case DOWN:
      totalPoints = checkForMatchesDownSwap(
          puzzleCopy,
          from,
          matchedPoints
      );
      break;
    case LEFT:
      totalPoints = checkForMatchesRightSwap(
          puzzleCopy,
          to,
          matchedPoints
      );
      break;
    case RIGHT:
      totalPoints = checkForMatchesRightSwap(
          puzzleCopy,
          from,
          matchedPoints
      );
      break;
  }

  /* Return sum of all matches */
  return totalPoints;
}


/* Function:
 *   getLegalMoves
 * Description:
 *   Returns all moves that result in matched devices
 */

vector< Move * > *getLegalMoves( const Puzzle *p ) {

  /* Local Constants */
  const Direction DIRS[] = { RIGHT, DOWN };
  const uint32 DIR_COUNT = 2;

  /* Local Variables */
  vector< Move * > *result = new vector< Move * >();
  uint32 points( 0 );
  vector< Point > *matched;

  /* Return if no swaps available */
  if ( p->m_swaps_used >= p->m_num_swaps ) {
    return result;
  }

  /* For each row in grid */
  for ( uint32 r = p->m_pool_height; r < p->m_grid_height; r++ ) {

    /* For each column in grid */
    for ( uint32 c = 0; c < p->m_grid_width; c++ ) {

      /* For each direction to move a piece */
      for ( uint32 d = 0; d < DIR_COUNT; d++ ) {

        /* Skip down tries for bottom row */
        if ( r == p->m_grid_height - 1 && DIRS[ d ] == DOWN ) {
          continue;
        }

        /* Skip right tries for rightmost row */
        if ( c == p->m_grid_width - 1 && DIRS[ d ] == RIGHT ) {
          continue;
        }
  
        matched = new vector< Point >();

        /* Find how many points are generated from swap */
        points = resultingPointsFromMove(
            p,
            Point( r, c ),
            DIRS[ d ],
            matched
        );

        /* If swap generates points*/
        if ( points > 0 ) {

          /* Add to list of legal Moves */
          result->push_back( new Move(
              Point( r, c ),
              formulatePoint( r, c, DIRS[ d ]
              ),
              points,
              matched
          ));
  
        }
  
        delete matched;

      }  // d
    } // c
  } // r

  // Return list of legal moves
  return result;
}
