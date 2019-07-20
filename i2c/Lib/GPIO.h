#ifndef GPIO   // if not define
#pragma once

#include <stdint.h>

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