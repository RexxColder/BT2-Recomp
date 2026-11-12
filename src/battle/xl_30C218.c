#include "m2c_macros.h"

void *memset(void *, int, unsigned int);

// Clears a 0x2C-byte block at the incoming pointer (tail call to memset).
void func_0030C218(void *arg0) {
    memset(arg0, 0, 0x2C);
}
