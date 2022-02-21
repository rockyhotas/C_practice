/*
 * Copyright (C) 2021 Rocky Hotas
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * As regards GPLv3: https://www.gnu.org/licenses/gpl-3.0.html
*/


#include <stdio.h>
#include <stdint.h>
/* for uint64_x */
#include <inttypes.h>
/* for PRIu64 and SCNu64 */
#include <stdlib.h>
/* for malloc and strtoul() */

// #include <math.h>
/* for sqrt(). But compile this file with:
 * 
 * gcc prime_test_square.c -o prime_test_square -lm
 *
 * https://stackoverflow.com/a/10409061 */

/* Only conceived for unsigned integer numbers */

/* Build a list of prime numbers and use them to
   check if the current number is prime */

typedef struct prime_list_node {
	uint64_t prime;
	struct prime_list_node *next;
} prime_list;

uint64_t limit;
prime_list *prime_head = NULL;
// pointer to the first element of the list: once it's different from NULL, it should be never modified
prime_list *prime_tail = NULL;

int prime_test (uint64_t candidate) {
	prime_list *next_prime = prime_head;
	//double upper_prime = sqrt(candidate);
	/* It must be computed just once, it doesn't matter if it is double.
	 * https://stackoverflow.com/a/24770694
	 * Check if this conversion arises precision problems. */
	// To avoid the use of sqrt: https://stackoverflow.com/a/37513428

	// check if candidate is divisible by one of the prime numbers obtained so far
	if (next_prime != NULL) {
		while (next_prime) {
			if ((candidate%next_prime->prime == 0) && (next_prime->prime * next_prime->prime <= candidate)) {
			//if (candidate%next_prime->prime == 0) {
				/* The "useful" prime numbers to perform the division test must not be
				 * greater than n / 2, which is the greatest possible integer divisor of
				 * n, if n is even. If n is odd, the greatest possible divisor is smaller
				 * than the integer part of n / 2. */
				// if candidate is divisible by a prime number, it is not a prime
				return 1;
			}
			else {
				if ((next_prime->next != NULL) && (next_prime->prime * next_prime->prime <= candidate)) {
				//if (next_prime->next != NULL) {
					next_prime = next_prime->next;
					continue;
				} else {
					prime_list *added_prime = (prime_list *) malloc(sizeof(prime_list));
					added_prime->prime = candidate;
					added_prime->next = NULL;
					/* Add the newly created item to the prime list, overwriting the NULL next pointer of
					 * the prime_tail item */
					prime_tail->next = added_prime;
					/* Using next_prime->next would cut off all the primes after next_prime: this iteration
					 * ends possibly before the list of primes ends, because of `candidate / 2'! */
					/* Now update the tail of the list: */
					prime_tail = added_prime;
					/* Print the new prime number to stdout */
					printf("%" PRIu64 "\n", candidate);
					return 0;
				}
			}
		}
	
	}
	else {
		// here, candidate should always be 2
		// create the prime list
		prime_head = (prime_list *) malloc(sizeof(prime_list));
		prime_head->prime = candidate;
		prime_head->next = NULL;
		prime_tail = prime_head;
		// in this moment, head and tail of the prime list are the same item
	}

	return 0;
}

void prime_list_generation (uint64_t border) {
	uint64_t i;

	if (border >= 2) {
		prime_test(2);	// create the first prime number
		for (i = 3; i <= border; i++) {
			// with i > 2, only odd numbers can be prime
			if (i%2 == 1) {
				prime_test(i);
			}
		}
	}

	if (border == 0 || border == 1) {
		printf("The selected number is too low. There are no prime numbers less than or equal to it.\n");
		return;
	}

	return;
}

/*
void prime_list_print () {
	prime_list *next_prime = prime_head;

	while (next_prime) {
		printf("%" PRIu64 "\n", next_prime->prime);
		next_prime = next_prime->next;
	}

	return;
}
*/


int main (int argc, char *argv[]) {
	if (argc < 2) {
		printf("Please, enter an integer number as argument to this program.\n");
		return 0;
	} else if (argc > 2) {
		printf("Please, note that only the first parameter will be considered.\n");
	}

	limit = (uint64_t)strtoul(argv[1], NULL, 10);
	/* There are no `strtouint64_t' functions available, apparently. However, usigned long in the current x86_64 system is 8 bytes,
         * exactly as uint64_t, which is unsigned, too. So, this convertion should not arise ambiguities, because it's made between
         * equivalent data types. */
	//printf("Enter an integer number:\n");
	//scanf("%" SCNu64, &limit);
	prime_list_generation(limit);
	//prime_list_print();

	return 0;
} 


/* When dealing with a big `limit', the (f)printf instructions make the difference: for limit = 1500000 they may require hundreds of seconds of extra time.
 * Removing all the unnecessary (f)printf, the computing time drops. */
