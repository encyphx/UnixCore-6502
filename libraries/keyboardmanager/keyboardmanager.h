#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include "Arduino.h"

#define IRQB_ACK 5

#define ODRPORTJMask 0xFF80
#define ODRPORTGMask 0xDFFF

#define KEYBD_IRQ 17

void KEYBD_read();
void KEYBD_setup();

#endif
