#include "m2c_macros.h"

void _fwalk(M2C_UNK, M2C_UNK);                   /* extern */
extern M2C_UNK fflush __attribute__((section(".data")));

// Walks the stdio file list with fflush as the callback, keeping arg0 as the reent pointer.
void func_0032AB10(void *arg0) {
    _fwalk(arg0, &fflush);
}
