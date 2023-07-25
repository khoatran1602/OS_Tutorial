#include "../gpio.h"

#define UART5_BASE (MMIO_BASE + 0x201a00)

#define UART5_DR (* (volatile unsigned int*)(UART5_BASE + 0x00))
#define UART5_RSRECR (* (volatile unsigned int*)(UART5_BASE + 0x04))

#define UART5_FR (* (volatile unsigned int*)(UART5_BASE + 0x18))
#define UART5_FR_TXFE (1<<7)
#define UART5_FR_RXFF (1<<6)
#define UART5_FR_TXFF (1<<5)
#define UART5_FR_RXFE (1<<4)
#define UART5_FR_BUSY (1<<3)
#define UART5_FR_CTS (1<<0)

#define UART5_ILPR (* (volatile unsigned int*)(UART5_BASE + 0x20))

#define UART5_IBRD (* (volatile unsigned int*)(UART5_BASE + 0x24))

#define UART5_FBRD (* (volatile unsigned int*)(UART5_BASE + 0x28))

#define UART5_LCRH (* (volatile unsigned int*)(UART5_BASE + 0x2C))
#define UART5_LCRH_SPS (1<<7)
#define UART5_LCRH_WLEN_5BIT (0<<5)
#define UART5_LCRH_WLEN_6BIT (1<<5)
#define UART5_LCRH_WLEN_7BIT (2<<5)
#define UART5_LCRH_WLEN_8BIT (3<<5)
#define UART5_LCRH_FEN (1<<4)
#define UART5_LCRH_STP2 (1<<3)
#define UART5_LCRH_EPS (1<<2)
#define UART5_LCRH_PEN (1<<1)
#define UART5_LCRH_BRK (1<<0)

#define UART5_CR (* (volatile unsigned int*)(UART5_BASE + 0x30))
#define UART5_CR_CTSEN (1<<15)
#define UART5_CR_RTSEN (1<<14)
#define UART5_CR_RTS (1<<11)
#define UART5_CR_RXE (1<<9)
#define UART5_CR_TXE (1<<8)
#define UART5_CR_LBE (1<<7)
#define UART5_CR_UARTEN (1<<0)

#define UART5_IFLS (* (volatile unsigned int*)(UART5_BASE + 0x34))

#define UART5_IMSC (* (volatile unsigned int*)(UART5_BASE + 0x38))
#define UART5_IMSC_OE	(1<<10)
#define UART5_IMSC_BE	(1<<9)  
#define UART5_IMSC_PE	(1<<8)  
#define UART5_IMSC_FE	(1<<7)	
#define UART5_IMSC_RT	(1<<6)	
#define UART5_IMSC_TX	(1<<5)  
#define UART5_IMSC_CTS	(1<<1)

#define UART5_RIS (* (volatile unsigned int*)(UART5_BASE + 0x3C))
#define UART5_MIS (* (volatile unsigned int*)(UART5_BASE + 0x40))
#define UART5_ICR (* (volatile unsigned int*)(UART5_BASE + 0x44))
#define UART5_DMACR (* (volatile unsigned int*)(UART5_BASE + 0x48))
#define UART5_ITCR (* (volatile unsigned int*)(UART5_BASE + 0x80))
#define UART5_ITIP (* (volatile unsigned int*)(UART5_BASE + 0x84))
#define UART5_ITOP (* (volatile unsigned int*)(UART5_BASE + 0x88))
#define UART5_TDR (* (volatile unsigned int*)(UART5_BASE + 0x8C))



/* Function prototypes */
void uart_init();
void uart_sendc(char c);
char uart_getc();
void uart_puts(char *s);
