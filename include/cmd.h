//
// Created by Grant Broadwater on 2/6/18.
//

#ifndef GLITTERBOMB_CMD_H
#define GLITTERBOMB_CMD_H

/* Types **********************************************************************/


enum ExecutionType {
    TEST = 0,
    RUN = 1
};


/* Function Declarations ******************************************************/


ExecutionType getExecutionType( const int argc, const char **argv );

#endif //GLITTERBOMB_CMD_H
