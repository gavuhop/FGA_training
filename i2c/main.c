#include <stdint.h>
#include "Lib/CLOCK.h"
#include "Lib/GPIO.h"
#include "Lib/I2C.h"

void Init_I2C(){
        CLK->PCKENR1.CLOCK_PCKEN13 = 1;
        I2C->I2C1_CR1.I2C_PE = 0;//Peripheral enable
        //  Setup the clock information.
        I2C->I2C1_FREQR.I2C_FREQ = 0x10; // set frequency 16MHz
        I2C->I2C1_CCRH.I2C_FS = 0;
        I2C->I2C1_CCRL.I2C_CCR = 0xa0;
        I2C->I2C1_CCRH.I2C_CCR = 0x00;
        //  Set the address of this device.
        I2C->I2C1_OARH.I2C_ADDMODE = 0;            //  7 bit address mode.
        I2C->I2C1_OARH.I2C_ADDCONF = 1;            //  Docs say this must always be 1.
        //  Setup the bus characteristics.
        I2C->I2C1_TRISER.I2C_TRISE = 0x17;
        //  Turn on the interrupts.
        I2C->I2C1_ITR.I2C_ITBUFEN = 1;                //  Buffer interrupt enabled.
        I2C->I2C1_ITR.I2C_ITEVTEN = 1;               //  Event interrupt enabled.
        I2C->I2C1_ITR.I2C_ITERREN = 1;
        //  Configuration complete so turn the peripheral on.
        I2C->I2C1_CR1.I2C_PE = 1;
        //  Enter master mode.
        I2C->I2C1_CR2.I2C_ACK = 1;
        I2C->I2C1_CR2.I2C_START = 1;
}

void I2C_recive(){

}

void I2C_transfer(){


}

int main( void ){
  
  //Init_I2C();
  
  
  
  
  return 0;
}
