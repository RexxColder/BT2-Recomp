#include "common.h"

s32 BtlScene_IsCharStopped(s32 arg0);
void EftTechEvt_RequestStop(s32 arg0);
void func_00129C38(s32 arg0, s32 arg1);

void func_0016A1E8(u8 *arg0) {
    u8 *s0;
    u8 *s2;
    s32 r;
    s32 v1;

    s0 = *(u8 **)(arg0 + 0x38);
    s2 = *(u8 **)(s0 + 0xB0);
    r = BtlScene_IsCharStopped(*(s32 *)s2);
    if (r != 0) {
        return;
    }
    *(s32 *)s0 = *(s32 *)s0 & ~0x20;
    if (*(u16 *)(arg0 + 8) & 1) {
        func_00129C38((s32)(s0 + 0x80), (s32)(arg0 + 0x10));
        *(s32 *)(s0 + 4) = *(s32 *)(s0 + 4) & ~8;
        *(s32 *)s0 = *(s32 *)s0 | 0x20;
    }
    v1 = *(s32 *)(arg0 + 4);
    if (v1 & 1) {
        if ((v1 & 2) == 0) {
            EftTechEvt_RequestStop(*(s32 *)s2);
            *(s32 *)s0 = (*(s32 *)s0 & ~0x10) | 0x200;
        } else {
            *(s32 *)s0 = (*(s32 *)s0 | 0x100) & ~0x10;
        }
    } else if ((v1 & 2) != 0 || (v1 & 4) != 0) {
        *(s32 *)s0 = (*(s32 *)s0 | 0x100) & ~0x10;
    }
    if (*(u16 *)(arg0 + 8) & 4) {
        *(s32 *)s0 = (*(s32 *)s0 | 1) & ~0x10;
        *(s32 *)(s0 + 4) = *(s32 *)(s0 + 4) & ~8;
    }
}
