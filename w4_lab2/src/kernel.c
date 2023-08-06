#ifdef UART3
#include "./uart/uart3.h"
#define MSG "Hello World! This is UART3 !!!\n"

#else //UART4
#include "./uart/uart4.h"
#define MSG "Hello World! This is UART4 !!!\n"
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