// -----------------------------------main.c -------------------------------------
#include "mbox.h"
#include "uart.h"

// Function to get board MAC revision
unsigned int get_board_revision() {
    // Mailbox data buffer: Read board MAC revision
    mBuf[0] = 8 * 4;               // Message Buffer Size in bytes (8 elements * 4 bytes (32 bit) each)
    mBuf[1] = MBOX_REQUEST;        // Message Request Code (this is a request message)
    mBuf[2] = 0x00010002;          // TAG Identifier: Get board MAC revision
    mBuf[3] = 4;                   // Value buffer size in bytes (max of request and response lengths)
    mBuf[4] = 0;                   // REQUEST CODE = 0
    mBuf[5] = 0;                   // clear output buffer (response data are mBuf[5] & mBuf[6])
    mBuf[6] = 0;                   // clear output buffer (response data are mBuf[5] & mBuf[6])
    mBuf[7] = MBOX_TAG_LAST;

    // Make the mailbox call
    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP)) {
        // Extract and return the board MAC revision
        return mBuf[5];
    } else {
        // Return 0 if the mailbox call failed
        return 0;
    }
}


// Function to get board MAC address
void get_board_mac_address(uint8_t mac_address[6]) {
    // Mailbox data buffer: Read board MAC address
    mBuf[0] = 8 * 4;               // Message Buffer Size in bytes (8 elements * 4 bytes (32 bit) each)
    mBuf[1] = MBOX_REQUEST;        // Message Request Code (this is a request message)
    mBuf[2] = 0x00010003;          // TAG Identifier: Get board MAC address
    mBuf[3] = 0;                   // Value buffer size in bytes (length is zero for MAC address)
    mBuf[4] = 0;                   // REQUEST CODE = 0
    mBuf[5] = 0;                   // clear output buffer (response data are mBuf[5] & mBuf[6])
    mBuf[6] = 0;                   // clear output buffer (response data are mBuf[5] & mBuf[6])
    mBuf[7] = MBOX_TAG_LAST;

    // Make the mailbox call
    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP)) {
        // Extract the MAC address (6 bytes) from the response buffer
        for (int i = 0; i < 6; i++) {
            mac_address[i] = (uint8_t)(mBuf[5] >> (8 * i));
        }
    } else {
        // If the mailbox call failed, set the MAC address to all zeros
        for (int i = 0; i < 6; i++) {
            mac_address[i] = 0;
        }
    }
}

void show_info() {
    // Call the function to get the board MAC address
    uint8_t mac_address[6];
    get_board_mac_address(mac_address);

     unsigned int board_revision = get_board_revision();

    // Print the board MAC revision
    uart_puts("Board MAC revision: ");
    uart_hex(board_revision);
    uart_puts("\n");

    // Print the board MAC address in human-readable format
    uart_puts("Board MAC address: ");
    for (int i = 0; i < 6; i++) {
        uart_dec(mac_address[i]);
        if (i < 5) uart_puts(":");
    }
    uart_puts("\n");
}

void mbox_buffer_setup(unsigned int buffer_addr, unsigned int tag_identifier, unsigned int num_values, unsigned int response, int *res_data, ...) {
    // Point to the buffer address
    volatile unsigned int *mbox = (volatile unsigned int *)buffer_addr;

    // Initialize the buffer with zeros
    for (int i = 0; i < 36; i++) {
        mbox[i] = 0;
    }

    // Set the total buffer size
    mbox[0] = 8 * 4;

    // Set the request code
    mbox[1] = MBOX_REQUEST;

    // Set the TAG identifier
    mbox[2] = tag_identifier;

    mBuf[3] = num_values * 3; // Response length
    mBuf[4] = 0; // REQUEST CODE = 0

    // Variadic arguments (request values) passed to the function
    va_list args;
    va_start(args, num_values);
    for (uint32_t i = 0; i <= num_values; i++) {
        mBuf[5 + i] = va_arg(args, uint32_t);
    }
    va_end(args);

    mBuf[7] = MBOX_TAG_LAST;

    // Set the response data pointer
    *res_data = (unsigned int)&mbox[response];
}

void main() {
    // set up serial console
    uart_init();
    // say hello
    uart_puts("Hello World!\n");
    // mailbox data buffer: Read ARM frequency
    mBuf[0] = 8*4; // Message Buffer Size in bytes (8 elements * 4 bytes (32 bit) each)
    mBuf[1] = MBOX_REQUEST; // Message Request Code (this is a request message)
    mBuf[2] = 0x00030002; // TAG Identifier: Get clock rate
    mBuf[3] = 8; // Value buffer size in bytes (max of request and response lengths)
    mBuf[4] = 0; // REQUEST CODE = 0
    mBuf[5] = 3; // clock id: ARM system clock
    mBuf[6] = 0; // clear output buffer (response data are mBuf[5] & mBuf[6])
    mBuf[7] = MBOX_TAG_LAST;
    if (mbox_call(ADDR(mBuf), MBOX_CH_PROP)) {
        uart_puts("Response Code for whole message: ");
        uart_hex(mBuf[1]);
        uart_puts("\n");
        uart_puts("Response Code in Message TAG: ");
        uart_hex(mBuf[4]);
        uart_puts("\n");
        uart_puts("DATA: ARM clock rate = ");
        uart_dec(mBuf[6]);
        uart_puts("\n");
    } else {
        uart_puts("Unable to query!\n");
    }

    show_info();

    // echo everything back
    while(1) {
        //read each char
        char c = uart_getc();
        //send back twice
        uart_sendc(c);
        uart_sendc(c);
    }
}


