#include "common.h"

void func_002F2B28();

/* Tail call to func_002F2B28 (no arguments). */
void func_002BD5D8(unsigned long r_a0, unsigned long r_a1, unsigned long r_a2) { /* asm: a0, a1, a2 arrive and pass through untouched */
    func_002F2B28(r_a0, r_a1, r_a2);
}
