#include "uart5.h"

/**
 * Set baud rate and characteristics (1113200 8N1) and map to GPIO
 */
void uart_init()
{
    unsigned int r;

	/* Turn off UART5 */
	UART5_CR = 0x0;

	/* Setup GPIO pins 12 and 13 */

	/* Set GPIO12 and GPIO13 to be pl011 TX/RX which is ALT4	*/
	r = GPFSEL1;
	r &= ~((0b111 << 6) | (0b111 << 9)); // Clear the gpio 12 and 13
	r |=  (3 << 6)|(3 << 9);   //Set value 3 (select ALT4: UART5)
	GPFSEL1 = r;
	
	r = GPIO_PUP_PDN_CNTRL_REG0;
	r &= ~((3 << 24) | (3 << 26)); //No resistor is selected for GPIO 12, 13
	GPIO_PUP_PDN_CNTRL_REG0 = r;

	/* Mask all interrupts. */
	UART5_IMSC = 0;

	/* Clear pending interrupts. */
	UART5_ICR = 0x7FF;

	/* Set integer & fractional part of Baud rate
	Divider = UART_CLOCK/(16 * Baud)            
	Default UART_CLOCK = 48MHz (old firmware it was 3MHz); 
	Integer part register UART5_IBRD  = integer part of Divider 
	Fraction part register UART5_FBRD = (Fractional part * 64) + 0.5 */

	//!! 921600 baud
	//UART5_IBRD = 3;
	//UART5_FBRD = 17;

	//!! 460800 baud
	//UART5_IBRD = 7;
	//UART5_FBRD = 33;

	//!! 230400 baud
	//UART5_IBRD = 13;
	//UART5_FBRD = 2;

	//!! 115200 baud
	UART5_IBRD = 26;       
	UART5_FBRD = 3;

	//!! 57600 baud
	//UART5_IBRD = 52;
	//UART5_FBRD = 6;

	//!! 38400 baud
	//UART5_IBRD = 78;
	//UART5_FBRD = 9;

	//!! 19200 baud
	//UART5_IBRD = 156;
	//UART5_FBRD = 17;

	//!! 14400 baud
	//UART5_IBRD = 208;
	//UART5_FBRD = 22;

	//!! 9600 baud
	//UART5_IBRD = 312;
	//UART5_FBRD = 33;

	//!! 4800 baud
	//UART5_IBRD = 625;
	//UART5_FBRD = 0;

	//!! 2400 baud
	//UART5_IBRD = 1250;
	//UART5_FBRD = 0;

	/* Set up the Line Control Register */
	/* Enable FIFO */
	/* Set length to 8 bit */
	/* Defaults for other bit are No parity, 1 stop bit */
	UART5_LCRH = UART5_LCRH_FEN | UART5_LCRH_WLEN_8BIT;

	/* Enable UART5, receive, and transmit */
	UART5_CR = 0x301;     // enable Tx, Rx, FIFO
}



/**
 * Send a character
 */
void uart_sendc(char c) {

    /* Check Flags Register */
	/* And wait until transmitter is not full */
	do {
		asm volatile("nop");
	} while (UART5_FR & UART5_FR_TXFF);

	/* Write our data byte out to the data register */
	UART5_DR = c ;
}

/**
 * Receive a character
 */
char uart_getc() {
    char c = 0;

    /* Check Flags Register */
    /* Wait until Receiver is not empty
     * (at least one byte data in receive fifo)*/
	do {
		asm volatile("nop");
    } while ( UART5_FR & UART5_FR_RXFE );

    /* read it and return */
    c = (unsigned char) (UART5_DR);

    /* convert carriage return to newline */
    return (c == '\r' ? '\n' : c);
}


/**
 * Display a string
 */
void uart_puts(char *s) {
    while (*s) {
        /* convert newline to carriage return + newline */
        if (*s == '\n')
            uart_sendc('\r');
        uart_sendc(*s++);
    }
}
