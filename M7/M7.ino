/* PIN 22 = A15, PIN 24 = A14, PIN 26 = A13, PIN 28 = A12, PIN 30 = A11, PIN 32 = A10, PIN 34 = A9, PIN 36 = A8, PIN 38 = A7, PIN 40 = A6, PIN 42 = A5, PIN 44 = A4, PIN 46 = A3, PIN 48 = A2, PIN 50 = A1, PIN 52 = A0 */
/* PIN 23 = D0-RD, PIN 25 = D1-RD, PIN 27 = D2-RD, PIN 29 = D3-RD, PIN 31 = D4-RD, PIN 33 = D5-RD, PIN 35 = D6-RD, PIN 37 = D7-RD */
/* PIN 39 = D0-WR, PIN 41 = D1-WR, PIN 43 = D2-WR, PIN 45 = D3-WR, PIN 47 = D4-WR, PIN 49 = D5-WR, PIN 51 = D6-WR, PIN 53 = D7-WR */
/* PIN 76 = KEYBD0, PIN 77 = KEYBD1, PIN 78 = KEYBD2, PIN 79 = KEYBD3, PIN 80 = KEYBD4, PIN 81 = KEYBD5, PIN 82 = KEYBD6, PIN 83 = KEYBD7 */
/* PIN 6 = BUS0, PIN 7 = BUS1, PIN 8 = BUS2, PIN 9 = BUS3, PIN 10 = BUS4, PIN 11 = BUS5, PIN 12 = BUS6, PIN 13 = BUS7 */
/* PIN 14 = RAM_RD_IRQ, PIN 15 = RAM_WR_IRQ, PIN 16 = BUS_IRQ, PIN 17 = KEYBD_IRQ, PIN 18 = LROM_RD_IRQ, PIN 19 = HROM_RD_IRQ */

#include <RPC.h>

#include "rammanager.h"
#include "rommanager.h"

#include "keyboardmanager.h"
#include "busmanager.h"

#define AddressPins 16
#define DataPins 8

const char ADDR_PIN[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52};

const char DATA_PIN_RD[] = {23, 25, 27, 29, 31, 33, 35, 37};
const char DATA_PIN_WR[] = {39, 41, 43, 45, 47, 49, 51, 53};

void setup() {

  RPC.begin();

  for(int i = 0; i < AddressPins; i++) {
    pinMode(ADDR_PIN[i], INPUT);
  }

  for(int i = 0; i < DataPins; i++) {
    pinMode(DATA_PIN_RD[i], OUTPUT);
  }

  for(int i = 0; i < DataPins; i++) {
    pinMode(DATA_PIN_WR[i], INPUT);
  }

  RAM_setup();
  ROM_setup();

  KEYBD_setup();
  BUS_setup();
  
  reset();

}

void loop() {}
