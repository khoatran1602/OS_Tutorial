#include "uart.h"

void main() {
    // intitialize UART
    uart_init();
    // say hello
    uart_puts("Hello World!\n");
    // echo everything back
    while(1) {
        // uart_puts("Hello World!\n");
        //read each char
        char c = uart_getc();
        //send back twice
        uart_sendc(c);
        uart_sendc(c);
    }
}