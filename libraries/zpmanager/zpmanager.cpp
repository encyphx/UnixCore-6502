#include "zpmanager.h"

byte zeropage[256];

// (address >= 0x0000) && (address <= 0x00FF)
void ZP_read() {

  unsigned int address = (unsigned int) (GPIOJ->IDR & 0x0080) + (GPIOE->IDR & 0x0040) + ((GPIOI->IDR & 0x8000) >> 10) + ((GPIOG->IDR & 0x0400) >> 6) + ((GPIOH->IDR & 0x8000) >> 12) + ((GPIOK->IDR & 0x0001) << 2) + ((GPIOI->IDR & 0x0800) >> 10) + ((GPIOK->IDR & 0x0004) >> 2);

  GPIOJ->ODR = (unsigned short) (((zeropage[address] & 0x00FE) >> 1) | (GPIOJ->ODR & ODRPORTJMask));
  GPIOG->ODR = (unsigned short) (((zeropage[address] & 0x0001) << 13) | (GPIOG->ODR & ODRPORTGMask));

}

// (address >= 0x0000) && (address <= 0x00FF)
void ZP_write() {

  unsigned int address = (unsigned int) (GPIOJ->IDR & 0x0080) + (GPIOE->IDR & 0x0040) + ((GPIOI->IDR & 0x8000) >> 10) + ((GPIOG->IDR & 0x0400) >> 6) + ((GPIOH->IDR & 0x8000) >> 12) + ((GPIOK->IDR & 0x0001) << 2) + ((GPIOI->IDR & 0x0800) >> 10) + ((GPIOK->IDR & 0x0004) >> 2);

  zeropage[address] = (byte) (GPIOG->IDR & 0x0080) + ((GPIOE->IDR & 0x0030) << 1) + ((GPIOB->IDR & 0x0004) << 2) + ((GPIOI->IDR & 0x2000) >> 10) + ((GPIOI->IDR & 0x0400) >> 8) + ((GPIOK->IDR & 0x0080) >> 6) + ((GPIOI->IDR & 0x4000) >> 14);

}

void ZP_setup() {

  pinMode(ZP_RD_IRQ, INPUT);
  pinMode(ZP_WR_IRQ, INPUT);

  memset(zeropage, 0x00, sizeof(byte)*256);
  
  attachInterrupt(digitalPinToInterrupt(ZP_RD_IRQ), ZP_read, RISING);
  attachInterrupt(digitalPinToInterrupt(ZP_WR_IRQ), ZP_write, RISING);

}
