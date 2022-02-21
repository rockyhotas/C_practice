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
/* for malloc */

/* Only conceived for unsigned integer numbers */

/* Build a list of prime numbers and use them to
   check if the current number is prime */

typedef struct prime_list_node {
	uint64_t prime;
	struct prime_list_node *next;
} prime_list;

uint64_t limit;
prime_list *prime_head = NULL;
prime_list *prime_tail = NULL;

int prime_test (uint64_t candidate) {
	prime_list *next_prime = prime_head;

	// check if candidate is divisible by one of the prime numbers obtained so far
	if (next_prime != NULL) {
		//fprintf(stderr, "Prime list already existing\n"); // DEBUG
		while (next_prime) {
			//fprintf(stderr, "address of prime to be tested: %" PRIu64 "\n", (uint64_t)next_prime); // DEBUG
			if ((candidate%next_prime->prime == 0) && (next_prime->prime <= candidate / 2)) {
				//fprintf(stderr, "divisible\n"); // DEBUG
				// if candidate is divisible by a prime number, it is not a prime
				return 1;
			}
			else {
				if ((next_prime->next != NULL) && (next_prime->prime <= candidate / 2)) {
					next_prime = next_prime->next;
					//fprintf(stderr, "continue\n"); // DEBUG
					continue;
				} else {
					//fprintf(stderr, "not divisible by any prime number of the list\n"); // DEBUG
					prime_list *added_prime = (prime_list *) malloc(sizeof(prime_list));
					added_prime->prime = candidate;
					added_prime->next = NULL;
					//fprintf(stderr, "added another prime\n"); // DEBUG
					prime_tail->next = added_prime;
					prime_tail = added_prime;
					//fprintf(stderr, "address of new prime: %" PRIu64 "\n", (uint64_t)next_prime->next); // DEBUG
					/* Print the new prime number to stdout */
                			printf("%" PRIu64 "\n", candidate);
					return 0;
				}
			}
		}
	
	}
	else {
		fprintf(stderr, "Creation of prime list\n");
		
		// here, candidate should always be 2
		// create the prime list
		prime_head = (prime_list *) malloc(sizeof(prime_list));
		prime_head->prime = candidate;
		prime_head->next = NULL;
		prime_tail = prime_head;
		// in this moment, head and tail of the prime list are the same item
		//fprintf(stderr, "list head is: %" PRIu64 "\n", (uint64_t)prime_head); // DEBUG
	}

	return 0;
}


void prime_list_generation (uint64_t border) {
        uint64_t i;

        if (border >= 2) {
                prime_test(2);  // create the first prime number
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
	//printf("Enter an integer number:\n");
	//scanf("%" SCNu64, &limit);
	printf("Ok, all the prime numbers till %" PRIu64 " will be printed now:\n", limit);
	prime_list_generation(limit);

	return 0;
} 
