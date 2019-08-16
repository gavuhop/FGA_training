#include <stdint.h>


#define CLK_DIVR	(*(volatile uint8_t *)0x50c0)
#define CLK_PCKENR2	(*(volatile uint8_t *)0x50c4)

#define TIM1_CR1	(*(volatile uint8_t *)0x52b0)
#define TIM1_PCNTRH	(*(volatile uint8_t *)0x52bf)
#define TIM1_PCNTRL	(*(volatile uint8_t *)0x52c0)
#define TIM1_PSCRH	(*(volatile uint8_t *)0x52c1)
#define TIM1_PSCRL	(*(volatile uint8_t *)0x52c2)





typedef struct GPIO_lse{
      uint8_t ODR;
      uint8_t IDR;
      uint8_t DDR;
      uint8_t CR1;
      uint8_t CR2;
  
}GPIO_TYPE;

#define PE ((GPIO_TYPE *) 0x5014)
#define PC ((GPIO_TYPE *) 0x500A)
#define PA ((GPIO_TYPE *) 0x5000)
#define PB ((GPIO_TYPE *) 0x5005)
#define PD ((GPIO_TYPE *) 0x500F)
#define PF ((GPIO_TYPE *) 0x5019)


#define EXTI_CR1        *(uint8_t *)    0x50A0
#define EXTI_CR2        *(uint8_t *)    0x50A1
#define EXTI_SR1        *(uint8_t *)    0x50A3
#define EXTI_CONF1      *(uint8_t *)    0x50A5

#define SBit(VAR, Place)         ((VAR) |= ((1<< Place)))
#define CBit(VAR, Place)         ((VAR) &=~ ((1<<Place)))

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80




unsigned int clock(void)
{
	unsigned char h = TIM1_PCNTRH;
	unsigned char l = TIM1_PCNTRL;
	return((unsigned int)(h) << 8 | l);
}



//EXTI_CR1
//EXTI_SR1
//ITC_SPR3


//EXTI_CONF1


//EXTI_CR1 kieu tac donglen chan de sinh ra ngat
//P3IS[1:0] P2IS[1:0] P1IS[1:0] P0IS[1:0]
//P1IS[1:0]: Portx bit 1 external interrupt sensitivity bits
//These bits can only be written when I1 and I0 in the CCR register are both set to 1 (level 3). They
//define the sensitivity of bit 1 of Port A, B, C, D and/or E external interrupts.
//00: Falling edge and low level
//01: Rising edge only
//10: Falling edge only
//11: Rising and falling edge




//EXTI_SR1 Trang thai cua ngat
//P7F P6F P5F P4F P3F P2F P1F P0F
//Bits 7:0 PxF: Port A/B/C/D/E/F bit x external interrupt flag
//These bits are set by hardware when an interrupt event occurs on the corresponding pin.They are
//cleared by writing a ‘1’ by software.
//0: No interrupt
//1: External interrupt pending
void Delay(uint32_t time){
  while (time){
    time--;
  }
}

#pragma vector=14
__interrupt void button1(){
      PC->ODR ^= BIT7;
      Delay(30000);
      PE->ODR ^= BIT7;  
      Delay(30000);  
      PE->ODR ^= (1<<7);
      EXTI_SR1 |= (1<<1);
}
#pragma vector = 15
__interrupt void button2(){
      PC->ODR ^= BIT7;
      Delay(30000);
      PE->ODR ^= BIT7;  
      Delay(30000);  
      PE->ODR ^= (1<<7);
      EXTI_SR1 |= (1<<4);
}
#pragma vector = 16
__interrupt void stop(){
      PC->ODR ^= BIT7;
      Delay(30000);
      PE->ODR ^= BIT7;  
      Delay(30000);  
      PE->ODR ^= (1<<7);
      EXTI_SR1 |= (1<<5);
}
#pragma vector = 17
__interrupt void cancel(){
      PC->ODR ^= BIT7;
      Delay(30000);
      PE->ODR ^= BIT7;  
      Delay(30000);  
      PE->ODR ^= (1<<7);
      EXTI_SR1 |= (1<<6);
}

int main(){
   PC->DDR |= BIT7;
        PC->ODR &=~BIT7;
  PC->CR1 |= BIT7;
  PC->CR2 &=~BIT7;
  
  PE->DDR |= BIT7;
  PE->ODR &=~BIT7;
  PE->CR1 |= BIT7;
  PE->CR2 &=~BIT7;
  
  PC->DDR &=~BIT1;
  PC->CR1 |=BIT1;
  PC->CR2 |=BIT1;
  PD->DDR &= ~((BIT4)|(BIT5)|(BIT6)|(BIT7));
  PD->CR1 |= ((BIT4)|(BIT5)|(BIT6)|(BIT7));
  PD->CR2 |= ((BIT4)|(BIT5)|(BIT6)|(BIT7));
  
  //EXTI_CR2 |= (2<<0)|(2<<2)|(2<<4);
  
  // chon cach tac dong interrupt
  EXTI_CR1&=~(BIT3+BIT2);  //Falling edge and low level
  // set muc uu tien
  //EXTI_CONF1
  asm("rim\n"); 
  while (1){    
      
  }
  
}