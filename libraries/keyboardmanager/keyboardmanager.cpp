#include "keyboardmanager.h"

void KEYBD_read() {

  byte data = ((GPIOC->IDR & 0x0010) >> 4) + ((GPIOC->IDR & 0x0020) >> 4) + ((GPIOB->IDR & 0x0001) << 2) + ((GPIOB->IDR & 0x0002) << 2) + ((GPIOC->IDR & 0x0008) << 1) + ((GPIOC->IDR & 0x0004) << 3) + ((GPIOC->IDR & 0x0001) << 6) + ((GPIOA->IDR & 0x0001) << 7);

  GPIOJ->ODR = (((data & 0x00FE) >> 1) | (GPIOJ->ODR & ODRPORTJMask));
  GPIOG->ODR = (((data & 0x0001) << 13) | (GPIOG->ODR & ODRPORTGMask));

  GPIOA->ODR = GPIOA->ODR | 0x0080;
  GPIOA->ODR = GPIOA->ODR & 0xFF7F;

}

void KEYBD_setup() {
  
  pinMode(KEYBD_IRQ, INPUT);

  pinMode(IRQB_ACK, OUTPUT);
  digitalWrite(IRQB_ACK, LOW);

  GPIOC->MODER = GPIOC->MODER & ~0x00000300;
  GPIOC->MODER = GPIOC->MODER & ~0x00000C00;
  GPIOB->MODER = GPIOB->MODER & ~0x00000003;
  GPIOB->MODER = GPIOB->MODER & ~0x0000000C;
  GPIOC->MODER = GPIOC->MODER & ~0x000000C0;
  GPIOC->MODER = GPIOC->MODER & ~0x00000030;
  GPIOC->MODER = GPIOC->MODER & ~0x00000003;
  GPIOA->MODER = GPIOA->MODER & ~0x00000003;
  
  attachInterrupt(digitalPinToInterrupt(KEYBD_IRQ), KEYBD_read, RISING);

}
