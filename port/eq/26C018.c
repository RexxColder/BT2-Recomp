#include "common.h"

/* 0x0026C018: memset(a0, 0, 0x44), tail call (returns memset's result). */
void *func_0026C018(void *a0) {
    return memset(a0, 0, 0x44);
}
