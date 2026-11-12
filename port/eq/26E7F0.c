#include "common.h"

s32 func_0026C010(s32 arg0, s32 arg1);
s32 func_0026CA00(s32 arg0, s32 arg1);
s32 func_0026DE08(s32 arg0, s32 arg1, s32 arg2);
s32 func_0026F6C0(s32 arg0, s32 arg1);
s32 func_0026FC88(s32 arg0, s32 arg1);
s32 func_0028BAA8(s32 arg0);
s32 memset(s32 arg0, s32 arg1, s32 arg2);

void func_0026E7F0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    memset(arg0, 0, 0x28);
    *(s32 *)(arg0 + 0) = arg1;
    *(s32 *)(arg0 + 4) = arg2;
    *(s32 *)(arg0 + 8) = 0;
    *(s32 *)(arg0 + 0xC) = 0;
    *(s32 *)(arg0 + 0x10) = 0;
    temp_v0 = func_0028BAA8(0x18);
    *(s32 *)(arg0 + 0x18) = temp_v0;
    memset(temp_v0, 0, 0x18);
    func_0026DE08(arg0, *(s32 *)(arg0 + 0x18), func_0026CA00(*(s32 *)(arg0 + 0), 5));
    *(u8 *)(*(s32 *)(arg0 + 0x18) + 0x11) = (u8)(*(u8 *)(*(s32 *)(arg0 + 0x18) + 0x11) | 2);
    temp_v0 = func_0028BAA8(8);
    *(s32 *)(arg0 + 0x1C) = temp_v0;
    memset(temp_v0, 0, 8);
    func_0026FC88(*(s32 *)(arg0 + 0x1C), arg0);
    temp_v0 = func_0028BAA8(8);
    *(s32 *)(arg0 + 0x20) = temp_v0;
    memset(temp_v0, 0, 8);
    func_0026F6C0(*(s32 *)(arg0 + 0x20), arg0);
    temp_v0 = func_0028BAA8(0x44);
    *(s32 *)(arg0 + 0x24) = temp_v0;
    memset(temp_v0, 0, 0x44);
    func_0026C010(*(s32 *)(arg0 + 0x24), arg0);
}
