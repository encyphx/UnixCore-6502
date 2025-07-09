#include "rammanager.h"

byte RAM[24576];

void RAM_read() {

  uint16_t address = ((GPIOJ->IDR & 0x1000) << 3) + ((GPIOG->IDR & 0x1000) << 2) + ((GPIOJ->IDR & 0x4000) >> 1) + ((GPIOJ->IDR & 0x8000) >> 3) + ((GPIOK->IDR & 0x0008) << 8) + ((GPIOK->IDR & 0x0010) << 6) + ((GPIOK->IDR & 0x0020) << 4) + ((GPIOK->IDR & 0x0040) << 2) + (GPIOJ->IDR & 0x0080) + (GPIOE->IDR & 0x0040) + ((GPIOI->IDR & 0x8000) >> 10) + ((GPIOG->IDR & 0x0400) >> 6) + ((GPIOH->IDR & 0x8000) >> 12) + ((GPIOK->IDR & 0x0001) << 2) + ((GPIOI->IDR & 0x0800) >> 10) + ((GPIOK->IDR & 0x0004) >> 2);

  GPIOJ->ODR = (((RAM[address] & 0x00FE) >> 1) | (GPIOJ->ODR & ODRPORTJMask));
  GPIOG->ODR = (((RAM[address] & 0x0001) << 13) | (GPIOG->ODR & ODRPORTGMask));

}

void RAM_write() {

  uint16_t address = ((GPIOJ->IDR & 0x1000) << 3) + ((GPIOG->IDR & 0x1000) << 2) + ((GPIOJ->IDR & 0x4000) >> 1) + ((GPIOJ->IDR & 0x8000) >> 3) + ((GPIOK->IDR & 0x0008) << 8) + ((GPIOK->IDR & 0x0010) << 6) + ((GPIOK->IDR & 0x0020) << 4) + ((GPIOK->IDR & 0x0040) << 2) + (GPIOJ->IDR & 0x0080) + (GPIOE->IDR & 0x0040) + ((GPIOI->IDR & 0x8000) >> 10) + ((GPIOG->IDR & 0x0400) >> 6) + ((GPIOH->IDR & 0x8000) >> 12) + ((GPIOK->IDR & 0x0001) << 2) + ((GPIOI->IDR & 0x0800) >> 10) + ((GPIOK->IDR & 0x0004) >> 2);
  
  RAM[address] = (GPIOG->IDR & 0x0080) + ((GPIOE->IDR & 0x0030) << 1) + ((GPIOB->IDR & 0x0004) << 2) + ((GPIOI->IDR & 0x2000) >> 10) + ((GPIOI->IDR & 0x0400) >> 8) + ((GPIOK->IDR & 0x0080) >> 6) + ((GPIOI->IDR & 0x4000) >> 14);

}

void RAM_setup() {

  pinMode(RAM_RD_IRQ, INPUT);
  pinMode(RAM_WR_IRQ, INPUT);

  memset(RAM, 0x00, sizeof(byte)*24576);

  attachInterrupt(digitalPinToInterrupt(RAM_RD_IRQ), RAM_read, RISING);
  attachInterrupt(digitalPinToInterrupt(RAM_WR_IRQ), RAM_write, RISING);

}
