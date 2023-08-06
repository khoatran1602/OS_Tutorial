#include "uart2.h"

/**
 * Set baud rate and characteristics (115200 8N1) and map to GPIO
 */
void uart_init()
{
    unsigned int r;

	/* Turn off UART2 */
	UART2_CR = 0x0;

	/* Set GPIO0 and GPIO1 to be pl011 TX/RX which is ALT4	*/
	r = GPFSEL0;
	r &=  ~((7 << 0) | (7 << 3)); //clear bits 5-0 (FSEL1, FSEL0)
	r |= (0b011 << 0)|(0b011 << 3);   //Set value 0b011 (select ALT4: TXD2/RXD2)
	GPFSEL0 = r;
	
	/* Enable GPIO 0, 1 */
#ifdef RPI3 //RBI3
//Not available on RPI3

#else //RPI4
	r = GPIO_PUP_PDN_CNTRL_REG0;
	r &= ~((3 << 0) | (3 << 2)); //No resistor is selected for GPIO 0, 1
	GPIO_PUP_PDN_CNTRL_REG0 = r;
#endif

	/* Mask all interrupts. */
	UART2_IMSC = 0;

	/* Clear pending interrupts. */
	UART2_ICR = 0x7FF;

	/* Set integer & fractional part of Baud rate
	Divider = UART_CLOCK/(16 * Baud)            
	Default UART_CLOCK = 48MHz (old firmware it was 3MHz); 
	Integer part register UART2_IBRD  = integer part of Divider 
	Fraction part register UART2_FBRD = (Fractional part * 64) + 0.5 */

	//Baud rate 57600
	//Divider = 48*10^6/(16 * 57600) = 52.08333333
	//IBRD = 52
	//FBRD = 0.08333333* 64 + 0.5 = 5.83333312

	UART2_IBRD = 52;       
	UART2_FBRD = 6;

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
