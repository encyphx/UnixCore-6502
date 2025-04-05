#ifndef ROMMANAGER_H
#define ROMMANAGER_H

#include "Arduino.h"

#define SIZE 0
#define HEXCODE {}

#define ODRPORTJMask 0xFF80
#define ODRPORTGMask 0xDFFF

#define LROM_RD_IRQ 20
#define HROM_RD_IRQ 21

extern byte lowrom[16384];
extern byte highrom[16384];

void LROM_read();
void HROM_read();
void ROM_setup();

#endif
