### Data type size
The actual memory occupation of data types is usually not known *a priori*: the dimensions of `int`, `long`, `double` depend on the architecture where the code is compiled.

For this reason, C language introduced standard exact-width integer types (introduced in C99, defined in [§ 7.18.1.1](https://www.dii.uchile.cl/~daespino/files/Iso_C_1999_definition.pdf) of ISO/IEC 9899:1999).

This simple code prints on `stdout` the size occupied in memory, in bytes, by several data types. As regards `x86_64 GNU/Linux`, the results are:


```
Size of char, sizeof(char): 1
Size of short: 2
Size of int: 4
Size of long: 8
Size of unsigned long: 8
Size of long long: 8
Size of unsigned long long: 8
Size of size_t: 8
Size of void*: 8
Size of float: 4
Size of double: 8
Size of uint8_t: 1
Size of int8_t: 1
Size of uint32_t: 4
Size of int32_t: 4
Size of uint64_t: 8
Size of int64_t: 8
```
