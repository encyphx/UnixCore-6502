#ifndef ROMMANAGER_H
#define ROMMANAGER_H

#include "Arduino.h"

#define FFFE 0x00
#define FFFF 0x00

#define L_SIZE 0
#define L_HEXCODE {}

#define H_SIZE 0
#define H_HEXCODE {}

#define ODRPORTJMask 0xFF80
#define ODRPORTGMask 0xDFFF

#define LROM_RD_IRQ 18
#define HROM_RD_IRQ 19

#define RST 4

extern byte lowrom[16384];
extern byte highrom[16384];

void LROM_read();
void HROM_read();
void ROM_setup();

void reset();

#endif
