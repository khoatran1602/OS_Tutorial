#include "printf.h"
#include "uart.h"

#define MAX_PRINT_SIZE 256

void printf(char *string, ...) {
	va_list ap;
	va_start(ap, string);

	char buffer[MAX_PRINT_SIZE];
	int buffer_index = 0;

	char temp_buffer[MAX_PRINT_SIZE];

	while (1) {
		if (*string == 0)
			break;  // Exit the loop if we reach the end of the string

		if (*string == '%') {
			string++;  // Move to the next character after '%'

			if (*string == 'd') {
				string++;  // Move to the next character after 'd'
				int x = va_arg(ap, int);  // Get the next argument as an integer
				int temp_index = MAX_PRINT_SIZE - 1;

				do {
					temp_buffer[temp_index] = (x % 10) + '0';  // Convert the integer digit to its ASCII representation
					temp_index--;
					x /= 10;
				} while (x != 0);

				for (int i = temp_index + 1; i < MAX_PRINT_SIZE; i++) {
					buffer[buffer_index] = temp_buffer[i];  // Copy the digits from the temporary buffer to the main buffer
					buffer_index++;
				}
			} else if (*string == 'x') {
				string++;  // Move to the next character after 'x'
				unsigned int x = va_arg(ap, unsigned int);  // Get the next argument as an unsigned integer
				int temp_index = MAX_PRINT_SIZE - 1;
				const char *hex_chars = "0123456789abcdef";

				do {
					temp_buffer[temp_index] = hex_chars[x % 16];  // Convert the remainder to its corresponding hex character
					temp_index--;
					x /= 16;
					} while (x != 0);

				for (int i = temp_index + 1; i < MAX_PRINT_SIZE; i++) {
					buffer[buffer_index] = temp_buffer[i];  // Copy the hex digits from the temporary buffer to the main buffer
					buffer_index++;
				}
			} else if (*string == 'o') {
				string++;  // Move to the next character after 'o'
				unsigned int x = va_arg(ap, unsigned int);  // Get the next argument as an unsigned integer
				int temp_index = MAX_PRINT_SIZE - 1;

				do {
					temp_buffer[temp_index] = (x % 8) + '0';  // Convert the remainder to its corresponding octal digit
					temp_index--;
					x /= 8;
				} while (x != 0);

				for (int i = temp_index + 1; i < MAX_PRINT_SIZE; i++) {
					buffer[buffer_index] = temp_buffer[i];  // Copy the octal digits from the temporary buffer to the main buffer
					buffer_index++;
				}
			} else if (*string == 'c') {
				string++;  // Move to the next character after 'c'
				char c = (char)va_arg(ap, int);  // Get the next argument as a character
				buffer[buffer_index] = c;  // Copy the character to the main buffer
				buffer_index++;
			} else if (*string == 's') {
				string++;  // Move to the next character after 's'
				char *s = va_arg(ap, char *);  // Get the next argument as a string
				while (*s != '\0' && buffer_index < MAX_PRINT_SIZE - 1) {
					buffer[buffer_index] = *s;  // Copy the characters from the string to the main buffer
					buffer_index++;
					s++;
				}
			} else if (*string == 'f') {
				string++;  // Move to the next character after 'f'
				double f = va_arg(ap, double);  // Get the next argument as a double
				// Assume a fixed decimal precision of 6
				int precision = 6;
				int int_part = (int)f;
				double fractional_part = f - int_part;

				// Print integer part
				int temp_index = MAX_PRINT_SIZE - 1;
				do {
					temp_buffer[temp_index] = (int_part % 10) + '0';  // Convert the integer digit to its ASCII representation
					temp_index--;
					int_part /= 10;
				} while (int_part != 0);

				for (int i = temp_index + 1; i < MAX_PRINT_SIZE; i++) {
					buffer[buffer_index] = temp_buffer[i];  // Copy the digits from the temporary buffer to the main buffer
					buffer_index++;
				}

				// Print decimal point
				buffer[buffer_index] = '.';
				buffer_index++;

				// Print fractional part
				for (int i = 0; i < precision; i++) {
					fractional_part *= 10;
					int digit = (int)fractional_part;
					buffer[buffer_index] = digit + '0';  // Convert the integer digit to its ASCII representation
					buffer_index++;
					fractional_part -= digit;
				}
			} else if (*string == '%') {
				string++;  // Move to the next character after '%'
				buffer[buffer_index] = '%';  // Copy the '%' character to the main buffer
				buffer_index++;
			}
		} else {
			buffer[buffer_index] = *string;  // Copy the character from the string to the main buffer
			buffer_index++;
			string++;
		}

		if (buffer_index == MAX_PRINT_SIZE - 1)
			break;  // Exit the loop if the buffer is full
	}

	va_end(ap);

	// Null-terminate the buffer
	buffer[buffer_index] = '\0';

	// Print out formatted string
	uart_puts(buffer);
}
