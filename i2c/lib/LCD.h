#include <stdint.h>

/* Clock-related registers */
#define CLK_CKDIVR (*(uint8_t*)0x50c0) // Clock master divider register
#define CLK_CRTCR (*(uint8_t*)0x50c1) // Clock RTC Register 
#define CLK_PCKENR2 (*(uint8_t*)0x50c4) // Peripheral clock gating register 2

#define ITC_SPR5 (*(uint8_t*)0x7f74) //Software priority register 5 

#define SET_BIT(REG,N) (REG |= (1<<N)) //Set bit N of register 
#define CLR_B(REG,N) (REG &= ~(1<<N)) //Clear bit N of register
#define GET_B(REG,N) ((0u == (REG & (1<<N)))?0u:1u) // Get bit N of register

typedef uint8_t ut8;

typedef struct LCD_R
{
	ut8 CR1;
	ut8 CR2;
	ut8 CR3;
	ut8 FRQ;
	ut8 PM0;
	ut8 PM1;
	ut8 PM2;
	ut8 PM3;
} LCD_R;

typedef struct LCD_RAMs
{
	ut8 RAM0;
	ut8 RAM1;
	ut8 RAM2;
	ut8 RAM3;
	ut8 RAM4;
	ut8 RAM5;
	ut8 RAM6;
	ut8 RAM7;
	ut8 RAM8;
	ut8 RAM9;
	ut8 RAM10;
	ut8 RAM11;
	ut8 RAM12;
	ut8 RAM13;
} LCD_RAMs;

LCD_R* get_LCD_R();

void enable_clock_for_LCD();
void configure_RTC_clock();
void configure_LCD_frequencies();
void configure_port_pins_for_LCD();
void reset_LCD_R();
void reset_LCD_RAMs();
void configure_LCD_interrupt();
void init_LCD();

/*Using*/
static void activate_segment_of_digit(ut8, ut8);
static void activate_colon(ut8);
static void activate_dp(ut8);
static void activate_bar(ut8);
void display_letter(ut8 digit, ut8 character); 
void display_number(ut8 digit, ut8 number); 
void display_win();
void display_a(ut8 number1, ut8 number2);
void display_b(ut8 number1, ut8 number2);