#include "mbox.h"
#include "uart.h"

void print_welcome() {
    uart_puts("####    \033[0m    ######## ######## ######## ########  #######  ##         #######    #####");
    uart_puts("\n");
    uart_puts(" ##     \033[0m    ##       ##       ##          ##    ##     ## ##    ##  ##     ##  ##   ##");
    uart_puts("\n");
    uart_puts(" ##     \033[0m    ##       ##       ##          ##           ## ##    ##  ##     ## ##     ##");
    uart_puts("\n");
    uart_puts(" ##     \033[0m    ######   ######   ######      ##     #######  ##    ##   ######## ##     ##    #####");
    uart_puts("\n");
    uart_puts(" ##     \033[0m     ##       ##       ##          ##    ##        #########        ## ##     ##");
    uart_puts("\n");
    uart_puts(" ##     \033[0m      ##       ##       ##          ##    ##              ##  ##     ##  ##   ##");
    uart_puts("\n");
    uart_puts("####    \033[0m       ######## ######## ########    ##    #########       ##   #######    #####");
    uart_puts("\n");
    uart_puts("\n");

    uart_puts("\n");
    uart_puts("##      #     #                                              #######           #######                  #######  #####      #####                                     ");
    uart_puts("\n");
    uart_puts("##  ##  #  #  # ###### #       ####   ####  #    # ######       #     ####        #    #    # ######    #     # #     #    #     #  ####  #    # #####   ####  ###### ");
    uart_puts("\n");
    uart_puts("##  ##  #  #  # #      #      #    # #    # ##  ## #            #    #    #       #    #    # #         #     # #          #       #    # #    # #    # #      #      ");
    uart_puts("\n");
    uart_puts("##  ##  #  #  # #####  #      #      #    # # ## # #####        #    #    #       #    ###### #####     #     #  #####     #       #    # #    # #    #  ####  #####  ");
    uart_puts("\n");
    uart_puts("##  ##  #  #  # #      #      #      #    # #    # #            #    #    #       #    #    # #         #     #       #    #       #    # #    # #####       # #      ");
    uart_puts("\n");
    uart_puts("##  ##  #  #  # #      #      #    # #    # #    # #            #    #    #       #    #    # #         #     # #     #    #     # #    # #    # #   #  #    # #     ");
    uart_puts("\n");
    uart_puts(" ###    ## ##  ###### ######  ####   ####  #    # ######       #     ####        #    #    # ######    #######  #####      #####   ####   ####  #    #  ####  ###### ");
    uart_puts("\n");
    uart_puts("\t Developed By Tran Dang Khoa - s3847766");
    uart_puts("\n");
    uart_puts("EEET2490 - Welcome To The OS Course");
}