#ifndef CLOCK
#define CLOCK
#include <stdint.h>
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
  uint8_t  CLOCK_CKM:3;
  uint8_t  CLOCK_Reserved:5;
}CLK_DIVR_TYPE; 

//CLK_CRTCR_TYPE
//RTCDIV2 RTCDIV1 RTCDIV0 RTCSEL3 RTCSEL2 RTCSEL1 RTCSEL0 RTCSWBSY
//rw      rw      rw      rw      rw      rw      rw      r
typedef struct {
//This bit is set by hardware any time a valid clock change for RTC is required.
//It is reset when the RTC clock change procedure is complete.
  uint8_t  CLOCK_RTCSWBSY  :1;
//0000: No clock selected
//0001: HSI clock used as RTC clock source
//0010: LSI clock used as RTC clock source
//0100: HSE clock used as RTC clock source
//1000: LSE clock used as RTC clock source
  uint8_t  CLOCK_RTCSEL0   :1;
  uint8_t  CLOCK_RTCSEL1   :1;
  uint8_t  CLOCK_RTCSEL2   :1;
  uint8_t  CLOCK_RTCSEL3   :1;
//000: RTC clock source/1
//001: RTC clock source /2
//010: RTC clock source /4
//011: RTC clock source /8
//100: RTC clock source /16
//101: RTC clock source /32
//110: RTC clock source /64
//111: RTC clock source /128
  uint8_t  CLOCK_RTCDIV0   :1;
  uint8_t  CLOCK_RTCDIV1   :1;
  uint8_t  CLOCK_RTCDIV2   :1;

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
  uint8_t  CLOCK_HSION  :1;
//This bit is set and cleared by hardware.
//0: HSI clock not ready
//1: HSI clock ready
  uint8_t  CLOCK_HSIRDY   :1;
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
  uint8_t  CLOCK_LSION   :1;
//This bit is set and cleared by hardware.
//0: LSI clock not ready
//1: LSI clock ready
  uint8_t  CLOCK_LSIRDY   :1;
//This bit is set and cleared by software. When it is set, the main voltage regulator is powered off as
//soon as the MCU enters Active-halt mode, so the wakeup time is longer.
//0: MVR regulator ON in HALT/Active-halt mode
//1: MVR regulator OFF in HALT/Active-halt mode
  uint8_t  CLOCK_SAHALT   :1;
//This bit is set and cleared by software.
//0: Fast wakeup from Halt/Active-halt modes disabled: system clock is the last selected clock source
//before entering Halt/Active-halt mode
//1: Fast wakeup from Halt/Active-halt modes enabled: HSI/8 used as system clock source after
//wakeup from Halt/Active-halt
  uint8_t  CLOCK_FHWU   :1;
//This bit is set and cleared by software.
//0: BEEP clock is switched off during Halt mode or Active-halt mode
//1: BEEP clock is kept running during Halt mode
  uint8_t  CLOCK_BEEPAHALT   :1;

  uint8_t  CLOCK_Reserved   :1;

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
  uint8_t  CLOCK_PCKEN10:1;
  uint8_t  CLOCK_PCKEN11:1;
  uint8_t  CLOCK_PCKEN12:1;
  uint8_t  CLOCK_PCKEN13:1;
  uint8_t  CLOCK_PCKEN14:1;
  uint8_t  CLOCK_PCKEN15:1;
  uint8_t  CLOCK_PCKEN16:1;
  uint8_t  CLOCK_PCKEN17:1;
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
  uint8_t  CLOCK_PCKEN20  :1;
  uint8_t  CLOCK_PCKEN21  :1;
  uint8_t  CLOCK_PCKEN22  :1;
  uint8_t  CLOCK_PCKEN23  :1;
  uint8_t  CLOCK_PCKEN24  :1;
  uint8_t  CLOCK_PCKEN25  :1;
  uint8_t  CLOCK_Reserved   :1;
//0: SYSCLK to peripheral disabled
//1: SYSCLK to peripheral enabled
  uint8_t  CLOCK_PCKEN27   :1;

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
  uint8_t  CLOCK_CCOSWBSY  :1;
//These bits are written by software to select the source of the output clock available on the CCO pin.
//0000: Clock output disabled, no clock output on CCO pin
//0001: HSI clock output on CCO pin
//0010: LSI clock output on CCO pin
//0100: HSE clock output on CCO pin
//1000: LSE clock output on CCO pin
//Note: Any write with a non valid target code will be skipped.
//The content of these bits is frozen and write protected when CCOSWBSY is set.
  uint8_t  CLOCK_CCOSEL   :4;
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
  uint8_t  CLOCK_CCODIV   :3;

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
   uint8_t  CLOCK_HSEON      :1;
//   This bit is set and cleared by hardware.
//0: HSE clock not ready
//1: HSE clock ready (HSE clock is stabilized and available)
   uint8_t  CLOCK_HSERDY     :1;
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
   uint8_t  CLOCK_LSEON      :1;
//This bit is set and cleared by hardware.
//0: LSE clock not ready
//1: LSE clock ready (LSE clock is stabilized and available)
//Note: the user must wait for the LSE startup time tSU(LSE) to get a stabilized frequency.
   uint8_t  CLOCK_LSERDY     :1;
//Set and reset by software in debug for bypassing the oscillator with the external clock. This bit can be
//written only if the external 1-16 MHz oscillator is disabled.
//0: external 1-16 MHz oscillator not bypassed
//1: external 1-16 MHz oscillator bypassed with external clock
   uint8_t  CLOCK_HSEBYP     :1;
//Set and reset by software to bypass the oscillator. This bit can be written only when the
//external low speed oscillator is disabled.
//0: LSE oscillator not bypassed
//1: LSE oscillator bypassed
   uint8_t  CLOCK_LSEBYP     :1;
   uint8_t  CLOCK_Reserved   :2;
 
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
  uint8_t  CLOCK_SWBSY:1;
//  This bit is set and cleared by software. Writing a 1 to this bit enables switching the system clock to the
//source defined in the CLK_SWR register.
//0: Disable clock switch execution
//1: Enable clock switch execution
  uint8_t  CLOCK_SWEN:1;
//  This bit is set and cleared by software.
//0: Clock switch interrupt disabled
//1: Clock switch interrupt enabled
  uint8_t  CLOCK_SWIEN:1;
//  This bit is set by hardware when the SWIEN bit is set and cleared by software writing 0. Its meaning
//depends on the status of the SWEN bit. Refer to Figure 19 and Figure 20.
//? In manual switching mode (SWEN=0):
//0: Target clock source not ready
//1: Target clock source ready
//? In automatic switching mode (SWEN=1):
//0: No clock switch event occurred
//1: Clock switch event occurred
  uint8_t  CLOCK_SWIF:1;
  uint8_t  CLOCK_Reserved:4;

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
  uint8_t  CLOCK_CSSEN:1;
//This bit is set and cleared by hardware.
//0: Auxiliary oscillator is OFF.
//1: Auxiliary oscillator (HSI) is ON and selected as current system clock source.
  uint8_t  CLOCK_AUX:1;
//This bit is set and cleared by software.
//0: Clock security system interrupt disabled
//1: Clock security system interrupt enabled
  uint8_t  CLOCK_CSSDIE:1;
//This bit is set by hardware and only cleared by device reset.
//0: CSS is OFF or no HSE crystal clock disturbance detected.
//1: HSE crystal clock disturbance detected.
  uint8_t  CLOCK_CSSD:1;
//  This bit, when set, avoids any clock glitch generated during the HSE switch-off executed by the CSS
//mechanism.
  uint8_t  CLOCK_CSSDGON:1;
  
  uint8_t  CLOCK_Reserved:3;
}CLK_CSSR_TYPE;

//CLK_CBEEPR_TYPE
//7 6 5 4 3       2               1       0
//Reserved        CLKBEEPSEL1 CLKBEEPSEL0 BEEPSWBSY
//-               rw          rw          r
//Clock BEEP register (CLK_CBEEPR)
typedef struct{
//This bit is set by hardware any time a valid clock change for BEEP is required.
//It is reset when the BEEP clock change procedure is complete
  uint8_t  CLOCK_BEEPSWBSY:1;
//These bits are set by software to select the clock source to be used by the BEEP.
//00: No clock selected
//01: LSI clock used as BEEP clock source
//10: LSE clock used as BEEP clock source
//Note: Any write with a non valid target code will be skipped.
//The content of these bits is frozen and write protected when BEEPSWBSY is set.
  uint8_t  CLOCK_CLKBEEPSEL0:1;
  uint8_t  CLOCK_CLKBEEPSEL1:1;
  
  uint8_t  CLOCK_Reserved:5;
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
  uint8_t  CLOCK_REGREADY:1;
//  This bit enables the direct switch-off of the main regulator regardless of the REGREADY flag status
//0: The main regulator follows the standard functionality
//1: The main regulator is switched off and all clocks are provided without taking into account the
//REGREADY flag status
  uint8_t  CLOCK_REGOFF:1;
//  This bit indicates the status of the oscillator
//0: HSI oscillator ON
//1: HSI oscillator OFF
  uint8_t  CLOCK_HSIPD:1;
//  This bit indicates the status of the LSI oscillator
//0: LSI oscillator ON
//1: LSI oscillator OFF
  uint8_t  CLOCK_LSIPD:1;
//  This bit indicates the status of the HSE oscillator
//0: HSE oscillator ON
//1: HSE oscillator OFF
  uint8_t  CLOCK_HSEPD:1;
//  This bit indicates the status of the LSE oscillator
//0: LSE oscillator ON
//1: LSE oscillator OFF
  uint8_t  CLOCK_LSEPD:1;
//  This bit indicates if the Flash program memory and Data EEPROM ready are busy
//0: Flash program memory and Data EEPROM not busy
//1: Flash program memory and Data EEPROM busy
  uint8_t  CLOCK_EEBUSY:1;
//  This bit indicated if the Flash program memory and Data EEPROM are ready
//0: Flash program memory and Data EEPROM not ready
//1: Flash program memory and Data EEPROM ready
  uint8_t  CLOCK_EEREADY:1;
  
  

}CLK_REGCSR_TYPE;

typedef struct{
  CLK_DIVR_TYPE DIVR;
  CLK_CRTCR_TYPE CRTCR;
  CLK_ICKCR_TYPE ICKR;
  CLK_PCKENR1_TYPE PCKENR1;
  CLK_PCKENR2_TYPE PCKENR2;
  CLK_CCOR_TYPE CCOR;
  CLK_ECKCR_TYPE ECKR;
  uint8_t  CLOCK_SCSR;
  uint8_t  CLOCK_SWR;
  CLK_SWCR_TYPE SWCR;
  CLK_CSSR_TYPE CSSR;
  CLK_CBEEPR_TYPE CBEEPR;
  uint8_t  CLOCK_HSICALR;
  uint8_t  CLOCK_HSITRIMR;
  uint8_t  CLOCK_HSIUNLCKR;
  CLK_REGCSR_TYPE REGCSR;
} CLK_TYPE;

#define CLK ((volatile CLK_TYPE *)0x50C0)

#endif