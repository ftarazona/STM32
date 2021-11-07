#include <stddef.h>
#include "matrix.h"

static rgb_color buffer1[LED_MATRIX_N_LEDS];
static rgb_color buffer2[LED_MATRIX_N_LEDS];
static rgb_color * currentBuffer = buffer1;
static rgb_color * currentImage = buffer2;
static int iLED = 0;


/* matrix_init intializes every driver pin in output high speed mode
 * and put every led to 0. */
void matrix_init(void)	{
	//Enabling peripherals' clocks
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN |
					RCC_AHB2ENR_GPIOBEN |
					RCC_AHB2ENR_GPIOCEN;

	//Configuring pins in output mode
	GPIOA->MODER = (GPIOA->MODER & 0x3ffc000f) |
					GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0 |
					GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0 |
					GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0 |
					GPIO_MODER_MODE15_0;
	GPIOB->MODER = (GPIOB->MODER & 0xffffffc0) |
					GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0 |
					GPIO_MODER_MODE2_0;
	GPIOC->MODER = (GPIOC->MODER & 0xfffff03f) |
					GPIO_MODER_MODE3_0 | GPIO_MODER_MODE4_0 |
					GPIO_MODER_MODE5_0;

	//Configuring pins in high speed mode
	GPIOA->OSPEEDR |= 	(3 << GPIO_OSPEEDR_OSPEED2_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED3_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED4_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED5_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED6_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED7_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED15_Pos);
	GPIOB->OSPEEDR |= 	(3 << GPIO_OSPEEDR_OSPEED0_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED1_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED2_Pos);
	GPIOC->OSPEEDR |= 	(3 << GPIO_OSPEEDR_OSPEED3_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED4_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED5_Pos);

	//Reseting the led matrix.
	RST(0);
	LAT(1);
	SB(1);
	SCK(0);
	SDA(0);
	deactivate_rows();

	active_wait(N_TICKS_DELAY);	//Waits about 100ms
	RST(1);
	init_bank0();	//Sets every bit in bank0 to 1.
}

/* deactivate_rows clears every row. Instead of using 8 instructions,
 * we directly write in BSRRegister */
void deactivate_rows(void)	{
	GPIOA->BSRR |= 0x80ec << 16;
	GPIOB->BSRR |= 0x0005 << 16;
}

/* activate_row activates a given row. It does not affect any other
 * row. */
void activate_row(int row)	{
	switch(row)	{
		case 0: ROW0(1); break;
		case 1: ROW1(1); break;
		case 2: ROW2(1); break;
		case 3: ROW3(1); break;
		case 4: ROW4(1); break;
		case 5: ROW5(1); break;
		case 6: ROW6(1); break;
		case 7: ROW7(1); break;
		default: break;
	}
}

/* send_byte send 8 bit to the DM163 microcontroller, following the
 * protocol. */
void send_byte(uint8_t val, int bank)	{
	SB(bank);	//Select the bank
	for(int i = 0; i < 8; ++i)	{
		SDA(val & (1 << (7 - i)));
		pulse_SCK();
	}
}

/* mat_set_row transmits the information for the DM163 to set a given
 * row to the good values given. */
void mat_set_row(int row, const rgb_color * val)	{
	for(int i = 0; i < 8; ++i)	{
		send_byte(val[i].b, 1);
		send_byte(val[i].g, 1);
		send_byte(val[i].r, 1);
		if(i == 6)
			deactivate_rows();
	}
	pulse_LAT();
	activate_row(row);
}

/* init_bank0 sets every bit in BANK0 to 1. */
void init_bank0(void)	{
	for(int i = 0; i < 24; ++i)	{
		send_byte(0xff, 0);
	}
	pulse_LAT();
}

/* display_image displays the image described by global object
 * led_values. */
void display_image(void)	{
	for(int i = 0; i < LED_MATRIX_N_ROWS; ++i)	{
		mat_set_row(i, currentImage + (LED_MATRIX_N_COLS * i));
	}
}

/* load_image loads the next image from buffer and sets iLED to 0.
 * It switches the pointer to the array not currently pointed.
 * The previous buffer is not automatically cleared, it has to be
 * erased by calling set_image */
void load_image(void)	{
	set_image();
	if(currentBuffer == buffer1)	{
		currentImage = buffer1;
		currentBuffer = buffer2;
	} else	{
		currentImage = buffer2;
		currentBuffer = buffer1;
	}
	iLED = 0;
}

/* update_image writes the value given in the buffer.
 * Returns 1 if the buffer is full. 
 * Returns -1 if attempt to write in a full buffer. */
void update_image(int x, int y, int color, uint8_t val)	{
	switch(color % 3)	{
		case RED	: currentBuffer[x][y].r = val; break;
		case GREEN	: currentBuffer[x][y].g = val; break;
		case BLUE	: currentBuffer[x][y].b = val; break;
		default		: break;
	}
}

/* void_image sets every remaining bit of the buffer to 0 */
void set_image(void)	{
	for(int x = 0; x < LED_MATRIX_N_ROWS; ++x)	{
		for(int y = 0; y < LED_MATRIX_N_COLS; ++y)	{
			update_image(x, y, RED, 0);
			update_image(x, y, GREEN, 0);
			update_image(x, y, BLUE, 0);
		}
	}
}
