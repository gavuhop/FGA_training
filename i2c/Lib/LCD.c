#include "lcd.h"

LCD_R* LCD_R = (LCD_R*)0x5400;
LCD_RAMs* ram_group = (LCD_RAMs*)0x540c;

LCD_R* get_LCD_R() 
{
	return LCD_R;
}
void reset_LCD_R()
{
	LCD_R->CR1 = 0x00;
	LCD_R->CR2 = 0x00;
	LCD_R->CR3 = 0x00;
	LCD_R->FRQ = 0x00;
	LCD_R->PM0 = 0x00;
	LCD_R->PM1 = 0x00;
	LCD_R->PM2 = 0x00;
	LCD_R->PM3 = 0x00;
}

void reset_LCD_RAMs()
{
	ram_group->RAM0 = 0x00;
	ram_group->RAM1 = 0x00;
	ram_group->RAM2 = 0x00;
	ram_group->RAM3 = 0x00;
	ram_group->RAM4 = 0x00;
	ram_group->RAM5 = 0x00;
	ram_group->RAM6 = 0x00;
	ram_group->RAM7 = 0x00;
	ram_group->RAM8 = 0x00;
	ram_group->RAM9 = 0x00;
	ram_group->RAM10 = 0x00;
	ram_group->RAM11 = 0x00;
	ram_group->RAM12 = 0x00;
	ram_group->RAM13 = 0x00;
}

/* Enable clock LCD*/
void enable_clock_for_LCD()
{
	SET_BIT(CLK_PCKENR2,3); 
}

/*Configre RTC clock 32.767Khz using LSE clock*/
void configure_RTC_clock()
{
	SET_BIT(CLK_CRTCR,4); // LSE clock used as RTC clock source
}

/* Calculate frame rate for input frequency of 16.384KHz and duty of 1/4*/
void configure_LCD_frequencies()
{
	LCD_R->FRQ = 0x30; //Set f_LCD = 256Hz and f_frame = 64Hz 
}

/*Configure port pins to be used as segment driver*/
void configure_port_pins_for_LCD()
{
	LCD_R->PM0 = 0xff; 
	LCD_R->PM1 = 0xff;
	LCD_R->PM2 = 0xff;
	LCD_R->PM3 = 0x00;
}
void configure_LCD_interrupt()
{
	ITC_SPR5 |= 0x03; //Set software prior of LCD interrupt to level 3
	CLR_B(LCD_R->CR3,5); //Interrupt disable

}

static void activate_segment_of_digit(ut8 digit, unsigned char segment)
{
	switch (digit) {
	    case 1:
		switch (segment) {
		    case 'A':
			ram_group->RAM6 |= 0x04; break;
		    case 'B':
			ram_group->RAM2 |= 0x40; break;
		    case 'C':
			ram_group->RAM3 |= 0x20; break;
		    case 'D':
			ram_group->RAM3 |= 0x10; break;
		    case 'E':
			ram_group->RAM0 |= 0x01; break;
		    case 'F':
			ram_group->RAM6 |= 0x08; break;
		    case 'G':
			ram_group->RAM2 |= 0x80; break;
		    case 'H':
			ram_group->RAM13 |= 0x08; break;
		    case 'J':
			ram_group->RAM13 |= 0x04; break;
		    case 'K':
			ram_group->RAM9 |= 0x40; break;
		    case 'M':
			ram_group->RAM0 |= 0x02; break;
		    case 'N':
			ram_group->RAM10 |= 0x10; break;
		    case 'P':
			ram_group->RAM7 |= 0x01; break;
		    case 'Q':
			ram_group->RAM9 |= 0x80; break;
		    default: break;
		}
		break;
	    case 2:
		switch (segment) {
		    case 'A':
			ram_group->RAM6 |= 0x01; break;
		    case 'B':
			ram_group->RAM2 |= 0x10; break;
		    case 'C':
			ram_group->RAM3 |= 0x80; break;
		    case 'D':
			ram_group->RAM3 |= 0x40; break;
		    case 'E':
			ram_group->RAM0 |= 0x04; break;
		    case 'F':
			ram_group->RAM6 |= 0x02; break;
		    case 'G':
			ram_group->RAM2 |= 0x20; break;
		    case 'H':
			ram_group->RAM13 |= 0x02; break;
		    case 'J':
			ram_group->RAM13 |= 0x01; break;
		    case 'K':
			ram_group->RAM9 |= 0x10; break;
		    case 'M':
			ram_group->RAM0 |= 0x08; break;
		    case 'N':
			ram_group->RAM10 |= 0x40; break;
		    case 'P':
			ram_group->RAM7 |= 0x04; break;
		    case 'Q':
			ram_group->RAM9 |= 0x20; break;
		    default: break;
		}
		break;
	    case 3:
		switch (segment) {
		    case 'A':
			ram_group->RAM5 |= 0x40; break;
		    case 'B':
			ram_group->RAM2 |= 0x04; break;
		    case 'C':
			ram_group->RAM4 |= 0x02; break;
		    case 'D':
			ram_group->RAM4 |= 0x01; break;
		    case 'E':
			ram_group->RAM0 |= 0x10; break;
		    case 'F':
			ram_group->RAM5 |= 0x80; break;
		    case 'G':
			ram_group->RAM2 |= 0x08; break;
		    case 'H':
			ram_group->RAM12 |= 0x80; break;
		    case 'J':
			ram_group->RAM12 |= 0x40; break;
		    case 'K':
			ram_group->RAM9 |= 0x04; break;
		    case 'M':
			ram_group->RAM0 |= 0x20; break;
		    case 'N':
			ram_group->RAM11 |= 0x01; break;
		    case 'P':
			ram_group->RAM7 |= 0x10; break;
		    case 'Q':
			ram_group->RAM9 |= 0x08; break;
		    default: break;
		}
		break;
	    case 4:
		switch (segment) {
		    case 'A':
			ram_group->RAM5 |= 0x10; break;
		    case 'B':
			ram_group->RAM2 |= 0x01; break;
		    case 'C':
			ram_group->RAM4 |= 0x08; break;
		    case 'D':
			ram_group->RAM4 |= 0x04; break;
		    case 'E':
			ram_group->RAM0 |= 0x40; break;
		    case 'F':
			ram_group->RAM5 |= 0x20; break;
		    case 'G':
			ram_group->RAM2 |= 0x02; break;
		    case 'H':
			ram_group->RAM12 |= 0x20; break;
		    case 'J':
			ram_group->RAM12 |= 0x10; break;
		    case 'K':
			ram_group->RAM9 |= 0x01; break;
		    case 'M':
			ram_group->RAM0 |= 0x80; break;
		    case 'N':
			ram_group->RAM11 |= 0x04; break;
		    case 'P':
			ram_group->RAM7 |= 0x40; break;
		    case 'Q':
			ram_group->RAM9 |= 0x02; break;
		    default: break;
		}
		break;
	    case 5:
		switch (segment) {
		    case 'A':
			ram_group->RAM5 |= 0x04; break;
		    case 'B':
			ram_group->RAM1 |= 0x40; break;
		    case 'C':
			ram_group->RAM4 |= 0x20; break;
		    case 'D':
			ram_group->RAM4 |= 0x10; break;
		    case 'E':
			ram_group->RAM1 |= 0x01; break;
		    case 'F':
			ram_group->RAM5 |= 0x08; break;
		    case 'G':
			ram_group->RAM1 |= 0x80; break;
		    case 'H':
			ram_group->RAM12 |= 0x08; break;
		    case 'J':
			ram_group->RAM12 |= 0x04; break;
		    case 'K':
			ram_group->RAM8 |= 0x40; break;
		    case 'M':
			ram_group->RAM1 |= 0x02; break;
		    case 'N':
			ram_group->RAM11 |= 0x10; break;
		    case 'P':
			ram_group->RAM8 |= 0x01; break;
		    case 'Q':
			ram_group->RAM8 |= 0x80; break;
		    default: break;
		}
		break;
	    case 6:
		switch (segment) {
		    case 'A':
			ram_group->RAM5 |= 0x01; break;
		    case 'B':
			ram_group->RAM1 |= 0x10; break;
		    case 'C':
			ram_group->RAM4 |= 0x80; break;
		    case 'D':
			ram_group->RAM4 |= 0x40; break;
		    case 'E':
			ram_group->RAM1 |= 0x04; break;
		    case 'F':
			ram_group->RAM5 |= 0x02; break;
		    case 'G':
			ram_group->RAM1 |= 0x20; break;
		    case 'H':
			ram_group->RAM12 |= 0x02; break;
		    case 'J':
			ram_group->RAM12 |= 0x01; break;
		    case 'K':
			ram_group->RAM8 |= 0x10; break;
		    case 'M':
			ram_group->RAM1 |= 0x08; break;
		    case 'N':
			ram_group->RAM11 |= 0x40; break;
		    case 'P':
			ram_group->RAM8 |= 0x04; break;
		    case 'Q':
			ram_group->RAM8 |= 0x20; break;
		    default: break;
		}
		break;
	    default: break;
	}
}

static void activate_colon(ut8 colon)
{
	switch (colon) {
	    case 1:
		ram_group->RAM7 |= 0x02; break;
	    case 2:
		ram_group->RAM7 |= 0x08; break;
	    case 3:
		ram_group->RAM7 |= 0x20; break;
	    case 4:
		ram_group->RAM7 |= 0x80; break;
	    default: break;
	}
}

static void activate_dp(ut8 dp)
{
	switch (dp) {
	    case 1:
		ram_group->RAM10 |= 0x20; break;
	    case 2:
		ram_group->RAM10 |= 0x80; break;
	    case 3:
		ram_group->RAM11 |= 0x02; break;
	    case 4:
		ram_group->RAM11 |= 0x08; break;
	    default: break;
	}
}

static void activate_bar(ut8 bar)
{
	switch (bar) {
	    case 0:
		ram_group->RAM11 |= 0x80; break;
	    case 1:
		ram_group->RAM8 |= 0x08; break;
	    case 2:
		ram_group->RAM11 |= 0x20; break;
	    case 3:
		ram_group->RAM8 |= 0x02; break;
	    default: break;
	}
}

void display_letter(ut8 digit, ut8 character)
{
	switch ((char)character) {
	    case 'A':
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'G');
		activate_segment_of_digit(digit, 'M');
		break;
	    case 'B':
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'D');
		activate_segment_of_digit(digit, 'M');
		activate_segment_of_digit(digit, 'J');
		activate_segment_of_digit(digit, 'P');
		break;
	    case 'C':
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'D');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		break;
	    case 'D':
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'D');
		activate_segment_of_digit(digit, 'J');
		activate_segment_of_digit(digit, 'P');
		break;
	    case 'E':
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'D');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'G');
		break;
	    case 'F':
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'G');
		break;
	    case 'G':
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'D');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'M');
		break;
	    case 'H':
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'G');
		activate_segment_of_digit(digit, 'M');
		break;
	    case 'I':
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'D');
		activate_segment_of_digit(digit, 'J');
		activate_segment_of_digit(digit, 'P');
		break;
	    case 'J':
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'D');
		activate_segment_of_digit(digit, 'E');
		break;
	    case 'K':
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'G');
		activate_segment_of_digit(digit, 'K');
		activate_segment_of_digit(digit, 'N');
		break;
	    case 'L':
		activate_segment_of_digit(digit, 'D');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		break;
	    case 'M':
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'H');
		activate_segment_of_digit(digit, 'K');
		break;
	    case 'N':
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'H');
		activate_segment_of_digit(digit, 'N');
		break;
	    case 'O':
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'D');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		break;
	    case 'P':
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'G');
		activate_segment_of_digit(digit, 'M');
		break;
	    case 'Q':
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'D');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'N');
		break;
	    case 'R':
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'N');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'G');
		activate_segment_of_digit(digit, 'M');
		break;
	    case 'S':
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'D');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'G');
		activate_segment_of_digit(digit, 'M');
		break;
	    case 'T':
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'J');
		activate_segment_of_digit(digit, 'P');
		break;
	    case 'U':
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'D');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		break;
	    case 'V':
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'Q');
		activate_segment_of_digit(digit, 'K');
		break;
	    case 'W':
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'Q');
		activate_segment_of_digit(digit, 'N');
		break;
	    case 'X':
		activate_segment_of_digit(digit, 'H');
		activate_segment_of_digit(digit, 'K');
		activate_segment_of_digit(digit, 'Q');
		activate_segment_of_digit(digit, 'N');
		break;
	    case 'Y':
		activate_segment_of_digit(digit, 'H');
		activate_segment_of_digit(digit, 'K');
		activate_segment_of_digit(digit, 'Q');
		break;
	    case 'Z':
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'K');
		activate_segment_of_digit(digit, 'Q');
		activate_segment_of_digit(digit, 'D');
		break;
	    default:
		break;
	}		
}

void display_number(ut8 digit, ut8 number)
{
	switch (number) {
	    case 0:
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'D');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'K');
		activate_segment_of_digit(digit, 'Q');
		break;
	    case 1:
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'K');
		break;
	    case 2:
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'G');
		activate_segment_of_digit(digit, 'M');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'D');
		break;
	    case 3:
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'G');
		activate_segment_of_digit(digit, 'M');
		activate_segment_of_digit(digit, 'D');
		break;
	    case 4:
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'G');
		activate_segment_of_digit(digit, 'M');
		break;
	    case 5:
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'G');
		activate_segment_of_digit(digit, 'M');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'D');
		break;
	    case 6:
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'D');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'G');
		activate_segment_of_digit(digit, 'M');
		break;
	    case 7:
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		break;
	    case 8:
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'E');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'G');
		activate_segment_of_digit(digit, 'M');
		activate_segment_of_digit(digit, 'D');
		break;
	    case 9:
		activate_segment_of_digit(digit, 'A');
		activate_segment_of_digit(digit, 'B');
		activate_segment_of_digit(digit, 'C');
		activate_segment_of_digit(digit, 'F');
		activate_segment_of_digit(digit, 'G');
		activate_segment_of_digit(digit, 'M');
		activate_segment_of_digit(digit, 'D');
		break;
	    default: break;
	}
}

void display_win(bool c)
{
		activate_segment_of_digit(2, 'B');
		activate_segment_of_digit(2, 'C');
		activate_segment_of_digit(2, 'E');
		activate_segment_of_digit(2, 'F');
		activate_segment_of_digit(2, 'Q');
		activate_segment_of_digit(2, 'N');
		activate_segment_of_digit(3, 'A');
		activate_segment_of_digit(3, 'D');
		activate_segment_of_digit(3, 'J');
		activate_segment_of_digit(3, 'P');
		activate_segment_of_digit(4, 'B');
		activate_segment_of_digit(4, 'C');
		activate_segment_of_digit(4, 'E');
		activate_segment_of_digit(4, 'F');
		activate_segment_of_digit(4, 'H');
		activate_segment_of_digit(4, 'N');
}
void display_a(bool a, ut8 number1, ut8 number2)
{
	display_letter(1, 'A');
	activate_colon(1);
	display_number(2, ut8 number1);
	display_number(2, ut8 number2);		
}
void display_b(bool b, ut8 number1, ut8 number2)
{
	display_letter(1, 'B');
	activate_colon(1);
	display_number(2, ut8 number1);
	display_number(2, ut8 number2);		
}
void init_LCD()
{
	enable_clock_for_LCD();
	configure_RTC_clock();
	
	reset_LCD_R();
	reset_LCD_RAMs();
	
	CLR_B(LCD_R->CR1,0);
	
	/* Select 1/4 duty ratio */
	SET_BIT(LCD_R->CR1,1);
	SET_BIT(LCD_R->CR1,2);
	
	configure_LCD_frequencies();
	configure_port_pins_for_LCD();
	
	SET_BIT(LCD_R->CR2,3); // Set contrast level
	SET_BIT(LCD_R->CR2,4); // High drive permanent enable
	configure_LCD_interrupt();
	/* Enable LCD controler */
	SET_BIT(LCD_R->CR3,6);
}
