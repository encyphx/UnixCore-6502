#ifndef STKMANAGER_H
#define STKMANAGER_H

#include "Arduino.h"

#define ODRPORTJMask 0xFF80
#define ODRPORTGMask 0xDFFF

#define STK_RD_IRQ 14
#define STK_WR_IRQ 15

extern byte stack[256];

void STK_read();
void STK_write();
void STK_setup();

#endif
