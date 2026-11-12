#include "m2c_macros.h"

void *memset(void *, int, unsigned int);

// Clears a 0x30-byte block at the incoming pointer (tail call to memset).
void func_0030B718(void *arg0) {
    memset(arg0, 0, 0x30);
}
