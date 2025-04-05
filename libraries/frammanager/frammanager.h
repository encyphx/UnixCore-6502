#ifndef FRAMMANAGER_H
#define FRAMMANAGER_H

#include "Arduino.h"

#define ODRPORTJMask 0xFF80
#define ODRPORTGMask 0xDFFF

#define FRAM_RD_IRQ 16
#define FRAM_WR_IRQ 17

extern byte freeram[24064];

void FRAM_read();
void FRAM_write();
void FRAM_setup();

#endif
