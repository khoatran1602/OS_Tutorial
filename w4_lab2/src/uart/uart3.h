#include "../gpio.h"

#define UART3_BASE (MMIO_BASE + 0x201600)

#define UART3_DR (* (volatile unsigned int*)(UART3_BASE + 0x00))
#define UART3_RSRECR (* (volatile unsigned int*)(UART3_BASE + 0x04))

#define UART3_FR (* (volatile unsigned int*)(UART3_BASE + 0x18))
#define UART3_FR_TXFE (1<<7)
#define UART3_FR_RXFF (1<<6)
#define UART3_FR_TXFF (1<<5)
#define UART3_FR_RXFE (1<<4)
#define UART3_FR_BUSY (1<<3)
#define UART3_FR_CTS (1<<0)

#define UART3_ILPR (* (volatile unsigned int*)(UART3_BASE + 0x20))

#define UART3_IBRD (* (volatile unsigned int*)(UART3_BASE + 0x24))

#define UART3_FBRD (* (volatile unsigned int*)(UART3_BASE + 0x28))

#define UART3_LCRH (* (volatile unsigned int*)(UART3_BASE + 0x2C))
#define UART3_LCRH_SPS (1<<7)
#define UART3_LCRH_WLEN_5BIT (0<<5)
#define UART3_LCRH_WLEN_6BIT (1<<5)
#define UART3_LCRH_WLEN_7BIT (2<<5)
#define UART3_LCRH_WLEN_8BIT (3<<5)
#define UART3_LCRH_FEN (1<<4)
#define UART3_LCRH_STP2 (1<<3)
#define UART3_LCRH_EPS (1<<2)
#define UART3_LCRH_PEN (1<<1)
#define UART3_LCRH_BRK (1<<0)

#define UART3_CR (* (volatile unsigned int*)(UART3_BASE + 0x30))
#define UART3_CR_CTSEN (1<<15)
#define UART3_CR_RTSEN (1<<14)
#define UART3_CR_RTS (1<<11)
#define UART3_CR_RXE (1<<9)
#define UART3_CR_TXE (1<<8)
#define UART3_CR_LBE (1<<7)
#define UART3_CR_UARTEN (1<<0)

#define UART3_IFLS (* (volatile unsigned int*)(UART3_BASE + 0x34))

#define UART3_IMSC (* (volatile unsigned int*)(UART3_BASE + 0x38))
#define UART3_IMSC_OE	(1<<10)
#define UART3_IMSC_BE	(1<<9)  
#define UART3_IMSC_PE	(1<<8)  
#define UART3_IMSC_FE	(1<<7)	
#define UART3_IMSC_RT	(1<<6)	
#define UART3_IMSC_TX	(1<<5)  
#define UART3_IMSC_CTS	(1<<1)

#define UART3_RIS (* (volatile unsigned int*)(UART3_BASE + 0x3C))
#define UART3_MIS (* (volatile unsigned int*)(UART3_BASE + 0x40))
#define UART3_ICR (* (volatile unsigned int*)(UART3_BASE + 0x44))
#define UART3_DMACR (* (volatile unsigned int*)(UART3_BASE + 0x48))
#define UART3_ITCR (* (volatile unsigned int*)(UART3_BASE + 0x80))
#define UART3_ITIP (* (volatile unsigned int*)(UART3_BASE + 0x84))
#define UART3_ITOP (* (volatile unsigned int*)(UART3_BASE + 0x88))
#define UART3_TDR (* (volatile unsigned int*)(UART3_BASE + 0x8C))



/* Function prototypes */
void uart_init();
void uart_sendc(char c);
char uart_getc();
void uart_puts(char *s);
