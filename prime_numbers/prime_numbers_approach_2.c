#include <stdio.h>
#include <stdint.h>
/* for uint64_x */
#include <inttypes.h>
/* for PRIu64 and SCNu64 */
#include <stdlib.h>
/* for strtoul() */
 
int main (int argc, char *argv[]) {

	uint64_t i, j, N;
	int p;

	if (argc < 2) {
	        printf("Please, enter an integer number as argument to this program.\n");
	        return 0;
	} else if (argc > 2) {
	        printf("Please, note that only the first parameter will be considered.\n");
	}

	N = (uint64_t)strtoul(argv[1], NULL, 10);

	if (N == 2)
		printf("%" PRIu64 "\n", N);

	if (N > 2) {
		/* check each number i from 3 to N */
		for (i = 3; i <= N; i++) {
			/* Only consider odd numbers */
			if (i%2 == 1) {
				p = 1;
				/* if i is divisible by any of the previous integers, starting from 2 to i / 2, it is not prime */
				for(j = 2; j <= i / 2; j++) {
					if(i%j == 0) {
						p = 0;
						break;
					}
				}
				/* if i is not divisible by any of the previous integers, it is prime: print its value to stdout */
				if (p == 1)
					printf("%" PRIu64 "\n", i);
			}
		     
		}
	}

        return 0;
}
