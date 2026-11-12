#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);

void func_00113FD0(u8 *arg0, s32 arg1, s32 arg2) {
    u8 sp[8];
    s32 x20;
    s32 x30;
    s32 a;
    s32 c;
    s32 f;

    if ((u8)arg1 == 0) {
        memcpy(sp, arg0 + 4, 8);
        if ((u8)arg2 == 0) {
            return;
        }
        *(u16 *)(arg0 + 4) = 0x200 - *(u16 *)(sp + 4);
        *(u16 *)(arg0 + 8) = 0x200 - *(u16 *)(sp + 0);
    } else {
        if ((u8)arg2 == 0) {
            return;
        }
        x20 = *(s32 *)(arg0 + 0x20);
        x30 = *(s32 *)(arg0 + 0x30);
        a = 0x200 - x30;
        c = 0x200 - x20;
        *(s32 *)(arg0 + 0x40) = a;
        *(s32 *)(arg0 + 0x50) = c;
        *(s32 *)(arg0 + 0x20) = a;
        *(s32 *)(arg0 + 0x30) = c;
    }
    f = *(s32 *)(arg0 + 0);
    *(s32 *)(arg0 + 0) = f ^ 0x20;
}
