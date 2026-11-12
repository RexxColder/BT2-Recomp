#include "m2c_macros.h"

void *memset(void *, int, unsigned int);

// Clears a 0x48-byte block at the incoming pointer (tail call to memset).
void func_002FD710(void *arg0) {
    memset(arg0, 0, 0x48);
}
