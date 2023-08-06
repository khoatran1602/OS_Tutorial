#include "../gpio.h"

#define UART2_BASE (MMIO_BASE + 0x201400)

#define UART2_DR (* (volatile unsigned int*)(UART2_BASE + 0x00))
#define UART2_RSRECR (* (volatile unsigned int*)(UART2_BASE + 0x04))

#define UART2_FR (* (volatile unsigned int*)(UART2_BASE + 0x18))
#define UART2_FR_TXFE (1<<7)
#define UART2_FR_RXFF (1<<6)
#define UART2_FR_TXFF (1<<5)
#define UART2_FR_RXFE (1<<4)
#define UART2_FR_BUSY (1<<3)
#define UART2_FR_CTS (1<<0)

#define UART2_ILPR (* (volatile unsigned int*)(UART2_BASE + 0x20))

#define UART2_IBRD (* (volatile unsigned int*)(UART2_BASE + 0x24))

#define UART2_FBRD (* (volatile unsigned int*)(UART2_BASE + 0x28))

#define UART2_LCRH (* (volatile unsigned int*)(UART2_BASE + 0x2C))
#define UART2_LCRH_SPS (1<<7)
#define UART2_LCRH_WLEN_5BIT (0<<5)
#define UART2_LCRH_WLEN_6BIT (1<<5)
#define UART2_LCRH_WLEN_7BIT (2<<5)
#define UART2_LCRH_WLEN_8BIT (3<<5)
#define UART2_LCRH_FEN (1<<4)
#define UART2_LCRH_STP2 (1<<3)
#define UART2_LCRH_EPS (1<<2)
#define UART2_LCRH_PEN (1<<1)
#define UART2_LCRH_BRK (1<<0)

#define UART2_CR (* (volatile unsigned int*)(UART2_BASE + 0x30))
#define UART2_CR_CTSEN (1<<15)
#define UART2_CR_RTSEN (1<<14)
#define UART2_CR_RTS (1<<11)
#define UART2_CR_RXE (1<<9)
#define UART2_CR_TXE (1<<8)
#define UART2_CR_LBE (1<<7)
#define UART2_CR_UARTEN (1<<0)

#define UART2_IFLS (* (volatile unsigned int*)(UART2_BASE + 0x34))

#define UART2_IMSC (* (volatile unsigned int*)(UART2_BASE + 0x38))
#define UART2_IMSC_OE	(1<<10)
#define UART2_IMSC_BE	(1<<9)  
#define UART2_IMSC_PE	(1<<8)  
#define UART2_IMSC_FE	(1<<7)	
#define UART2_IMSC_RT	(1<<6)	
#define UART2_IMSC_TX	(1<<5)
#define UART2_IMSC_RX	(1<<4)  
#define UART2_IMSC_CTS	(1<<1)

#define UART2_RIS (* (volatile unsigned int*)(UART2_BASE + 0x3C))
#define UART2_MIS (* (volatile unsigned int*)(UART2_BASE + 0x40))
#define UART2_ICR (* (volatile unsigned int*)(UART2_BASE + 0x44))
#define UART2_DMACR (* (volatile unsigned int*)(UART2_BASE + 0x48))
#define UART2_ITCR (* (volatile unsigned int*)(UART2_BASE + 0x80))
#define UART2_ITIP (* (volatile unsigned int*)(UART2_BASE + 0x84))
#define UART2_ITOP (* (volatile unsigned int*)(UART2_BASE + 0x88))
#define UART2_TDR (* (volatile unsigned int*)(UART2_BASE + 0x8C))



/* Function prototypes */
void uart_init();
void uart_sendc(char c);
char uart_getc();
void uart_puts(char *s);
