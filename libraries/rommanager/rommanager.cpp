#include "rommanager.h"

byte lowrom[16384] = L_HEXCODE;
byte highrom[16384] = H_HEXCODE;

// (address >= 0x8000) && (address <= 0xBFFF)
void LROM_read() {

  uint16_t address = 0x8000 + ((GPIOJ->IDR & 0x4000) >> 1) + ((GPIOJ->IDR & 0x8000) >> 3) + ((GPIOK->IDR & 0x0008) << 8) + ((GPIOK->IDR & 0x0010) << 6) + ((GPIOK->IDR & 0x0020) << 4) + ((GPIOK->IDR & 0x0040) << 2) + (GPIOJ->IDR & 0x0080) + (GPIOE->IDR & 0x0040) + ((GPIOI->IDR & 0x8000) >> 10) + ((GPIOG->IDR & 0x0400) >> 6) + ((GPIOH->IDR & 0x8000) >> 12) + ((GPIOK->IDR & 0x0001) << 2) + ((GPIOI->IDR & 0x0800) >> 10) + ((GPIOK->IDR & 0x0004) >> 2);

  GPIOJ->ODR = (((lowrom[address - 0x8000] & 0x00FE) >> 1) | (GPIOJ->ODR & ODRPORTJMask));
  GPIOG->ODR = (((lowrom[address - 0x8000] & 0x0001) << 13) | (GPIOG->ODR & ODRPORTGMask));

}

// (address >= 0xC000) && (address <= 0xFFFF)
void HROM_read() {

  uint16_t address = 0xC000 + ((GPIOJ->IDR & 0x4000) >> 1) + ((GPIOJ->IDR & 0x8000) >> 3) + ((GPIOK->IDR & 0x0008) << 8) + ((GPIOK->IDR & 0x0010) << 6) + ((GPIOK->IDR & 0x0020) << 4) + ((GPIOK->IDR & 0x0040) << 2) + (GPIOJ->IDR & 0x0080) + (GPIOE->IDR & 0x0040) + ((GPIOI->IDR & 0x8000) >> 10) + ((GPIOG->IDR & 0x0400) >> 6) + ((GPIOH->IDR & 0x8000) >> 12) + ((GPIOK->IDR & 0x0001) << 2) + ((GPIOI->IDR & 0x0800) >> 10) + ((GPIOK->IDR & 0x0004) >> 2);

  GPIOJ->ODR = (((highrom[address - 0xC000] & 0x00FE) >> 1) | (GPIOJ->ODR & ODRPORTJMask));
  GPIOG->ODR = (((highrom[address - 0xC000] & 0x0001) << 13) | (GPIOG->ODR & ODRPORTGMask));

}

void ROM_setup() {

  pinMode(LROM_RD_IRQ, INPUT);
  pinMode(HROM_RD_IRQ, INPUT);

  if (L_SIZE < 16384) {
    memset(&lowrom[L_SIZE], 0x00, sizeof(byte)*(16384-L_SIZE));
  }

  memset(&highrom[H_SIZE], 0x00, sizeof(byte)*(16384-H_SIZE));

  highrom[16380] = 0x00;
  highrom[16381] = 0x80;

  highrom[16382] = FFFE;
  highrom[16383] = FFFF;

  attachInterrupt(digitalPinToInterrupt(LROM_RD_IRQ), LROM_read, RISING);
  attachInterrupt(digitalPinToInterrupt(HROM_RD_IRQ), HROM_read, RISING);

}

void reset() {

  pinMode(RST, OUTPUT);

  digitalWrite(RST, HIGH);
  delay(1000);
  digitalWrite(RST, LOW);
  delay(1000);
  digitalWrite(RST, HIGH);

}
