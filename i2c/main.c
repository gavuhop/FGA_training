#include <stdint.h>
#include "Lib/CLOCK.h"
#include "Lib/GPIO.h"
#include "Lib/I2C.h"

#define DEVICE_ADDRESS          0x48
#define I2C_READ                1
#define I2C_WRITE               0
unsigned char _buffer[2];
int _nextByte = 0;
void Init_I2C(){
        I2C->I2C1_CR1.I2C_PE = 0;//Peripheral disable
        //  Setup the clock information.
        I2C->I2C1_FREQR.I2C_FREQ = 0x10; // set frequency 16MHz
        I2C->I2C1_CCRH.I2C_FS = 0;      // standar mode
        I2C->I2C1_CCRL.I2C_CCR = 0xa0; //  160 
        I2C->I2C1_CCRH.I2C_CCR = 0x00;
        //  Set the address of this device.
        I2C->I2C1_OARH.I2C_ADDMODE = 0;            //  7 bit address mode.
        I2C->I2C1_OARH.I2C_ADDCONF = 1;            //  Docs say this must always be 1.
        //  Setup the bus characteristics.
        I2C->I2C1_TRISER.I2C_TRISE = 0x17;         // 23 
        //  Turn on the interrupts.
        I2C->I2C1_ITR.I2C_ITBUFEN = 1;                //  Buffer interrupt enabled.
        I2C->I2C1_ITR.I2C_ITEVTEN = 1;               //  Event interrupt enabled.
        I2C->I2C1_ITR.I2C_ITERREN = 1;
        //  Configuration complete so turn the peripheral on.
        I2C->I2C1_CR1.I2C_PE = 1; // must turn on after config
        //  Enter master mode.
        I2C->I2C1_CR2.I2C_ACK = 1;
        I2C->I2C1_CR2.I2C_START = 1;
}


void I2C_init_CLOCK(){
        
        CLK->ICKR.CLOCK_HSION  = 1;                 //  Enable the HSI.
        
        while (CLK->ICKR.CLOCK_HSIRDY == 0);       //  Wait for the HSI to be ready for use.
        CLK->DIVR.CLOCK_CKM = 0;                     //  Ensure the clocks are running at full speed.
        CLK->PCKENR1.CLOCK_PCKEN13 = 1;                 //  Enable I2C peripheral clocks.
        CLK->PCKENR2.CLOCK_PCKEN23 = 1;                 // enable LCD
        //CLK->CLOCK_HSITRIMR = 0;                   //  Turn off any HSIU trimming.
        CLK->SWCR.CLOCK_SWIEN = 0;                    //  Set SWIM to run at clock / 2.
        CLK->CLOCK_SWR = 0x01;                     //  Use HSI as the clock source.
        CLK->SWCR.CLOCK_SWEN = 1;                  //  Enable switching.
        while (CLK->SWCR.CLOCK_SWBSY != 0);        //  Pause while the clock switch is busy.
        
}

#pragma vector = 31
      __interrupt void I2C_IRQHandler()
        
        {
        if (I2C->I2C1_SR1.I2C_SB)
            {
            //
        //  Master mode, send the address of the peripheral we
        //  are talking to.  Reading SR1 clears the start condition.
        //
            //reg = I2C->I2C1_SR1;
        //
        //  Send the slave address and the read bit.
        //
            I2C->I2C1_DR.I2C_DR = (0x48<<1)|1 ;
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
            //reg = I2C->SR1;
           // reg = I2C->SR3;
            return;
        }
        if (I2C->I2C1_SR1.I2C_RXNE)
        {
        //  The TMP102 temperature sensor returns two bytes of data
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
        //  If we get here then we have an error so clear
        //  the error and continue.
        //unsigned char reg = I2C_SR1;
        //reg = I2C->SR3;
        
}

int main( void ){
  
  //Init_I2C();
  
  
  

  
  return 0;
}
