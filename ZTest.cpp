/******************************************************************************
 *
 * File:
 *   ZTest
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   glitterbomb
 *
 ******************************************************************************/

#include "ZTest.h"

#include <iostream>

#include "ZTestLegalMoveGenerator.h"

using namespace std;

int ZTest::executeAllTests() {

  /* Test Objects */
  const ZTest *testObjects[] = {
      new ZTestLegalMoveGenerator()
  };
  const uint32 NUM_TEST_OBJECTS = 1;

  /* Local variables */
  int ret_val( 0 );

  /* Call each test case */
  for ( uint32 i = 0; i < NUM_TEST_OBJECTS; i++ ) {
    ret_val |= testObjects[ i ]->test( 1u << i );
  }

  /* return results */
  return ret_val;
}
