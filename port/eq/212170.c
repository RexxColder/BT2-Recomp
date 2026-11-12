#include "common.h"

s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
s32 func_002765A8(s32 arg0, f32 *arg1, f32 *arg2, s32 arg3);
void func_003126C8(void *arg0, f32 *arg1);
void *BtlChar_GetPos(void *arg0);
void func_002608E8(void *arg0);
void func_00260A50(void *arg0);
void func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);

void func_00212170(u8 *arg0) {
    f32 buf[8];
    s32 temp_s0;

    if (func_00211310(arg0, 9, 0x01000000) != 0) {
        temp_s0 = func_002765A8(*(s32 *)(arg0 + 0x1534), buf, buf + 4, 1);
        func_003126C8(*(u8 **)(arg0 + 0x1530) + 0x9A0, buf);
        func_003126C8(*(u8 **)(arg0 + 0x1530) + 0x9B0, buf + 4);
        *(s32 *)(*(u8 **)(arg0 + 0x1530) + 0x9F0) = temp_s0;
        *(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0xB4) = buf[5];
        *(s32 *)((u8 *)BtlChar_GetPos(arg0) + 0xB0) = 0;
        *(f32 *)(arg0 + 0x150) = buf[5];
        func_002608E8(*(u8 **)(arg0 + 0x1530));
        func_00260A50(*(u8 **)(arg0 + 0x1530));
        func_002113C0(arg0, 9, 0x01000000, 0);
    }
}
