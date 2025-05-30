#include "stkmanager.h"

byte stack[256];

// (address >= 0x0100) && (address <= 0x01FF)
void STK_read() {

  uint16_t address = 0x0100 + (GPIOJ->IDR & 0x0080) + (GPIOE->IDR & 0x0040) + ((GPIOI->IDR & 0x8000) >> 10) + ((GPIOG->IDR & 0x0400) >> 6) + ((GPIOH->IDR & 0x8000) >> 12) + ((GPIOK->IDR & 0x0001) << 2) + ((GPIOI->IDR & 0x0800) >> 10) + ((GPIOK->IDR & 0x0004) >> 2);

  GPIOJ->ODR = (((stack[address - 0x0100] & 0x00FE) >> 1) | (GPIOJ->ODR & ODRPORTJMask));
  GPIOG->ODR = (((stack[address - 0x0100] & 0x0001) << 13) | (GPIOG->ODR & ODRPORTGMask));

}

// (address >= 0x0100) && (address <= 0x01FF)
void STK_write() {

  uint16_t address = 0x0100 + (GPIOJ->IDR & 0x0080) + (GPIOE->IDR & 0x0040) + ((GPIOI->IDR & 0x8000) >> 10) + ((GPIOG->IDR & 0x0400) >> 6) + ((GPIOH->IDR & 0x8000) >> 12) + ((GPIOK->IDR & 0x0001) << 2) + ((GPIOI->IDR & 0x0800) >> 10) + ((GPIOK->IDR & 0x0004) >> 2);

  stack[address - 0x0100] = (GPIOG->IDR & 0x0080) + ((GPIOE->IDR & 0x0030) << 1) + ((GPIOB->IDR & 0x0004) << 2) + ((GPIOI->IDR & 0x2000) >> 10) + ((GPIOI->IDR & 0x0400) >> 8) + ((GPIOK->IDR & 0x0080) >> 6) + ((GPIOI->IDR & 0x4000) >> 14);

}

void STK_setup() {

  pinMode(STK_RD_IRQ, INPUT);
  pinMode(STK_WR_IRQ, INPUT);

  memset(stack, 0x00, sizeof(byte)*256);
  
  attachInterrupt(digitalPinToInterrupt(STK_RD_IRQ), STK_read, RISING);
  attachInterrupt(digitalPinToInterrupt(STK_WR_IRQ), STK_write, RISING);

}
