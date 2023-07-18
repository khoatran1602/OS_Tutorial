#include <stdio.h>


//print hello world in main
int main(void) {
    printf("Hello World!\n");
    return 0;
}

int X = 0b0101111001110000011101010101111;

//set bit 3 of X
int setBit3(int x) {
    return x | (1 << 3);
}

//set bit 3 & 5 of X
int setBit3and5(int x) {
    return x | (1 << 3) | (1 << 5);
}

//clear bit 6 of X
int clearBit6(int x) {
    return x & ~(1 << 6);
}

//clear bit 6 and 8 of X
int clearBit6and8(int x) {
    return x & ~(1 << 6) & ~(1 << 8);
}

//both set bits 5-3 and clear bits 6-8 of X
int setBit3to5andClear6to8(int x) {
    return x | (1 << 3) | (1 << 5) & ~(1 << 6) & ~(1 << 8);
}

//Toggle (reverse) bits 7 and 4 of X
int toggleBit7and4(int x) {
    return x ^ (1 << 7) ^ (1 << 4);
}

//Copy bits 7-4 of X to bits 11-8 of another integer Y
int copyBit7to4(int x) {
    return (x & 0b0000111100000000) << 4;
}




