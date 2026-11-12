#include "m2c_macros.h"

void func_003126C8();             /* extern */

void func_0020E9A0(void *arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3) {
    void *temp_s0;

    temp_s0 = (char *)arg0 + (arg3 * 0x10);
    func_003126C8(temp_s0 + 0x7B0, arg1);
    func_003126C8(temp_s0 + 0x830, arg2);
    M2C_FIELD(arg0, s32 *, 0x8B0) = (s32) (M2C_FIELD(arg0, s32 *, 0x8B0) | (1 << arg3));
    func_003126C8(arg0 + 0x820, arg1);
    func_003126C8(arg0 + 0x8A0, arg2);
    M2C_FIELD(arg0, s32 *, 0x8B0) = (s32) (M2C_FIELD(arg0, s32 *, 0x8B0) | 0x80);
}
