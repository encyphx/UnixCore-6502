#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include "Arduino.h"

#define ODRPORTJMask 0xFF80
#define ODRPORTGMask 0xDFFF

#define KEYBD_IRQ 19
#define IRQB_IRQ 5

void KEYBD_read();
void KEYBD_setup();

#endif
