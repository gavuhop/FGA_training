#include "I2C.h"

uint8_t I2C1_Read(){
  I2C->I2C1_CR2.I2C_ACK=0;
  I2C_Stop();
  while (!I2C->I2C1_SR1.I2C_RXNE){}
  return I2C->I2C1_DR.I2C_DR;
  
}
void I2C1_Write(uint8_t data){
  I2C->I2C1_DR.I2C_DR=data;
  while (!I2C->I2C1_SR1.I2C_TXE);

}
void I2C1_Start(){
  I2C->I2C1_CR2.I2C_START=1;
  I2C->I2C1_CR2.I2C_ACK=1;
  while (!I2C->I2C1_SR1.I2C_SB);
}
void I2C1_Stop(){
  I2C->I2C1_CR2.I2C_STOP=1;
  while (!I2C->I2C1_SR3.I2C_MSL);
}
void I2C1_Select_Slave(uint8_t address,uint8_t mode){
  uint8_t data=(address<<1)+mode;
  I2C->I2C1_DR.I2C_DR=data;
  while (!I2C->I2C1_SR1.I2C_ADDR);
  data='a';
}



void InitI2C_Master(){
   I2C->I2C1_CR1.I2C_PE=0;              //disable i2c
   //clock of i2c
   I2C->I2C1_FREQR.I2C_FREQ=0x10;       //16MHZ         =>Tc=1/16000000 (s);
   I2C->I2C1_CCRH.I2C_FS=0;             //Standard mode I2C
   I2C->I2C1_CCRL.I2C_CCR=0x50;         //
   I2C->I2C1_CCRH.I2C_CCR=0x00;
   //address deveice
   I2C->I2C1_OARL.I2C_ADD=0x32;         //address master=0x32
   
   I2C->I2C1_OARH.I2C_ADDCONF=1;        //this bit must set by software (always=1)
   //
   
   //
   
   I2C->I2C1_CR1.I2C_SMBUS=0;   
   I2C->I2C1_TRISER.I2C_TRISE=0x11;     //  I2C_FREQ+1   
   
   //interupt
//   I2C->I2C1_ITR.I2C_ITBUFEN=1;         //  Buffer interrupt enabled.
//   I2C->I2C1_ITR.I2C_ITERREN=1;                 
//   I2C->I2C1_ITR.I2C_ITEVTEN=1;         //  Event interrupt enabled.
   //
   
//   
//   I2C->I2C1_FREQR.I2C_FREQ=0x2;
//   I2C->I2C1_CCRL.I2C_CCR=0x000A; 
   I2C->I2C1_CR1.I2C_PE=1;              //enable i2c
   //
   I2C->I2C1_CR2.I2C_ACK=0;
   I2C->I2C1_CR2.I2C_START=0;           //
}
void InitI2C_Slave(){
        I2C->I2C1_CR1.I2C_PE = 0;//Peripheral disable
        //  Setup the clock information.
        I2C->I2C1_FREQR.I2C_FREQ = 0x10; // set frequency 16MHz
        I2C->I2C1_CCRH.I2C_FS = 0;      // standar mode
        I2C->I2C1_CCRL.I2C_CCR = 0xa0; //  160 
        I2C->I2C1_CCRH.I2C_CCR = 0x00;
        //  Set the address of this device.
        I2C->I2C1_OARH.I2C_ADDMODE = 0;            //  7 bit address mode.
        I2C->I2C1_OARH.I2C_ADD = 0;
        I2C->I2C1_OARL.I2C_ADD = 0x50;        
        I2C->I2C1_OARH.I2C_ADDCONF = 1;            //  Docs say this must always be 1.
        //  Setup the bus characteristics.
        I2C->I2C1_TRISER.I2C_TRISE = 0x11;         // 17 
        //  Turn on the interrupts.
//        I2C->I2C1_ITR.I2C_ITBUFEN = 1;                //  Buffer interrupt enabled.
//        I2C->I2C1_ITR.I2C_ITEVTEN = 1;               //  Event interrupt enabled.
//        I2C->I2C1_ITR.I2C_ITERREN = 1;
        //  Configuration complete so turn the peripheral on.
        I2C->I2C1_CR1.I2C_PE = 1; // must turn on after config
        //  Enter master mode.
        I2C->I2C1_CR2.I2C_ACK = 1;
   
   
}