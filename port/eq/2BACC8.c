#include "common.h"

/* GUESS arity: a0 is passed through to func_002B8280 (not written before the call) */
s32 func_002B8280(s32 arg0);
void Rand_Range(s32 arg0, s32 arg1);
void func_002B3190(s32 arg0);
void func_002B7088(s32 arg0, s32 arg1);
void func_002B7448(s32 arg0);
void func_002BB418(s32 arg0, s32 arg1);
void func_002FFEF8(s32 arg0);
extern u8 D_00379B20[] __attribute__((section(".data")));

void func_002BACC8(u8 *arg0) {
    s32 *temp_v0;

    if (func_002B8280((s32)arg0) != 1) {
        Rand_Range((s32)D_00379B20, 1);
        return;
    }
    func_002BB418((s32)arg0, 1);
    func_002B7088((s32)arg0, *(s32 *)(arg0 + 0x1C0));
    func_002B7448((s32)arg0);
    func_002FFEF8(*(s32 *)(arg0 + 0x48));
    temp_v0 = (s32 *)*(s32 *)(arg0 + 0x1BC);
    if (temp_v0 != 0) {
        ((void (*)(s32))(*(s32 *)(*temp_v0 + 0x14)))((s32)temp_v0);
    }
    func_002B3190((s32)arg0);
    *(s32 *)(arg0 + 0x2D4) = 0;
}
