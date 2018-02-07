/******************************************************************************
 *
 * File:
 *   cmd
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   glitterbomb
 *
 ******************************************************************************/

#include "cmd.h"

#include <cstring>

#include "types.h"

ExecutionType getExecutionType( const int argc, const char **argv ) {

  /* Local variables */
  char *firstParameter;

  /* Default to RUN */
  if ( argc == 1 ) {
    return RUN;
  }

  /* Initialize */
  firstParameter = new char[strlen( argv[ 1 ] ) + 1];
  strcpy( firstParameter, argv[ 1 ] );

  /* Convert first parameter to lower case */
  for ( uint32 i = 0; i < strlen( firstParameter ); ++i ) {
    firstParameter[ i ] = ( char ) tolower( firstParameter[ i ] );
  }

  /* Check for test parameter */
  if ( strcmp( firstParameter, "test" ) == 0 ) {
    delete[] firstParameter;
    return TEST;
  }

  delete[] firstParameter;

  /* Default to RUN */
  return RUN;
}
