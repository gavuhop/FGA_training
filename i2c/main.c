#ifndef GPIO   // if not define
#pragma once

#include<stdint.h>

typedef struct{
  uint8_t BIT0:1;
  uint8_t BIT1:1;
  uint8_t BIT2:1;
  uint8_t BIT3:1;
  uint8_t BIT4:1;
  uint8_t BIT5:1;
  uint8_t BIT6:1;
  uint8_t BIT7:1;
}BYTE_TYPE;

typedef struct{
  BYTE_TYPE ODR;
  BYTE_TYPE IDR;
  BYTE_TYPE DDR;
  BYTE_TYPE CR1;
  BYTE_TYPE CR2;
}PORT_TYPE;
#define PA ((volatile PORT_TYPE *)0x5000)

#define PB ((volatile PORT_TYPE *)0x5005)

#define PC ((volatile PORT_TYPE *)0x500A)

#define PD ((volatile PORT_TYPE *)0x500F)

#define PE ((volatile PORT_TYPE *)0x5014)

#define PF ((volatile PORT_TYPE *)0x5019)
#endif  // end if
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CLOCK
#define CLOCK

//CLK_DIVR_TYPE
//Reserved        CKM[2:0]
//- - - - -       rw rw rw
typedef struct {
//000: System clock source/1
//001: System clock source /2
//010: System clock source /4
//011: System clock source /8
//100: System clock source /16
//101: System clock source /32
//110: System clock source /64
//111: System clock source /128
//These bits are written by software to define the system clock prescaling factor.
  uint8_t CKM:3;
  uint8_t Reserved:5;
}CLK_DIVR_TYPE; 

//CLK_CRTCR_TYPE
//RTCDIV2 RTCDIV1 RTCDIV0 RTCSEL3 RTCSEL2 RTCSEL1 RTCSEL0 RTCSWBSY
//rw      rw      rw      rw      rw      rw      rw      r
typedef struct {
//This bit is set by hardware any time a valid clock change for RTC is required.
//It is reset when the RTC clock change procedure is complete.
  uint8_t RTCSWBSY  :1;
//0000: No clock selected
//0001: HSI clock used as RTC clock source
//0010: LSI clock used as RTC clock source
//0100: HSE clock used as RTC clock source
//1000: LSE clock used as RTC clock source
  uint8_t RTCSEL0   :1;
  uint8_t RTCSEL1   :1;
  uint8_t RTCSEL2   :1;
  uint8_t RTCSEL3   :1;
//000: RTC clock source/1
//001: RTC clock source /2
//010: RTC clock source /4
//011: RTC clock source /8
//100: RTC clock source /16
//101: RTC clock source /32
//110: RTC clock source /64
//111: RTC clock source /128
  uint8_t RTCDIV0   :1;
  uint8_t RTCDIV1   :1;
  uint8_t RTCDIV2   :1;

}CLK_CRTCR_TYPE;

//CLK_ICKCR_TYPE
//  Reserved    BEEPAHALT       FHWU     SAHALT  LSIRDY  LSION   HSIRDY  HSION
//  -           rw              rw       rw      r       rw      r       rw
typedef struct {

  
//This bit is set and cleared by software. It is set by hardware whenever the HSI oscillator is required, for
//example:
//? When activated as safe oscillator by the CSS
//? When switching to HSI clock (see CLK_SWR register)
//? When HSI is selected as the active CCO source, RTC clock
//? When exiting Halt/Active-halt in fast wake up mode
//It cannot be cleared when HSI is selected as system clock (CLK_SCSR register), as active CCO
//source, as active RTC clock or if the safe oscillator (AUX) is enabled.
//0: High-speed internal RC OFF
//1: High-speed internal RC ON
  uint8_t HSION  :1;
//This bit is set and cleared by hardware.
//0: HSI clock not ready
//1: HSI clock ready
  uint8_t HSIRDY   :1;
//example:
//? When switching to the LSI clock (see CLK_SWR register)
//? When LSI is selected as the active CCO source (see CLK_CCOR register)
//? When LSI is selected as the active RTC clock source (see CLK_CRTCR register)
//? When LSI is selected as the active BEEP clock source (see CLK_CBEEPR register)
//? When LSI measurement is enabled (MSR bit set in the BEEP_CSR1 register)
//It cannot be cleared when LSI is selected
//? as system clock source (CLK_SCSR register)
//? as active CCO source
//? as clock source for the BEEP peripheral while BEEPAHALT bit is set
//? or as active clock source for RTC.
//0: Low speed internal RC OFF
//1: Low speed internal RC ON
  uint8_t LSION   :1;
//This bit is set and cleared by hardware.
//0: LSI clock not ready
//1: LSI clock ready
  uint8_t LSIRDY   :1;
//This bit is set and cleared by software. When it is set, the main voltage regulator is powered off as
//soon as the MCU enters Active-halt mode, so the wakeup time is longer.
//0: MVR regulator ON in HALT/Active-halt mode
//1: MVR regulator OFF in HALT/Active-halt mode
  uint8_t SAHALT   :1;
//This bit is set and cleared by software.
//0: Fast wakeup from Halt/Active-halt modes disabled: system clock is the last selected clock source
//before entering Halt/Active-halt mode
//1: Fast wakeup from Halt/Active-halt modes enabled: HSI/8 used as system clock source after
//wakeup from Halt/Active-halt
  uint8_t FHWU   :1;
//This bit is set and cleared by software.
//0: BEEP clock is switched off during Halt mode or Active-halt mode
//1: BEEP clock is kept running during Halt mode
  uint8_t BEEPAHALT   :1;

  uint8_t Reserved   :1;

}CLK_ICKCR_TYPE;
//////////////////////
//PCKEN1[7:0]
//rw rw rw rw rw rw rw rw
//0: SYSCLK to peripheral disabled
//1: SYSCLK to peripheral enabled
//PCKEN17 DAC
//PCKEN16 BEEP
//PCKEN15 USART1
//PCKEN14 SPI1
//PCKEN13 I2C1
//PCKEN12 TIM4
//PCKEN11 TIM3
//PCKEN10 TIM2
//////////////////////
typedef struct {
  uint8_t PCKEN10:1;
  uint8_t PCKEN11:1;
  uint8_t PCKEN12:1;
  uint8_t PCKEN13:1;
  uint8_t PCKEN14:1;
  uint8_t PCKEN15:1;
  uint8_t PCKEN16:1;
  uint8_t PCKEN17:1;
}CLK_PCKENR1_TYPE;



//CLK_PCKENR2_TYPE
//PCKEN27       Reserved        PCKEN2[5:0]
//rw            -               rw rw rw rw rw rw
//PCKEN27(1) Boot ROM
//PCKEN25 COMP1 and COMP2
//PCKEN24 DMA1
//PCKEN23 LCD
//PCKEN22 RTC
//PCKEN21 TIM1
//PCKEN20 ADC1
typedef struct {
  uint8_t PCKEN20  :1;
  uint8_t PCKEN21  :1;
  uint8_t PCKEN22  :1;
  uint8_t PCKEN23  :1;
  uint8_t PCKEN24  :1;
  uint8_t PCKEN25  :1;
  uint8_t Reserved   :1;
//0: SYSCLK to peripheral disabled
//1: SYSCLK to peripheral enabled
  uint8_t PCKEN27   :1;

}CLK_PCKENR2_TYPE;



//CLK_CCOR_TYPE
//7 6 5         4 3 2 1                 0
//CCODIV[2:0]   CCOSEL[3:0]             CCOSWBSY
//rw rw rw      rw rw rw rw             r
//Configurable clock output register CLK_CCOR
typedef struct {
//This bit is set and cleared by hardware. It indicates that the selected CCO clock source is being
//switched-on and stabilized. While CCOSWBSY is set, the CCOSEL bits and CCODIV bits are writeprotected.
//CCOSWBSY remains set until the CCO clock is enabled.
//0: CCO clock not busy
//1: CCO clock busy
  uint8_t CCOSWBSY  :1;
//These bits are written by software to select the source of the output clock available on the CCO pin.
//0000: Clock output disabled, no clock output on CCO pin
//0001: HSI clock output on CCO pin
//0010: LSI clock output on CCO pin
//0100: HSE clock output on CCO pin
//1000: LSE clock output on CCO pin
//Note: Any write with a non valid target code will be skipped.
//The content of these bits is frozen and write protected when CCOSWBSY is set.
  uint8_t CCOSEL   :4;
//These bits are written by software to select the clock CCO division factor.
//000: CCO
//001: CCO divided by 2
//010: CCO divided by 4
//011: CCO divided by 8
//100: CCO divided by 16
//101: CCO divided by 32
//110: CCO divided by 64
//111: CCO divided by 64
//Note: Any write with a non valid target code will be skipped.
//The content of these bits is frozen and write protected when CCOSWBSY is set.
  uint8_t CCODIV   :3;

}CLK_CCOR_TYPE;



//CLK_ECKCR_TYPE
//7 6           5        4       3       2       1       0
//Reserved      LSEBYP   HSEBYP  LSERDY  LSEON   HSERDY  HSEON
//-             rw       rw      r       rw      r       rw
//External clock register (CLK_ECKCR)
typedef struct {
//  This bit is set and cleared by software. It can be used to switch the external crystal oscillator ON or
//OFF. It is set by hardware in the following cases:
//? When switching to HSE clock (see CLK_SWR register)
//? When HSE is selected as the active CCO source (see CLK_CCOR register)
//? When HSE is selected as the active RTC source (see CLK_CRTCR register)
//It cannot be cleared when HSE is selected as system clock (indicated in CLK_   register) or as
//the active CCO source or as active RTC clock source.
//0: HSE clock OFF
//1: HSE clock ON
   uint8_t HSEON      :1;
//   This bit is set and cleared by hardware.
//0: HSE clock not ready
//1: HSE clock ready (HSE clock is stabilized and available)
   uint8_t HSERDY     :1;
//   This bit is set and cleared by software. It can be used to switch the external crystal oscillator on or off.
//It is set by hardware in the following cases:
//? When switching to LSE clock (see CLK_SWR register)
//? When LSE is selected as the active CCO source (see CLK_CCOR register)
//? When LSE is selected as the active RTC source (see CLK_CRTCR register)
//? When LSE is selected as the active BEEP source (see CLK_CBEPR register)
//It cannot be cleared when LSE is selected
//? as system clock source (CLK_SCSR register),
//? as active CCO source
//? as clock source for the BEEP peripheral and BEEPAHALT bit is set
//? or as active clock source for RTC.
//0: LSE clock off
//1: LSE clock on
   uint8_t LSEON      :1;
//This bit is set and cleared by hardware.
//0: LSE clock not ready
//1: LSE clock ready (LSE clock is stabilized and available)
//Note: the user must wait for the LSE startup time tSU(LSE) to get a stabilized frequency.
   uint8_t LSERDY     :1;
//Set and reset by software in debug for bypassing the oscillator with the external clock. This bit can be
//written only if the external 1-16 MHz oscillator is disabled.
//0: external 1-16 MHz oscillator not bypassed
//1: external 1-16 MHz oscillator bypassed with external clock
   uint8_t HSEBYP     :1;
//Set and reset by software to bypass the oscillator. This bit can be written only when the
//external low speed oscillator is disabled.
//0: LSE oscillator not bypassed
//1: LSE oscillator bypassed
   uint8_t LSEBYP     :1;
   uint8_t Reserved   :2;
 
}CLK_ECKCR_TYPE;



//7 6 5 4 3 2 1 0
//CKM[7:0]
//r r r r r r r r
//System clock status register (CLK_SCSR)




//CLK_SWCR_TYPE
//7 6 5 4         3        2       1      0
//Reserved        SWIF     SWIEN   SWEN   SWBSY
//-               rc_w0    rw      rw     rw
//Switch control register (CLK_SWCR)
typedef struct{
//  This bit is set and cleared by hardware. It can be cleared by software to reset the clock switch process.
//0: No clock switch ongoing
//1: Clock switch ongoing
  uint8_t SWBSY:1;
//  This bit is set and cleared by software. Writing a 1 to this bit enables switching the system clock to the
//source defined in the CLK_SWR register.
//0: Disable clock switch execution
//1: Enable clock switch execution
  uint8_t SWEN:1;
//  This bit is set and cleared by software.
//0: Clock switch interrupt disabled
//1: Clock switch interrupt enabled
  uint8_t SWIEN:1;
//  This bit is set by hardware when the SWIEN bit is set and cleared by software writing 0. Its meaning
//depends on the status of the SWEN bit. Refer to Figure 19 and Figure 20.
//? In manual switching mode (SWEN=0):
//0: Target clock source not ready
//1: Target clock source ready
//? In automatic switching mode (SWEN=1):
//0: No clock switch event occurred
//1: Clock switch event occurred
  uint8_t SWIF:1;
  uint8_t Reserved:4;

}CLK_SWCR_TYPE;



//CLK_CSSR_TYPE
//7 6 5    4       3      2      1   0
//Reserved CSSDGON CSSD   CSSDIE AUX CSSEN
//-        rw      rc_w0  rw     r   rwo
//Clock security system register (CLK_CSSR)
typedef struct{
//This bit can be written once-only by software. It cannot be reset before the next device reset.
//0: Clock security system OFF
//1: Clock security system ON
  uint8_t CSSEN:1;
//This bit is set and cleared by hardware.
//0: Auxiliary oscillator is OFF.
//1: Auxiliary oscillator (HSI) is ON and selected as current system clock source.
  uint8_t AUX:1;
//This bit is set and cleared by software.
//0: Clock security system interrupt disabled
//1: Clock security system interrupt enabled
  uint8_t CSSDIE:1;
//This bit is set by hardware and only cleared by device reset.
//0: CSS is OFF or no HSE crystal clock disturbance detected.
//1: HSE crystal clock disturbance detected.
  uint8_t CSSD:1;
//  This bit, when set, avoids any clock glitch generated during the HSE switch-off executed by the CSS
//mechanism.
  uint8_t CSSDGON:1;
  
  uint8_t Reserved:3;
}CLK_CSSR_TYPE;

//CLK_CBEEPR_TYPE
//7 6 5 4 3       2               1       0
//Reserved        CLKBEEPSEL1 CLKBEEPSEL0 BEEPSWBSY
//-               rw          rw          r
//Clock BEEP register (CLK_CBEEPR)
typedef struct{
//This bit is set by hardware any time a valid clock change for BEEP is required.
//It is reset when the BEEP clock change procedure is complete
  uint8_t BEEPSWBSY:1;
//These bits are set by software to select the clock source to be used by the BEEP.
//00: No clock selected
//01: LSI clock used as BEEP clock source
//10: LSE clock used as BEEP clock source
//Note: Any write with a non valid target code will be skipped.
//The content of these bits is frozen and write protected when BEEPSWBSY is set.
  uint8_t CLKBEEPSEL0:1;
  uint8_t CLKBEEPSEL1:1;
  
  uint8_t Reserved:5;
}CLK_CBEEPR_TYPE;


//7 6 5 4 3 2 1 0
//HSICAL[7:0]
//r r r r r r r r
//HSI calibration register (CLK_HSICALR)
//This register is initially loaded with the factory calibration value used to trim the HSI oscillator.


//7 6 5 4 3 2 1 0
//HSITRIM[7:0]
//rw rw rw rw rw rw rw rw
//HSI clock calibration trimming register (CLK_HSITRIMR)
//To ensure the best HSI clock accuracy, the value to be written to this register should be within the
//following range: [(HSICALR regiter value) -12] < x < [(HSICALR regiter value) + 8 ].
//Note: Once this register configured, its value is used instead of the HSICALR register values.
//These bits are used by the application to choose/change the HSI oscillator trimming value. A
//hardware protection can be provided to avoid erroneous write access to this register, refer to
//the CLK_HSIUNLCK register.

//7 6 5 4 3 2 1 0
//HSIUNLCK[7:0]
//rw rw rw rw rw rw rw rw
//HSI unlock register (CLK_HSIUNLCKR)
//This register is used by the application for both unlocking the hardware write protection of HSITRIM
//register and enabling the use of HSITRIM as trimming value for HSI oscillator.
//The HSITRIM unlock/enable procedure consists in:
//1) two consecutive write accesses at this address, the first one with the value 0xAC and the second
//one with the value 0x35
//2) a write access to the HSITRIM register.
//Note: When this procedure is correctly completed the HSITRIM will be locked again


//CLK_REGCSR_TYPE
//7               6        5       4       3       2       1       0
//EEREADY         EEBUSY   LSEPD   HSEPD   LSIPD   HSIPD   REGOFF  REGREADY
//r                r       r       r       r       r       rw      r
//Main regulator control status register (CLK_REGCSR)

typedef struct{
//  The REGREADY bit indicates the main regulator status: this bit is set when the main regulator is ready
//to provide the full power.
  uint8_t REGREADY:1;
//  This bit enables the direct switch-off of the main regulator regardless of the REGREADY flag status
//0: The main regulator follows the standard functionality
//1: The main regulator is switched off and all clocks are provided without taking into account the
//REGREADY flag status
  uint8_t REGOFF:1;
//  This bit indicates the status of the oscillator
//0: HSI oscillator ON
//1: HSI oscillator OFF
  uint8_t HSIPD:1;
//  This bit indicates the status of the LSI oscillator
//0: LSI oscillator ON
//1: LSI oscillator OFF
  uint8_t LSIPD:1;
//  This bit indicates the status of the HSE oscillator
//0: HSE oscillator ON
//1: HSE oscillator OFF
  uint8_t HSEPD:1;
//  This bit indicates the status of the LSE oscillator
//0: LSE oscillator ON
//1: LSE oscillator OFF
  uint8_t LSEPD:1;
//  This bit indicates if the Flash program memory and Data EEPROM ready are busy
//0: Flash program memory and Data EEPROM not busy
//1: Flash program memory and Data EEPROM busy
  uint8_t EEBUSY:1;
//  This bit indicated if the Flash program memory and Data EEPROM are ready
//0: Flash program memory and Data EEPROM not ready
//1: Flash program memory and Data EEPROM ready
  uint8_t EEREADY:1;
  
  

}CLK_REGCSR_TYPE;

typedef struct{
  CLK_DIVR_TYPE DIVR;
  CLK_CRTCR_TYPE CRTCR;
  CLK_ICKCR_TYPE ICKR;
  CLK_PCKENR1_TYPE PCKENR1;
  CLK_PCKENR2_TYPE PCKENR2;
  CLK_CCOR_TYPE CCOR;
  CLK_ECKCR_TYPE ECKR;
  uint8_t SCSR;
  uint8_t SWR;
  CLK_SWCR_TYPE SWCR;
  CLK_CSSR_TYPE CSSR;
  CLK_CBEEPR_TYPE CBEEPR;
  uint8_t HSICALR;
  uint8_t HSITRIMR;
  uint8_t HSIUNLCKR;
  CLK_REGCSR_TYPE REGCSR;
} CLK_TYPE;

#define CLK ((volatile CLK_TYPE *)0x50C0)

#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef I2C

typedef struct{
  uint8_t _PE:1; 
  //0: Peripheral disable
  //1: Peripheral enable: the corresponding I/Os are selected as alternate functions.
  uint8_t _SMBUS:1;
  //0: I2C mode
  //1: SMBus mode
  uint8_t _Reserved:1;
  uint8_t _SMBTYPE:1;
  //0: SMBus Device
  //1: SMBus Host
  uint8_t _ENARP:1;
  //0: ARP disabled
  //1: ARP enabled
  uint8_t _ENPEC:1;
  //0: PEC calculation disabled
  //1: PEC calculation enabled
  uint8_t _ENGC:1;
  //0: General call disabled. Address 0x00 is NACKed.
  //1: General call enabled. Address 0x00 is ACKed.
  uint8_t _NOSTRETCH:1;
  //0: Clock stretching enabled
  //1: Clock stretching disabled
}I2C1_CR1_TYPE;

typedef struct{
      uint8_t _START:1;
      //– In Master mode:
        //0: No Start generation
        //1: Repeated start generation
      //– In Slave mode:
        //0: No Start generation
        //1: Start generation when the bus is free
      uint8_t _STOP:1; // set and clear by software
      //– In Master mode:
          //0: No Stop generation.
          //1: Stop generation after the current byte transfer or after the current Start condition is sent.
          //– In Slave mode:
          //0: No Stop generation.
          //1: Release the SCL and SDA lines after the current byte transfer.
      uint8_t _ACK:1; //This bit is set and cleared by software and cleared by hardware when PE=0.
      //0: No acknowledge returned
      //1: Acknowledge returned after a byte is received (matched address or data)
      uint8_t _POS:1;//Acknowledge position
      //0: ACK bit controls the (N)ACK of the current byte being received in the shift register. The PEC bit
      //indicates the current byte in the shift register is PEC.
      //1: ACK bit controls the (N)ACK of the next byte which will be received in the shift register. The PEC
      //bit indicates the next byte in the shift register is PEC.
      uint8_t _PEC:1; //Packet error checking.
      //0: No PEC transfer
      //1: PEC transfer (in Tx or Rx mode)
      uint8_t _ALERT:1;
      //0: Releases SMBAlert pin high. Alert Response Address Header followed by NACK.
      //1: Drives SMBAlert pin low. Alert Response Address Header followed by ACK.
      uint8_t _Reserved:1; 
      uint8_t _SWRST:1;//Software reset
      //0: I2C Peripheral not at reset state
      //1: I2C Peripheral at reset state
}I2C1_CR2_TYPE;


typedef struct{
      uint8_t _FREQ:6;
      //The allowed range is between 1 MHz and 16 MHz
      //000000: not allowed
      //000001: 1 MHz
      //000010: 2 MHz
      //...
      //010000: 16 MHz
      //Higher values: not allowed
      uint8_t _Reserved:2;
}I2C1_FREQR_TYPE;


typedef struct{
      uint8_t _ADD0:1;
      //7-bit addressing mode: don’t care
      //10-bit addressing mode: bit 0 of address
      uint8_t _ADD:7; //bits 7:1 of address
}I2C1_OARL_TYPE;

typedef struct{
      uint8_t _Reserved1:1;
      uint8_t _ADD:2; //10-bit addressing mode: bits 9:8 of address.
      uint8_t _Reserved2:3;
      uint8_t _ADDCONF:1; //Address mode configuration
      //This bit must set by software (must always be written as ‘1’).
      uint8_t _ADDMODE:1; //Addressing mode (Slave mode)
      //0: 7-bit slave address (10-bit address not acknowledged)
      //1: 10-bit slave address (7-bit address not acknowledged)              
}I2C1_OARH_TYPE;
              
typedef struct{
      uint8_t _ENDUAL:1;//Dual addressing mode enable
      //0: Only OAR1 is recognized in 7-bit Addressing mode.
      // //1: Both OAR1 and OAR2 are recognized in 7-bit Addressing mode.
      uint8_t _ADD2:7; //Interface address
      //Bits 7:1 of address in Dual addressing mode.

}I2C_OAR2_TYPE;

typedef struct{
      uint8_t _DR:8;
      //– Transmitter mode: Byte transmission starts automatically when a byte is written in the DR register. A
      //continuous transmit stream can be maintained if the next data to be transmitted is put in DR once
      //the transmission is started (TXE=1)
      //– Receiver mode: Received byte is copied into DR (RXNE=1). A continuous transmit stream can be
      //maintained if DR is read before the next data is received (RXNE=1).
}I2C1_DR_TYPE;

typedef struct{
      uint8_t _SB:1;//Start bit (Master mode)
      //0: No Start condition
      //1: Start condition generated
      uint8_t _ADDR:1;//Address sent      
      //– Address matched (Slave)
      //0: Address mismatched or not received.
      //1: Received address matched
      //– Address sent (Master)
      //0: No end of address transmission
      //1: End of address transmission
      uint8_t _BTF:1;
      //0: Data byte transfer not done
      //1: Data byte transfer succeeded
      uint8_t _ADD10:1; //10-bit header sent (Master mode)
//0: No ADD10 event occurred.
//1: Master has sent first address byte (header).
      uint8_t _STOPF:1;//Stop detection (Slave mode)
//0: No Stop condition detected
//1: Stop condition detected
      uint8_t _Reserved:1;
      uint8_t _RXNE:1;//Data register not empty
//0: Data register empty
//1: Data register not empty
      uint8_t _TXE:1;//Data register empty (transmitters)
      //0: Data register not empty
      //1: Data register empty              
}I2C1_SR1_TYPE;

typedef struct{
      uint8_t _BERR:1;//Bus error
//0: No misplaced Start or Stop condition
//1: Misplaced Start or Stop condition
      uint8_t _ARLO:1;//Arbitration lost (master mode)
//0: No Arbitration lost detected
//1: Arbitration lost detected
      uint8_t _AF:1;
//0: No acknowledge failure
//1: Acknowledge failure
      uint8_t _OVR:1;//Overrun/underrun
//0: No overrun/underrun
//1: Overrun or underrun
      uint8_t _PECERR:1;//PEC Error in reception
//0: no PEC error: receiver returns ACK after PEC reception (if ACK=1)
//1: PEC error: receiver returns NACK after PEC reception (whatever ACK)
      uint8_t _WUFH:1;//Wakeup from Halt
//0: no wakeup from Halt mode
//1: 7-bit address or header match in Halt mode (slave mode) or Halt entered when in master mode.
      uint8_t _TIMEOUT:1;//Timeout or Tlow error
//0: No timeout error
//1: SCL remained low for 25 ms (timeout)
      uint8_t _SMBALERT:1;//SMBus alert
//In SMBus host mode:
//0: no SMBAlert
//1: SMBAlert event occurred on pin
//In SMBus slave mode:
//0: no SMBAlert response address header
//1: SMBAlert response address header to SMBAlert LOW received
}I2C1_SR2_TYPE;

typedef struct{
      uint8_t _MSL:1;
      //Master/Slave
//0: Slave mode
//1: Master mode
      uint8_t _BUSY:1;//Bus busy
//0: No communication on the bus
//1: Communication ongoing on the bus      
      uint8_t _TRA:1;//Transmitter/Receiver
//0: Data bytes received
//1: Data bytes transmitted      
      uint8_t _Reserved:1;
      uint8_t _GENCALL:1;//General call header (Slave mode)
//0: No general call
//1: General call header received when ENGC=1      
      uint8_t _SMBDEFAULT:1;
      uint8_t _SMBHOST:1;
      uint8_t _DUALF:1;//Dual flag (Slave mode)
//0: Received address matched with OAR1
//1: Received address matched with OAR2      

}I2C1_SR3_TYPE;

typedef struct{
      uint8_t _ITERREN:1;//Error interrupt enable
//0: Error interrupt disabled
//1: Error interrupt enabled
      uint8_t _ITEVTEN:1;//Event interrupt enable
//0: Event interrupt disabled
//1: Event interrupt enabled
      uint8_t _ITBUFEN:1;//Buffer interrupt enable
//0: TXE = 1 or RXNE = 1 does not generate any interrupt.
//1:TXE = 1 or RXNE = 1 generates Event interrupt.
      uint8_t _DMAEN:1;//DMA requests enable
//0: DMA requests disabled
//1: DMA request enabled when TxE=1 or RxNE =1
      uint8_t _LAST:1;//DMA last transfer
//0: Next DMA EOT is not the last transfer
//1: Next DMA EOT is the last transfer
      uint8_t _Reserved:3;
}I2C1_ITR_TYPE;
              
typedef struct{
      uint8_t _CCR:8;//Clock control register (Master mode)
     
}I2C1_CCRL_TYPE;

typedef struct{
      uint8_t _CCR:4;//Clock control register in Fast/Standard mode (Master mode)(1)
      uint8_t _Reserved:2;
      uint8_t _DUTY:1;//Fast mode duty cycle
      //0: Fast mode tlow/thigh = 2
      //1: Fast mode tlow/thigh = 16/9 (see CCR)
      uint8_t _FS:1;//2C master mode selection
      //0: Standard mode I2C
      //1: Fast mode I2C
}I2C1_CCRH_TYPE;

typedef struct{
      uint8_t _TRISE:6;//Maximum rise time in Fast/Standard mode (Master mode)
//These bits should provide the maximum duration of the SCL feedback loop in master mode. The
//purpose is to keep a stable SCL frequency whatever the SCL rising edge duration.
//These bits must be programmed with the maximum SCL rise time given in the I2C bus specification,
//incremented by 1
      uint8_t _Reserved:2;
}I2C1_TRISER_TYPE;

typedef struct{
      
      uint8_t _PEC:8;//Packet error checking register
  /*This register contains the internal PEC when ENPEC=1.*/    
}I2C1_PECR_TYPE;

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


#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    I2C->I2C1_TRISER._TRISE  =1;
    

    return 0;
}
