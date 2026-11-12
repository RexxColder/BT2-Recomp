#include "common.h"

s32 BtlScene_IsCharStopped(s32 arg0);
void func_00129C38(s32 arg0, s32 arg1);
void func_00149990(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_001F3758(s32 arg0);

void func_0014A260(s32 arg0) {
    u8 *s0;
    s32 *s2;
    s32 s3;

    s0 = *(u8 **)((u8 *)arg0 + 0x38);
    s3 = *(s32 *)((u8 *)func_001F3758(arg0) + 0x38);
    s2 = *(s32 **)(s0 + 0xC0);
    if (BtlScene_IsCharStopped(*s2) == 0) {
        if (*(u16 *)((u8 *)arg0 + 8) & 1) {
            func_00129C38((s32)(s0 + 0x90), (s32)((u8 *)arg0 + 0x10));
            if ((*(s32 *)s0 & 0x20) == 0) {
                func_00149990(*s2, arg0, s3, 1);
                *(s32 *)s0 = *(s32 *)s0 | 0x20;
            }
        }
        if (*(u16 *)((u8 *)arg0 + 8) & 4) {
            *(s32 *)s0 = *(s32 *)s0 | 1;
        }
    }
}
