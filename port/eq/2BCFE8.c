#include "common.h"

/* GUESS arity: a0 (the arg0 pointer) and a1 (D_00345344) are passed through to func_002BD1D0 */
s32 func_002BD1D0(s32 arg0, s32 arg1);
s32 func_002BD088(s32 arg0);
s32 func_002BD298(void);
void Rand_Range(s32 arg0, s32 arg1);
extern s32 D_00345344 __attribute__((section(".data")));
extern u8 D_00379F88[] __attribute__((section(".data")));

s32 func_002BCFE8(s32 *arg0) {
    s32 temp_s0;

    if (D_00345344 == 1) {
        if (arg0 == 0) {
            Rand_Range((s32)D_00379F88, D_00345344);
            return 0;
        }
        temp_s0 = *arg0;
        if (temp_s0 == D_00345344) {
            if (func_002BD1D0((s32)arg0, D_00345344) == temp_s0) {
                return 0;
            }
            if (func_002BD298() != temp_s0) {
                return func_002BD088((s32)arg0);
            }
            return 0;
        }
        return 0;
    }
    return 0;
}
