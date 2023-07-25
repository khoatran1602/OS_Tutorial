#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    //Given a variable X as unsigned int (32 bits). Write expression(s) in C to swap its bits 7-4 with bits 13-10.
    unsigned int X, temp1, temp2;
    //input X
    scanf("%u", &X);
    printf("X = %u\n", X);
    //declare r to X
    unsigned int r = X;
    //read the bits 7-4
    temp1 = (r >> 4) & 0x0F;
    //read the bits 13-10
    temp2 = (r >> 10) & 0x0F;
    //clear the bits 7-4 and 13-10
    r &= ~(0x0F << 4);
    r &= ~(0x0F << 10);
    //write the bits 7-4 and 13-10
    r = r | (temp1 << 10);
    r = r | (temp2 << 4);
    X = r;
    //print the result
    printf("%u", X);

    return 0;
}