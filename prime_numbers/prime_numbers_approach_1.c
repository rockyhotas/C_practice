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

	if (N >= 2) {
		/* check each number i from 2 to N */
		for (i = 2; i <= N; i++) {
			p = 1;
			/* if i is divisible by any of the previous integers, starting from 2 to i - 1, it is not prime */
			for(j = 2; j <= i - 1; j++) {
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

        return 0;
}
