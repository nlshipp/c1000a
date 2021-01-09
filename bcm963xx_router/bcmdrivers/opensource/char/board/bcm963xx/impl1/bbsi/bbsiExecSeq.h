/*
<:label-BRCM::DUAL/GPL:standard 
:>
*/

#ifndef _BBSI_EXECUTE_SEQUENCE_H
#define _BBSI_EXECUTE_SEQUENCE_H

#include <linux/types.h>

enum cmdToExec
{ 
    CMD_READ,
    CMD_WRITE,    
    CMD_WAIT,
    CMD_END
};


typedef struct
{
    enum cmdToExec command;
    uint32_t addr;
    uint32_t value;
} cmdElem;



void bbsiExecuteCommandSequence(cmdElem *prSeq);

#endif

