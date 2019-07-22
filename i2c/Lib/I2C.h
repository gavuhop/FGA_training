#ifndef I2C
#include <stdint.h>
typedef struct{
  uint8_t I2C_PE:1; 
  //0: Peripheral disable
  //1: Peripheral enable: the corresponding I/Os are selected as alternate functions.
  uint8_t  I2C_SMBUS:1;
  //0: I2C mode
  //1: SMBus mode
  uint8_t  I2C_Reserved:1;
  uint8_t  I2C_SMBTYPE:1;
  //0: SMBus Device
  //1: SMBus Host
  uint8_t  I2C_ENARP:1;
  //0: ARP disabled
  //1: ARP enabled
  uint8_t  I2C_ENPEC:1;
  //0: PEC calculation disabled
  //1: PEC calculation enabled
  uint8_t  I2C_ENGC:1;
  //0: General call disabled. Address 0x00 is NACKed.
  //1: General call enabled. Address 0x00 is ACKed.
  uint8_t  I2C_NOSTRETCH:1;
  //0: Clock stretching enabled
  //1: Clock stretching disabled
}I2C1_CR1_TYPE; //Control register 1
//      7       6     5     4       3       2       1     0
//NOSTRETCH  ENGC  ENPEC  ENARP  SMBTYPE Reserved SMBUS  PE
//     rw      rw     rw    rw              rw     rw    rw
typedef struct{
      uint8_t  I2C_START:1;
      //spa In Master mode:
        //0: No Start generation
        //1: Repeated start generation
      //SPA In Slave mode:
        //0: No Start generation
        //1: Start generation when the bus is free
      uint8_t  I2C_STOP:1; // set and clear by software
      //SPA In Master mode:
          //0: No Stop generation.
          //1: Stop generation after the current byte transfer or after the current Start condition is sent.
          //SPA In Slave mode:
          //0: No Stop generation.
          //1: Release the SCL and SDA lines after the current byte transfer.
      uint8_t  I2C_ACK:1; //This bit is set and cleared by software and cleared by hardware when PE=0.
      //0: No acknowledge returned
      //1: Acknowledge returned after a byte is received (matched address or data)
      uint8_t  I2C_POS:1;//Acknowledge position
      //0: ACK bit controls the (N)ACK of the current byte being received in the shift register. The PEC bit
      //indicates the current byte in the shift register is PEC.
      //1: ACK bit controls the (N)ACK of the next byte which will be received in the shift register. The PEC
      //bit indicates the next byte in the shift register is PEC.
      uint8_t  I2C_PEC:1; //Packet error checking.
      //0: No PEC transfer
      //1: PEC transfer (in Tx or Rx mode)
      uint8_t  I2C_ALERT:1;
      //0: Releases SMBAlert pin high. Alert Response Address Header followed by NACK.
      //1: Drives SMBAlert pin low. Alert Response Address Header followed by ACK.
      uint8_t  I2C_Reserved:1; 
      uint8_t  I2C_SWRST:1;//Software reset
      //0: I2C Peripheral not at reset state
      //1: I2C Peripheral at reset state
}I2C1_CR2_TYPE; //Control register 2
//   7       6        5   4   3   2   1     0
//SWRST  Reserved  ALERT PEC POS ACK STOP START
//  rw                rw rw  rw  rw   rw   rw

typedef struct{
      uint8_t  I2C_FREQ:6;
      //The allowed range is between 1 MHz and 16 MHz
      //000000: not allowed
      //000001: 1 MHz
      //000010: 2 MHz
      //...
      //010000: 16 MHz
      //Higher values: not allowed
      uint8_t  I2C_Reserved:2;
}I2C1_FREQR_TYPE; //Frequency register
//      7 6                 5 4 3 2 1 0
//   Reserved                FREQ[5:0]
//      r                       rw

typedef struct{
      uint8_t  I2C_ADD0:1;
      //7-bit addressing mode: don't care
      //10-bit addressing mode: bit 0 of address
      uint8_t  I2C_ADD:7; //bits 7:1 of address
}I2C1_OARL_TYPE;//Own address register LSB

//    7 6 5 4 3 2 1              0
//      ADD[7:1]                ADD0
//       rw                     rw

typedef struct{
      uint8_t  I2C_Reserved1:1;
      uint8_t  I2C_ADD:2; //10-bit addressing mode: bits 9:8 of address.
      uint8_t  I2C_Reserved2:3;
      uint8_t  I2C_ADDCONF:1; //Address mode configuration
      //This bit must set by software (must always be written as 1 ).
      uint8_t  I2C_ADDMODE:1; //Addressing mode (Slave mode)
      //0: 7-bit slave address (10-bit address not acknowledged)
      //1: 10-bit slave address (7-bit address not acknowledged)              
}I2C1_OARH_TYPE; //Own address register MSB
  
//   7       6      5 4 3    2 1       0
//ADDMODE ADDCONF Reserved ADD[9:8] Reserved
//   rw     rw       r       rw        r
typedef struct{
      uint8_t  I2C_ENDUAL:1;//Dual addressing mode enable
      //0: Only OAR1 is recognized in 7-bit Addressing mode.
      // //1: Both OAR1 and OAR2 are recognized in 7-bit Addressing mode.
      uint8_t  I2C_ADD2:7; //Interface address
      //Bits 7:1 of address in Dual addressing mode.

}I2C_OAR2_TYPE;//Own address register 2


//     7 6 5 4 3 2 1       0
//      ADD2[7:1]       ENDUAL
//        rw              rw
typedef struct{
      uint8_t  I2C_DR:8;
      //-  Transmitter mode: Byte transmission starts automatically when a byte is written in the DR register. A
      //continuous transmit stream can be maintained if the next data to be transmitted is put in DR once
      //the transmission is started (TXE=1)
      //-  Receiver mode: Received byte is copied into DR (RXNE=1). A continuous transmit stream can be
      //maintained if DR is read before the next data is received (RXNE=1).
}I2C1_DR_TYPE;//Data register
//7 6 5 4 3 2 1 0
//   DR[7:0]
//     rw

typedef struct{
      uint8_t  I2C_SB:1;//Start bit (Master mode)
      //0: No Start condition
      //1: Start condition generated
      uint8_t  I2C_ADDR:1;//Address sent      
      //- Address matched (Slave)
      //0: Address mismatched or not received.
      //1: Received address matched
      //-  Address sent (Master)
      //0: No end of address transmission
      //1: End of address transmission
      uint8_t  I2C_BTF:1;
      //0: Data byte transfer not done
      //1: Data byte transfer succeeded
      uint8_t  I2C_ADD10:1; //10-bit header sent (Master mode)
//0: No ADD10 event occurred.
//1: Master has sent first address byte (header).
      uint8_t  I2C_STOPF:1;//Stop detection (Slave mode)
//0: No Stop condition detected
//1: Stop condition detected
      uint8_t  I2C_Reserved:1;
      uint8_t  I2C_RXNE:1;//Data register not empty
//0: Data register empty
//1: Data register not empty
      uint8_t  I2C_TXE:1;//Data register empty (transmitters)
      //0: Data register not empty
      //1: Data register empty              
}I2C1_SR1_TYPE;//Status register 1
//  7   6      5      4     3    2    1   0
//TXE RXNE Reserved STOPF ADD10 BTF ADDR SB
// r    r      r      r     r    r   r   r
typedef struct{
      uint8_t  I2C_BERR:1;//Bus error
//0: No misplaced Start or Stop condition
//1: Misplaced Start or Stop condition
      uint8_t  I2C_ARLO:1;//Arbitration lost (master mode)
//0: No Arbitration lost detected
//1: Arbitration lost detected
      uint8_t  I2C_AF:1;
//0: No acknowledge failure
//1: Acknowledge failure
      uint8_t  I2C_OVR:1;//Overrun/underrun
//0: No overrun/underrun
//1: Overrun or underrun
      uint8_t  I2C_PECERR:1;//PEC Error in reception
//0: no PEC error: receiver returns ACK after PEC reception (if ACK=1)
//1: PEC error: receiver returns NACK after PEC reception (whatever ACK)
      uint8_t  I2C_WUFH:1;//Wakeup from Halt
//0: no wakeup from Halt mode
//1: 7-bit address or header match in Halt mode (slave mode) or Halt entered when in master mode.
      uint8_t  I2C_TIMEOUT:1;//Timeout or Tlow error
//0: No timeout error
//1: SCL remained low for 25 ms (timeout)
      uint8_t  I2C_SMBALERT:1;//SMBus alert
//In SMBus host mode:
//0: no SMBAlert
//1: SMBAlert event occurred on pin
//In SMBus slave mode:
//0: no SMBAlert response address header
//1: SMBAlert response address header to SMBAlert LOW received
}I2C1_SR2_TYPE;//Status register 2
//    7            6       5        4      3    2      1      0
//SMBALERT     TIMEOUT   WUFH    PECERR   OVR   AF   ARLO   BERR
// rc_w0        rc_w0   rc_w0     rc_w0  rc_w0 rc_w0 rc_w0  rc_w0
typedef struct{
      uint8_t  I2C_MSL:1;
      //Master/Slave
//0: Slave mode
//1: Master mode
      uint8_t  I2C_BUSY:1;//Bus busy
//0: No communication on the bus
//1: Communication ongoing on the bus      
      uint8_t  I2C_TRA:1;//Transmitter/Receiver
//0: Data bytes received
//1: Data bytes transmitted      
      uint8_t  I2C_Reserved:1;
      uint8_t  I2C_GENCALL:1;//General call header (Slave mode)
//0: No general call
//1: General call header received when ENGC=1      
      uint8_t  I2C_SMBDEFAULT:1;
      uint8_t  I2C_SMBHOST:1;
      uint8_t  I2C_DUALF:1;//Dual flag (Slave mode)
//0: Received address matched with OAR1
//1: Received address matched with OAR2      

}I2C1_SR3_TYPE;//Status register 3
//    7      6          5         4         3      2    1     0
// DUALF  SMBHOST  SMBDEFAULT  GENCALL  Reserved  TRA  BUSY  MSL
//   r       r          r         r         r      r    r     r
typedef struct{
      uint8_t  I2C_ITERREN:1;//Error interrupt enable
//0: Error interrupt disabled
//1: Error interrupt enabled
      uint8_t  I2C_ITEVTEN:1;//Event interrupt enable
//0: Event interrupt disabled
//1: Event interrupt enabled
      uint8_t  I2C_ITBUFEN:1;//Buffer interrupt enable
//0: TXE = 1 or RXNE = 1 does not generate any interrupt.
//1:TXE = 1 or RXNE = 1 generates Event interrupt.
      uint8_t  I2C_DMAEN:1;//DMA requests enable
//0: DMA requests disabled
//1: DMA request enabled when TxE=1 or RxNE =1
      uint8_t  I2C_LAST:1;//DMA last transfer
//0: Next DMA EOT is not the last transfer
//1: Next DMA EOT is the last transfer
      uint8_t  I2C_Reserved:3;
}I2C1_ITR_TYPE;//Interrupt and DMA register
// 7 6 5      4     3       2         1       0
//Reserved  LAST  DMAEN  ITBUFEN  ITEVTEN  ITERREN
//   r       rw     rw      rw       rw      rw              
typedef struct{
      uint8_t  I2C_CCR:8;//Clock control register (Master mode)
     
}I2C1_CCRL_TYPE;//Clock control register low
//7 6 5 4 3 2 1 0
//    CCR[7:0]
//      rw
typedef struct{
      uint8_t  I2C_CCR:4;//Clock control register in Fast/Standard mode (Master mode)(1)
      uint8_t  I2C_Reserved:2;
      uint8_t  I2C_DUTY:1;//Fast mode duty cycle
      //0: Fast mode tlow/thigh = 2
      //1: Fast mode tlow/thigh = 16/9 (see CCR)
      uint8_t  I2C_FS:1;//2C master mode selection
      //0: Standard mode I2C
      //1: Fast mode I2C
}I2C1_CCRH_TYPE;//Clock control register high
//  7     6       5 4       3 2 1 0
//F/S   DUTY   Reserved    CCR[11:8]
// rw    rw       r          rw
typedef struct{
      uint8_t  I2C_TRISE:6;//Maximum rise time in Fast/Standard mode (Master mode)
//These bits should provide the maximum duration of the SCL feedback loop in master mode. The
//purpose is to keep a stable SCL frequency whatever the SCL rising edge duration.
//These bits must be programmed with the maximum SCL rise time given in the I2C bus specification,
//incremented by 1
      uint8_t  I2C_Reserved:2;
}I2C1_TRISER_TYPE;//TRISE register
//   7 6         5 4 3 2 1 0
//Reserved       TRISE[5:0]
//   r              rw
typedef struct{
      
      uint8_t  I2C_PEC:8;//Packet error checking register
  /*This register contains the internal PEC when ENPEC=1.*/    
}I2C1_PECR_TYPE;//PEC register
// 7 6 5 4 3 2 1 0
//   PEC[7:0]
//     rw
typedef struct{
     I2C1_CR1_TYPE              I2C1_CR1;     
     I2C1_CR2_TYPE              I2C1_CR2;
     I2C1_FREQR_TYPE            I2C1_FREQR;
     I2C1_OARL_TYPE             I2C1_OARL;
     I2C1_OARH_TYPE             I2C1_OARH;
     I2C_OAR2_TYPE              I2C_OAR2;
     I2C1_DR_TYPE               I2C1_DR;
     I2C1_SR1_TYPE              I2C1_SR1;
     I2C1_SR2_TYPE              I2C1_SR2;
     I2C1_SR3_TYPE              I2C1_SR3;
     I2C1_ITR_TYPE              I2C1_ITR;
     I2C1_CCRL_TYPE             I2C1_CCRL;
     I2C1_CCRH_TYPE             I2C1_CCRH;
     I2C1_TRISER_TYPE           I2C1_TRISER;
     I2C1_PECR_TYPE             I2C1_PECR;
}I2C_TYPE;

#define I2C ((volatile I2C_TYPE *)0x5210)

uint8_t I2C1_Read();
void I2C1_Write(uint8_t data);
void I2C1_Start();
void I2C1_Stop();
void I2C1_Select_Slave(uint8_t address,uint8_t mode);
void InitI2C_Master();
void InitI2C_Slave();
#endif