#include "common.h"

void Gsc_DumpCommand(s32 arg0, s32 arg1);
s32 Gsc_NextCommand(s32 arg0);

#define BSWAP32(w) ((((w) >> 24) & 0xFF) | (((w) << 24) & 0xFF000000u) | (((w) & 0xFF00) << 8) | (((w) >> 8) & 0xFF00))

void Gsc_DumpCommandsById(u8 *arg0, s32 arg1) {
    u8 *a2;
    u8 *a3;
    u8 *s0;
    u8 *s1;
    u8 *s3;
    s32 t;
    s32 v0;

    a2 = *(u8 **)(arg0 + 0x1C);
    a3 = *(u8 **)(arg0 + 0x20);
    s1 = a2 + *(s32 *)(a2 + 4);
    s3 = a3 + *(s32 *)(a3 + 4);
    if (BSWAP32(*(u32 *)s1) == 0x47534143) {
        do {
            s0 = s1 + *(s32 *)(s1 + 4);
            t = *(s32 *)s0;
            if (t & 0xF) {
                v0 = t & 0xF;
                do {
                    if (v0 == 1 && *(u16 *)(s0 + 2) == arg1) {
                        Gsc_DumpCommand((s32)s0, (s32)s3);
                    }
                    s0 = (u8 *)Gsc_NextCommand((s32)s0);
                    v0 = *(s32 *)s0 & 0xF;
                } while (v0 != 0);
            }
            s1 = s1 + *(s32 *)(s1 + 8) + *(s32 *)(s1 + 4) + 0x10;
        } while (BSWAP32(*(u32 *)s1) == 0x47534143);
    }
}
