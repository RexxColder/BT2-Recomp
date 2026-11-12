#include "m2c_macros.h"

void func_002C0268(M2C_UNK, M2C_UNK, M2C_UNK, s32);

/* Tail-forwards the caller's a0..a2 to func_002C0268 with a3 = 1. */
/* Forwards its a0..a2 to func_002C0268 with a3 = 1 (tail call) */
void func_002C0250(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_002C0268(arg0, arg1, arg2, 1);
}
