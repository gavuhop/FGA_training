#include <stdint.h>
#include "Lib/CLOCK.h"
#include "Lib/GPIO.h"
#include "Lib/I2C.h"
#include "Lib/LCD.h"

#define PIN_BIT_BANG_DATA       PC->ODR.BIT0
#define PIN_BIT_BANG_CLOCK      PC->ODR.BIT1
#define PIN_ERROR               PC->ODR.BIT4

//
//  I2C device related constants.
//
#define DEVICE_ADDRESS          0x48
#define I2C_READ                1
#define I2C_WRITE               0
unsigned char _buffer[2];
int _nextByte = 0;

void Delay(){
  uint32_t time=40000;
  while(time--);
}
void I2C_init_CLOCK(){
        
       CLK->ICKR.CLOCK_HSION  = 1;                 //  Enable the HSI.
       //while (CLK->ICKR.CLOCK_HSIRDY == 0);       //  Wait for the HSI to be ready for use.
       CLK->DIVR.CLOCK_CKM = 0;                     //  Ensure the clocks are running at full speed.
       CLK->PCKENR1.CLOCK_PCKEN13 = 1;                 //  Enable I2C peripheral clocks.
       CLK->PCKENR2.CLOCK_PCKEN23 = 1;                 // enable LCD
       CLK->CLOCK_SWR = 0x01;                     //  Use HSI as the clock source.
       CLK->SWCR.CLOCK_SWEN = 1;                  //  Enable switching.
       while (CLK->SWCR.CLOCK_SWBSY != 0);        //  Pause while the clock switch is busy.
        
  //      while (CLK->SWCR.CLOCK_SWBSY);      //wait when clock switch on going
  //CLK->SWCR.CLOCK_SWEN =1;             //enable switch clock
  //CLK->CLOCK_SWR =0x01;                    //select HSI
  //while (CLK->CLOCK_SCSR !=0x01);          //wait for HSI selected
  //CLK->DIVR.CLOCK_CKM =0x0;            //000: System clock source/1  
  //CLK->PCKENR2.CLOCK_PCKEN23 =1;       //enable clock for lcd
  //CLK->PCKENR1.CLOCK_PCKEN13 =1;       //enable clock for i2c
        
}

void InitGpio(){
  //SDA
  PC->DDR.BIT0=1;            //OUITPUT            
  PC->CR1.BIT0=1;            //PUSH-PULL
  PC->CR2.BIT0=1;            //
 
  PC->DDR.BIT1=0;            //OUITPUT            
  PC->CR1.BIT1=1;            //PUSH-PULL
  PC->CR2.BIT1=1;            //

  PC->DDR.BIT7=1;
  PC->CR1.BIT7=1;
  PC->CR2.BIT7=1;
  PC->ODR.BIT7=1;
}
void BitBang(unsigned char byte)
{
    for (short bit = 7; bit >= 0; bit--)
    {
        if (byte & (1 << bit))
        {
            PC->ODR.BIT0 = 1;
        }
        else
        {
            PC->ODR.BIT0 = 0;
        }
        PC->ODR.BIT1 = 1;
        PC->ODR.BIT1 = 0;
    }
    PC->ODR.BIT0 = 0;
}

#pragma vector =31   // i2c
__interrupt void I2C_IRQHandler()
{
    if (I2C->I2C1_SR1.I2C_SB)// 
    {
        //
        //  Master mode, send the address of the peripheral we
        //  are talking to.  Reading SR1 clears the start condition.
        //
        //
        //  Send the slave address and the read bit.
        //
        I2C->I2C1_DR.I2C_DR = (DEVICE_ADDRESS << 1) | I2C_READ;
        //
        //  Clear the address registers.
        //
        I2C->I2C1_OARL.I2C_ADD = 0;
        I2C->I2C1_OARH.I2C_ADD = 0;
        return;
    }
    if (I2C->I2C1_SR1.I2C_ADDR)
    {
        //
        //  In master mode, the address has been sent to the slave.
        //  Clear the status registers and wait for some data from the salve.
        //
      PC->ODR.BIT7 =1;

        return;
    }
    if (I2C->I2C1_SR1.I2C_RXNE)
    {
        //
        //  The TMP102 temperature sensor returns two bytes of data
        //
        _buffer[_nextByte++] = I2C->I2C1_DR.I2C_DR;
        if (_nextByte == 1)
        {
            I2C->I2C1_CR2.I2C_ACK = 0;
            I2C->I2C1_CR2.I2C_STOP = 1;
        }
        else
        {
            BitBang(_buffer[0]);
            BitBang(_buffer[1]);
        }
        return;
    }
    //
    //  If we get here then we have an error so clear
    //  the error and continue.
    //
    //unsigned char reg = I2C->I2C1_SR1.I2C_ADDR;
    //;//reg = I2C_SR3;
    ///
    //  Send a diagnostic signal to indicate we have cleared 
    //  the error condition.
    //
    PIN_ERROR = 1;
    //__no_operation();
    PIN_ERROR = 0;
}
int main( void ){
  
  I2C_init_CLOCK();
  InitI2C_Master();
  //InitI2C_Slave();
  InitGpio();
   
  asm("rim\n");
  
  while(1){
      PC->ODR.BIT7 ^=1;
      Delay();
  }
  
  

  
  //return 0;
}
