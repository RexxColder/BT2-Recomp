#include "common.h"

void Gsc_DumpCommand(s32 arg0, s32 arg1);
s32 Gsc_NextCommand(s32 arg0);

#define BSWAP32(x) ((((u32)(x)) >> 24) | (((u32)(x)) << 24) | ((((u32)(x)) & 0xFF00) << 8) | ((((u32)(x)) >> 8) & 0xFF00))

void Gsc_DumpFileNode(u8 *arg0) {
    u8 *a1;
    u8 *a2;
    u8 *s1;
    u8 *s2;
    u8 *s0;
    u32 w;

    a1 = *(u8 **)(arg0 + 0x1C);
    a2 = *(u8 **)(arg0 + 0x20);
    s1 = a1 + *(s32 *)(a1 + 0x4);
    w = *(u32 *)s1;
    s2 = a2 + *(s32 *)(a2 + 0x4);

    if (BSWAP32(w) != 0x47534143) {
        return;
    }
    do {
        s0 = s1 + *(s32 *)(s1 + 0x4);
        if (*(u32 *)s0 & 0xF) {
            do {
                Gsc_DumpCommand((s32)s0, (s32)s2);
                s0 = (u8 *)Gsc_NextCommand((s32)s0);
            } while (*(u32 *)s0 & 0xF);
        }
        s1 = s1 + *(s32 *)(s1 + 0x8) + *(s32 *)(s1 + 0x4) + 0x10;
        w = *(u32 *)s1;
    } while (BSWAP32(w) == 0x47534143);
}
