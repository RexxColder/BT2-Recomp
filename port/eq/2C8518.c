#include "common.h"

extern void *memcpy(void *dst, const void *src, u32 n);
s32 func_002CA9A0(s32 arg0);
void func_002DA3A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* 0x002C8518: fills a free slot of the table at arg0 (slot pointer from func_002CA9A0, slot
 * state word 0). Stores the count arg2[1] (clamped to 0x200) at slot+0x238 and runs
 * func_002DA3A8 on the slot's sub-record at +0x38. Index arg1 gives two words (+4, +8: 50*index
 * and 1, or 0 and 0 for the last index 0x3FFFF), 0x28 bytes from arg0+0xD30+0x3C go to slot+0xC,
 * the word at arg0+0xD30+0x64 to slot+0x34, and the state word is set to 1. */
void func_002C8518(u8 *arg0, s32 arg1, u8 *arg2) {
    u8 *s0;
    u8 *s2n = arg0 + 0xD30;
    s32 a2;

    s0 = (u8 *)(s32)func_002CA9A0((s32)arg0);
    if (s0 == NULL) {
        return;
    }
    if (*(s32 *)s0 != 0) {
        return;
    }

    a2 = *(s32 *)(arg2 + 4);
    if (a2 >= 0x201) {
        a2 = 0x200;
    }
    *(s32 *)(s0 + 0x238) = a2;
    func_002DA3A8((s32)(s0 + 0x38), *(s32 *)arg2, a2, 0x200);

    if (arg1 != 0x3FFFF) {
        *(s32 *)(s0 + 0x08) = 1;
        *(s32 *)(s0 + 0x04) = (s32)((u32)arg1 * 50u);
    } else {
        *(s32 *)(s0 + 0x04) = 0;
        *(s32 *)(s0 + 0x08) = 0;
    }

    memcpy(s0 + 0x0C, s2n + 0x3C, 0x28);
    *(s32 *)(s0 + 0x34) = *(s32 *)(s2n + 0x64);
    *(s32 *)s0 = 1;
}
