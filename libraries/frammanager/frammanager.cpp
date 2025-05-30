#include "frammanager.h"

byte freeram[24064];

// (address >= 0x0200) && (address <= 0x5FFF)
void FRAM_read() {

  uint16_t address = ((GPIOJ->IDR & 0x1000) << 3) + ((GPIOG->IDR & 0x1000) << 2) + ((GPIOJ->IDR & 0x4000) >> 1) + ((GPIOJ->IDR & 0x8000) >> 3) + ((GPIOK->IDR & 0x0008) << 8) + ((GPIOK->IDR & 0x0010) << 6) + ((GPIOK->IDR & 0x0020) << 4) + ((GPIOK->IDR & 0x0040) << 2) + (GPIOJ->IDR & 0x0080) + (GPIOE->IDR & 0x0040) + ((GPIOI->IDR & 0x8000) >> 10) + ((GPIOG->IDR & 0x0400) >> 6) + ((GPIOH->IDR & 0x8000) >> 12) + ((GPIOK->IDR & 0x0001) << 2) + ((GPIOI->IDR & 0x0800) >> 10) + ((GPIOK->IDR & 0x0004) >> 2);

  GPIOJ->ODR = (((freeram[address - 0x0200] & 0x00FE) >> 1) | (GPIOJ->ODR & ODRPORTJMask));
  GPIOG->ODR = (((freeram[address - 0x0200] & 0x0001) << 13) | (GPIOG->ODR & ODRPORTGMask));

}

// (address >= 0x0200) && (address <= 0x5FFF)
void FRAM_write() {

  uint16_t address = ((GPIOJ->IDR & 0x1000) << 3) + ((GPIOG->IDR & 0x1000) << 2) + ((GPIOJ->IDR & 0x4000) >> 1) + ((GPIOJ->IDR & 0x8000) >> 3) + ((GPIOK->IDR & 0x0008) << 8) + ((GPIOK->IDR & 0x0010) << 6) + ((GPIOK->IDR & 0x0020) << 4) + ((GPIOK->IDR & 0x0040) << 2) + (GPIOJ->IDR & 0x0080) + (GPIOE->IDR & 0x0040) + ((GPIOI->IDR & 0x8000) >> 10) + ((GPIOG->IDR & 0x0400) >> 6) + ((GPIOH->IDR & 0x8000) >> 12) + ((GPIOK->IDR & 0x0001) << 2) + ((GPIOI->IDR & 0x0800) >> 10) + ((GPIOK->IDR & 0x0004) >> 2);

  freeram[address - 0x0200] = (GPIOG->IDR & 0x0080) + ((GPIOE->IDR & 0x0030) << 1) + ((GPIOB->IDR & 0x0004) << 2) + ((GPIOI->IDR & 0x2000) >> 10) + ((GPIOI->IDR & 0x0400) >> 8) + ((GPIOK->IDR & 0x0080) >> 6) + ((GPIOI->IDR & 0x4000) >> 14);

}

void FRAM_setup() {

  pinMode(FRAM_RD_IRQ, INPUT);
  pinMode(FRAM_WR_IRQ, INPUT);

  memset(freeram, 0x00, sizeof(byte)*24064);
  
  attachInterrupt(digitalPinToInterrupt(FRAM_RD_IRQ), FRAM_read, RISING);
  attachInterrupt(digitalPinToInterrupt(FRAM_WR_IRQ), FRAM_write, RISING);

}
