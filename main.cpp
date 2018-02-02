#include <iostream>

#include "ZTest.h"

using namespace std;

enum ExecutionType {
    TEST = 0,
    RUN = 1
};

ExecutionType getExecutionType( const int argc, const char **argv );


int main( const int argc, const char **argv ) {

  if ( getExecutionType( argc, argv ) == TEST ) {
    return ZTest::executeAllTests();
  }

  return 0;
}


ExecutionType getExecutionType( const int argc, const char **argv ) {

  /* Local variables */
  char *firstParameter;

  /* Default to RUN */
  if ( argc == 1 ) {
    return RUN;
  }

  /* Initialize */
  firstParameter = new char[strlen( argv[ 1 ] )];
  strcpy( firstParameter, argv[ 1 ] );

  /* Convert first parameter to lower case */
  for ( int i = 0; i < strlen( firstParameter ); ++i ) {
    firstParameter[ i ] = ( char ) tolower( firstParameter[ i ] );
  }

  /* Check for test parameter */
  if ( strcmp( firstParameter, "test" ) == 0 ) {
    return TEST;
  }

  /* Default to RUN */
  return RUN;
}