# Vector
A simple dynamic array implementation in C using a single header file, inspired by https://github.com/nothings/stb/.

## Build Instructions

```
gcc main.c -o main
```

## Using Vector.h

To include Vector.h, do as follows

```c
#define VECTOR_H_IMPLEMENTATION
#include "Vector.h"
```

If `VECTOR_H_IMPLEMENTATION` is not defined, Vector.h acts as a header file with only the forward declarations so that the functions can be rewritten if required. Adding `VECTOR_H_IMPLEMENTATION`, makes it behave like a fully featured library.
