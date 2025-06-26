#ifndef RAMMANAGER_H
#define RAMMANAGER_H

#include "Arduino.h"

#define ODRPORTJMask 0xFF80
#define ODRPORTGMask 0xDFFF

#define RAM_RD_IRQ 14
#define RAM_WR_IRQ 15

extern byte RAM[24576];

void RAM_read();
void RAM_write();
void RAM_setup();

#endif
