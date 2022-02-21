#include <stdio.h>
#include <stdint.h>

/* Based on
   https://stackoverflow.com/a/3225548/2501622
 */

/* https://stackoverflow.com/a/2524675
   https://stackoverflow.com/a/2524876
   as regards zu */

int main() {
	printf("The sizeof() operator yields the number of bytes required to store an object of the type of\n"
	"its operand.\n");
	printf("Rigorously speaking, sizeof() returns an unsigned integral constant, a value of type size_t,\n"
	"whose definition depends on the current system and it is specified in the header file <stddef.h>.\n");
	printf("To clear any ambiguity, the standard type int8_t or uint8_t is 1 byte, regardless of the\n"
	"platform it is implemented on. Therefore, the result of sizeof performed on uint8_t is the unit of\n"
	"measurement in bytes of any other sizeof measurement. If sizeof(uint8_t) is 1, then any other result\n"
	"given by sizeof() is expressed in bytes.\n");
	printf("\n");
	printf("Size of char, sizeof(char): %zu\n", sizeof(char));
	printf("Size of short: %zu\n", sizeof(short));
	printf("Size of int: %zu\n", sizeof(int));
	printf("Size of long: %zu\n", sizeof(long));
	printf("Size of unsigned long: %zu\n", sizeof(unsigned long));
	printf("Size of long long: %zu\n", sizeof(long long));
	printf("Size of unsigned long long: %zu\n", sizeof(unsigned long long));
	printf("Size of size_t: %zu\n", sizeof(size_t));
	printf("Size of void*: %zu\n", sizeof(void*));
	printf("Size of float: %zu\n", sizeof(float));
	printf("Size of double: %zu\n", sizeof(double));
	printf("Size of uint8_t: %zu\n", sizeof(uint8_t));
	printf("Size of int8_t: %zu\n", sizeof(int8_t));
	printf("Size of uint32_t: %zu\n", sizeof(uint32_t));
	printf("Size of int32_t: %zu\n", sizeof(int32_t));
	printf("Size of uint64_t: %zu\n", sizeof(uint64_t));
	printf("Size of int64_t: %zu\n", sizeof(int64_t));

	return 0;
}
