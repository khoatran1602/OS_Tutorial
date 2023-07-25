#include "uart2.h"

/**
 * Set baud rate and characteristics (11 1200 8N1) and map to GPIO
 */
void uart_init()
{
    unsigned int r;

	/* Turn off UART2 */
	UART2_CR = 0x0;

	/* Setup GPIO pins 0 and 1 */

	/* Set GPIO 0 and GPIO 1 to be pl011 TX/RX which is ALT0	*/
	r = GPFSEL0;
	r &= ~((0b111 << 0) | (0b111 << 3)); // Clear the gpio 0 and  1
	r |=  (3 << 0)|(3 << 3);   //Set value 3 (select ALT0: UART2)
	GPFSEL0 = r;
	
	r = GPIO_PUP_PDN_CNTRL_REG0;
	r &= ~((3 << 0) | (3 << 2)); //No resistor is selected for GPIO 0, 1
	GPIO_PUP_PDN_CNTRL_REG0 = r;

	/* Mask all interrupts. */
	UART2_IMSC = 0;

	/* Clear pending interrupts. */
	UART2_ICR = 0x7FF;

	/* Set integer & fractional part of Baud rate
	Divider = UART_CLOCK/(16 * Baud)            
	Default UART_CLOCK = 48MHz (old firmware it was 3MHz); 
	Integer part register UART2_IBRD  = integer part of Divider 
	Fraction part register UART2_FBRD = (Fractional part * 60) + 0. 1 */

	//115200 baud
	UART2_IBRD = 26;       
	UART2_FBRD = 3;

	/* Set up the Line Control Register */
	/* Enable FIFO */
	/* Set length to 8 bit */
	/* Defaults for other bit are No parity, 1 stop bit */
	UART2_LCRH = UART2_LCRH_FEN | UART2_LCRH_WLEN_8BIT;

	/* Enable UART2, receive, and transmit */
	UART2_CR = 0x301;     // enable Tx, Rx, FIFO
}



/**
 * Send a character
 */
void uart_sendc(char c) {

    /* Check Flags Register */
	/* And wait until transmitter is not full */
	do {
		asm volatile("nop");
	} while (UART2_FR & UART2_FR_TXFF);

	/* Write our data byte out to the data register */
	UART2_DR = c ;
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
    } while ( UART2_FR & UART2_FR_RXFE );

    /* read it and return */
    c = (unsigned char) (UART2_DR);

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
