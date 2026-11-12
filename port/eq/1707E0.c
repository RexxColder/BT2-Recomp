#include "common.h"

void *func_001F3758(s32 arg0);
s32 BtlScene_IsCharStopped(s32 arg0);
void EftTechEvt_RequestStop(s32 arg0);
void func_00129C38(s32 arg0, s32 arg1);
void func_0016FFE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_001707E0(u8 *arg0) {
    u8 *s0;
    s32 *s2;
    s32 s3;
    s32 a0v;
    s32 v1;

    s0 = *(u8 **)(arg0 + 0x38);
    s3 = *(s32 *)((u8 *)func_001F3758((s32)arg0) + 0x38);
    s2 = *(s32 **)(s0 + 0xD0);
    if (BtlScene_IsCharStopped(*s2) != 0 || (*(s32 *)s0 & 0x200) != 0) {
        return;
    }

    if (*(u16 *)(arg0 + 8) & 1) {
        func_00129C38((s32)(s0 + 0xA0), (s32)(arg0 + 0x10));
        func_0016FFE0(*s2, (s32)arg0, s3, 1);
        v1 = *(s32 *)s0;
        if (!(v1 & 0x20)) {
            *(s32 *)s0 = v1 | 0x20;
        }
    }

    a0v = *(s32 *)(arg0 + 4);
    if ((a0v & 1) && !(a0v & 2)) {
        if (!(*(s32 *)s0 & 0x200)) {
            EftTechEvt_RequestStop(*s2);
            *(s32 *)s0 = *(s32 *)s0 | 0x200;
            *(f32 *)(s0 + 0x1C) = *(f32 *)(s0 + 0x1C) * 3.0f;
        }
    } else if ((a0v & 2) || (a0v & 4)) {
        *(s32 *)s0 = (*(s32 *)s0 | 1) & ~0x10;
    }
}
