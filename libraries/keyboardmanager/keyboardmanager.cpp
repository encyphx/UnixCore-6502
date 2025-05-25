#include "keyboardmanager.h"

void KEYBD_read() {

  byte data = (byte) ((GPIOC->IDR & 0x0010) >> 4) + ((GPIOC->IDR & 0x0020) >> 4) + ((GPIOB->IDR & 0x0001) << 2) + ((GPIOB->IDR & 0x0002) << 2) + ((GPIOC->IDR & 0x0008) << 1) + ((GPIOC->IDR & 0x0004) << 3) + ((GPIOC->IDR & 0x0001) << 6) + ((GPIOA->IDR & 0x0001) << 7)

  GPIOJ->ODR = (unsigned short) (((data & 0x00FE) >> 1) | (GPIOJ->ODR & ODRPORTJMask));
  GPIOG->ODR = (unsigned short) (((data & 0x0001) << 13) | (GPIOG->ODR & ODRPORTGMask));

  GPIOA->ODR = (unsigned short) GPIOA->ODR | 0x0080;
  GPIOA->ODR = (unsigned short) GPIOA->ODR & 0xFF7F;

}

void KEYBD_setup() {
  
  pinMode(KEYBD_IRQ, INPUT);

  GPIOC->MODER = (0x00000000 | (GPIOC->MODER & ~0x00000300));
  GPIOC->MODER = (0x00000000 | (GPIOC->MODER & ~0x00000C00));
  GPIOB->MODER = (0x00000000 | (GPIOB->MODER & ~0x00000003));
  GPIOB->MODER = (0x00000000 | (GPIOB->MODER & ~0x0000000C));
  GPIOC->MODER = (0x00000000 | (GPIOC->MODER & ~0x000000C0));
  GPIOC->MODER = (0x00000000 | (GPIOC->MODER & ~0x00000030));
  GPIOC->MODER = (0x00000000 | (GPIOC->MODER & ~0x00000003));
  GPIOA->MODER = (0x00000000 | (GPIOA->MODER & ~0x00000003));


  pinMode(IRQB_IRQ, OUTPUT);
  digitalWrite(IRQB_IRQ, LOW);
  
  attachInterrupt(digitalPinToInterrupt(KEYBD_IRQ), KEYBD_read, RISING);

}
