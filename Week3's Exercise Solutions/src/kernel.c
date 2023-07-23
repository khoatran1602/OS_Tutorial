// -----------------------------------main.c -------------------------------------

#ifdef UART0
#include "./uart/uart0.h"
#define MSG "Hello World! This is UART0 !!!\n"

#else //UART1
#include "./uart/uart1.h"
#define MSG "Hello World! This is UART1 !!!\n"
#endif

void main(){
    // intitialize UART
    uart_init();
    
    // say hello
    uart_puts(MSG);

    // echo everything back 
    while(1) {
    	//read each char
    	char c = uart_getc();

    	/* Convert received characters from UPPERCASE 
        to lowercase and vice versa */
    	if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        } else if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';
        }
    }
}
