### Prime numbers

The generation of prime numbers is a suitable way to test the performance of a code approach, of a programming language, of a whole platform.

Consider the following problem: given an integer number `N`, print all the prime numbers less than, or equal to, `N`.

Remember that only integer numbers and integer results are considered here. A Ubuntu 20.04 `x86_64` platform with Intel&reg; Core&trade; i5-4670 CPU @ 3.40GHz is used to run this code, compiled in each case with `gcc sourcefile.c -o executable`. The step improvements presented here are based on [this reference](https://www.geeksforgeeks.org/program-to-print-first-n-prime-numbers/).

#### Approach 1
According to the formal definition, a number `n` is prime if it is not divisible by any number other than 1 and itself, `n`. 

`0` can not be divisible by itself, so it can not be considered prime. `1` is not considered prime as well, because it is its only divisor. The smallest prime number is `2`, which is also the only even number to be prime. Strictly speaking, according to the above definition, a number `n > 2` is prime if it is not divisible by any number from `2` to `n-1`. It is enough to run this division test for all the integers between `2` and `N`.

However, several other considerations can be made to write a more efficient algorithm.

#### Approach 2
Is it really necessary to iterate through all the numbers from `2` to `n-1`?

`2` (which is prime) is the smallest number which can appear in the factorization of any integer number `n > 2`. If `2` is in the factorization of `n`, `n` is divisible by `n/2` and, being `2` the smallest divisor of `n`, `n/2` is its greatest divisor. So, the possible divisors of any number `n > 2` span from `2` to `n/2`. It is not necessary to span from `2` to `n` to check if `n` is prime. If `n` has divisors smaller than `n` and greater than `1`, the greatest of them will be `<= n/2`. Using the `int` data type, if `n/2` is not integer (that is: if `n` is odd and can not be divided by `2`), the algorithm will stop even before, at the integer number before `n/2`: `(n - 1)/2`. Moreover, except `2`, even numbers can not be prime numbers: so, the division check for a number `n > 2` must only be performed when `n` is odd.

#### Approach 3
The factorization of `n` is a *list* of all the prime numbers that are divisors of `n`. It is enough, therefore, to check all the *prime* numbers between `2` and `n/2`, not *all* the numbers. The other ones are unessential, because they can themselves be factored using the prime numbers.

This would imply to keep, and continuously update, a list of prime numbers during the execution. If the limit value `N` is not known, this list can not be an array, because it must be dynamically allocated, each time a new prime number is "discovered".

As regards complexity, in the previous prime numbers programs, the prime numbers obtained are printed in the `stdout`, then forgotten. Instead, here, all the discovered prime numbers should be maintained into memory during the whole execution (and writing, and then reading them, to/from a file for each prime number test would imply a longer time waste). This adds complexity (as regards code and as regards system resources; however, the dimensions of the list, in bytes of memory, are tiny, few MB even with large `N`), but such an approach is theoretically more efficient, because it aims at reducing the number of unnecessary operations.

The number `N` provided by the user is stored in the variable

```
uint64_t limit;
```

The linked list of items, used to store the prime numbers, is defined as:

```
typedef struct prime_list_node {
        uint64_t prime;
        struct prime_list_node *next;
} prime_list;
```

This is a recursive definition, which is allowed by C. Each item stores a prime number and a pointer to the next list item. This pointer, in the last item, has value `NULL`.

```
prime_list *prime_head = NULL;
prime_list *prime_tail = NULL;
```

Outside the list, two pointers are kept as global variables: one to the first element of the list, `prime_head`, and one to the last element of the list, `prime_tail`. In the beginning, both are initialized to `NULL`; once a list is created, `prime_head` is updated and should be never modified again; `prime_tail` is instead modified each time a new item is added to the list (and it is always added at the end of the list).

The elements of this prime numbers list are, in other words, dynamically created: a new item is added each time a new prime number is discovered. For dynamically allocated data, in C it is necessary to use `malloc()`, because otherwise the compiler can not determine the amount of space to be reserved for the data structures ([Reference 1][dynamic_allocation_1]) ([Reference 2][dynamic_allocation_2]).

In function `prime_test`, the creation of a list of primes is performed when `prime_head` is `NULL`:

```
prime_head = (prime_list *) malloc(sizeof(prime_list));
prime_head->prime = candidate;
prime_head->next = NULL;
prime_tail = prime_head;
```

Now, consider:

```
if ((next_prime->next != NULL) && (next_prime->prime <= candidate / 2)) {
	next_prime = next_prime->next;
	fprintf(stderr, "continue\n"); // DEBUG
	continue;
} else {
```

This `else` is about the case when there are no more prime numbers for the division test: `candidate` is not divisible by any of the current prime numbers, therefore it is a prime number. `next_prime` is still pointing to the last element of the prime list explored by the `while` loop: it is not necessarily the last discovered prime, because the iterations stop when the prime numbers reach the value `candidate / 2`.

```
prime_list *added_prime = (prime_list *) malloc(sizeof(prime_list));
added_prime->prime = candidate;
added_prime->next = NULL;
```

Create a new item, `added_prime`, for the list of prime numbers. Its `prime` member must store the value of `candidate`, the new prime just found; the `next` pointer should be `NULL`, because this is the current last item of the prime list.

    prime_tail->next = added_prime;

Add the newly created item to the prime list, overwriting the `NULL` value of pointer `next` of the `prime_tail` item. As already pointed out, the new prime number is added at the tail of the list.

    prime_tail = added_prime;

Update the pointer to the tail of the list. Using `next_prime->next` here, instead of `prime_tail`, would cut off all the primes after `next_prime`: as already noticed, this iteration ends possibly before the list of primes ends, because of `candidate / 2`.

    limit = (uint64_t)strtoul(argv[1], NULL, 10);

There are no `strtouint64_t` functions available, apparently. However, `usigned long` in the current `x86_64` system is 8 bytes, exactly as `uint64_t`, which is unsigned, too. So, this convertion should not arise ambiguities, because it is made between equivalent data types.

In the source file, several commented lines ending with `DEBUG` are included: they may be useful to inspect the program, but beware that, if they are uncommented, the performances drop with large `N`.


#### Approach 4
If a number `n` is not prime, it is called a [*composite number*](https://en.wikipedia.org/wiki/Composite_number). Assume that a composite number `n` has two (not necessarily different) prime numbers `a, b` different from `n`, with `a, b` between `2` and `n`. It is: `n = a * b`.

If both `a > sqrt(n)`, `b > sqrt(n)` (`sqrt(n)` is the square root of `n`), their product would be `a * b > n`, which is not possible. If `a >= sqrt(n)`, it must necessarily be `b <= sqrt(n)` and vice versa. In the special case where `a = sqrt(n)`, it must be `a = b = sqrt(n)`, so that `a * b = n`. In all the other cases, *at least one* between `a` and `b` must be less than `sqrt(n)` ([Reference][prime_sqrt]). Be careful: this only guarantees that, if `n` is not prime, it must have a prime divisor which is `<= sqrt(n)`, but it can also still have a prime divisor which is `>= sqrt(n)`. This result can be exploited to further reduce the number of divisions to determine if `n` is prime or not.

If `n` is not a prime number, the research of a prime divisor must only be performed till `sqrt(n)`: if there is no divisor `<= sqrt(n)`, `n` is prime. This is an enormous performace improvement for large values of `N`.


#### Tests

```
$ time ./prime_numbers_approach_1 2100000
[omitted printed prime numbers]

real    20m29,012s
user    20m27,550s
sys     0m1,125s
```

The first prime numbers are quickly computed. As the numbers grow, however, the checks to be performed (to determine if the current candidate number is prime) increase, so the discovery of new prime numbers gets slower. This is not just a feature of "approach 1", but of all the approaches followed here. The difference between them is how many prime numbers they managed to generate before becoming slower. As regards "approach 1", it becomes slower after few prime numbers.


```
$ time ./prime_numbers_approach_2 2100000
[omitted printed prime numbers]

real    9m15,008s
user    9m14,649s
sys     0m0,317s
```

The simple improvements of considering only the odd numbers `n > 2` and dividing them only by the numbers till `n/2` halved the time required.


```
$ time ./prime_numbers_approach_3 2100000
[omitted printed prime numbers]

real    0m58,166s
user    0m57,949s
sys     0m0,212s
```

Other than the improvements in "approach 2", considering only the previous prime numbers for the division has required only `1/10` of the time.

```
$ time ./prime_numbers_approach_4 2100000
[omitted printed prime numbers]

real    0m0,602s
user    0m0,380s
sys     0m0,220s
```

This is the most significant improvement as regards performance.

If the same test is run several times, according to the conditions of the operating system, it may give slightly different results, but the differences between these 4 different implementations keep being the same.

For *small* `N`, till `100000`, all the programs are roughly equivalent. As `N` grows, instead, wide differences appear, with approach 4 giving the best performance.



[dynamic_allocation_1]: https://stackoverflow.com/a/3889495
[dynamic_allocation_2]: https://www.learn-c.org/en/Linked_lists
[prime_sqrt]: http://mathandmultimedia.com/2012/06/02/determining-primes-through-square-root/
