// -----------------------------------main.c-------------------------------------
#include "mbox.h"
#include "uart.h"

void main() {
    /*
    Decimals: 1997
    Characters: b B 
    String: Thien 
    Float: 2.314560
    Hex: 55
    Octal: 74
    Percent: %
    Width:       500
    Check precious: 1.26 
    */
    printf("Decimals: %d\n", 1997);
    printf("Characters: %c %c \n", 'b', 66);
    printf("String: %s \n", "Thien");
    printf("Float: %f \n", 2.31456);
    printf("Hex: %x\n", 85);
    printf("Octal: %o\n", 60);
    printf("Percent: %%\n");
    printf("Width: %10d ", 500);
    printf("\nCheck precious: %.2f \n", 1.2565);
}