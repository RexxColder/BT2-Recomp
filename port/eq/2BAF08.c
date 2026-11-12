#include "common.h"

s32 func_002B8280(s32 arg0);
s32 Rand_Range(s32 arg0, s32 arg1);
s32 func_002BB418(s32 arg0, s32 arg1);
extern u8 D_00379C18[] __attribute__((section(".data")));

/* 0x002BAF08: if func_002B8280(arg0) != 1 tail call Rand_Range(&D_00379C18, 0); else tail call func_002BB418(arg0, 0). */
s32 func_002BAF08(s32 arg0) {
    if (func_002B8280(arg0) != 1) {
        return Rand_Range((s32)D_00379C18, 0);
    }
    return func_002BB418(arg0, 0);
}
