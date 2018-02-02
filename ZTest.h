//
// Created by Grant Broadwater on 2/1/18.
//

#ifndef GLITTERBOMB_ZTEST_H
#define GLITTERBOMB_ZTEST_H

#include "types.h"

class ZTest {

private:

public:

    /* Static caller function */
    static int executeAllTests();

    virtual int test( uint32 testID ) const = 0;
};


#endif //GLITTERBOMB_ZTEST_H
