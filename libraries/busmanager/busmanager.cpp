#include "busmanager.h"

void BUS_write() {

  byte data = (GPIOG->IDR & 0x0080) + ((GPIOE->IDR & 0x0030) << 1) + ((GPIOB->IDR & 0x0004) << 2) + ((GPIOI->IDR & 0x2000) >> 10) + ((GPIOI->IDR & 0x0400) >> 8) + ((GPIOK->IDR & 0x0080) >> 6) + ((GPIOI->IDR & 0x4000) >> 14);
  
  GPIOD->ODR = (((data & 0x01) << 13) | (GPIOD->ODR & 0xDFFF));
  GPIOB->ODR = (((data & 0x02) << 3) | ((data & 0x0C) << 6) | (GPIOB->ODR & 0xFCEF));
  GPIOK->ODR = (((data & 0x10) >> 3) | (GPIOK->ODR & 0xFFFD));
  GPIOJ->ODR = (((data & 0x60) << 5) | (GPIOJ->ODR & 0xF3FF));
  GPIOH->ODR = (((data & 0x80) >> 1) | (GPIOH->ODR & 0xFFBF));
  
}

void BUS_setup() {

  pinMode(BUS_IRQ, INPUT);

  GPIOD->MODER = (0x04000000 | (GPIOD->MODER & ~0x0C000000));
  GPIOB->MODER = (0x00000100 | (GPIOB->MODER & ~0x00000300));
  GPIOB->MODER = (0x00010000 | (GPIOB->MODER & ~0x00030000));
  GPIOB->MODER = (0x00040000 | (GPIOB->MODER & ~0x000C0000));
  GPIOK->MODER = (0x00000004 | (GPIOK->MODER & ~0x0000000C));
  GPIOJ->MODER = (0x00100000 | (GPIOJ->MODER & ~0x00300000));
  GPIOJ->MODER = (0x00400000 | (GPIOJ->MODER & ~0x00C00000));
  GPIOH->MODER = (0x00001000 | (GPIOH->MODER & ~0x00003000));

  attachInterrupt(digitalPinToInterrupt(BUS_IRQ), BUS_write, RISING);

}
