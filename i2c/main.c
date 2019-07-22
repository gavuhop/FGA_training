#include <stdint.h>
<<<<<<< HEAD

#include "Lib/GPIO.h"
#include "Lib/CLOCK.h"
#include "Lib/I2C.h"
#include "lib/LCD.h"
=======
#include "Lib/CLOCK.h"
#include "Lib/GPIO.h"
#include "Lib/I2C.h"
>>>>>>> ba29e34b980676b1b3ac14b11f19153c41371274
unsigned char reg;
uint8_t total;
#define I2C_WRITE 0
#define I2C_READ 1

void I2C_init_CLOCK(){
        
        CLK->ICKR.CLOCK_HSION  = 1;                 //  Enable the HSI.
        while (CLK->ICKR.CLOCK_HSIRDY == 0);       //  Wait for the HSI to be ready for use.
        CLK->DIVR.CLOCK_CKM = 0;                     //  Ensure the clocks are running at full speed.
        CLK->PCKENR1.CLOCK_PCKEN13 = 1;                 //  Enable I2C peripheral clocks.
        CLK->PCKENR2.CLOCK_PCKEN23 = 1;                 // enable LCD
        CLK->CLOCK_SWR = 0x01;                     //  Use HSI as the clock source.
        CLK->SWCR.CLOCK_SWEN = 1;                  //  Enable switching.
        while (CLK->SWCR.CLOCK_SWBSY != 0);        //  Pause while the clock switch is busy.
        
}



int main( void ){
<<<<<<< HEAD
  I2C_init_CLOCK();
  InitI2C_Master();
  InitI2C_Slave();
  
  
  

  
=======
  
  //Init_I2C();
  
  
  

  
>>>>>>> ba29e34b980676b1b3ac14b11f19153c41371274
  return 0;
}
