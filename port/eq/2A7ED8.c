#include "common.h"

s32 Gsc_CountOption(s32 arg0);
s32 Gsc_FindOptionN(s32 arg0, s32 arg1);
s32 Gsc_GetInt(void);
s32 func_002A0010(s32 arg0);
extern u8 D_003B26B0[] __attribute__((section(".data")));

s32 func_002A7ED8(s32 arg0) {
    u8 *base;
    u8 *s0;
    u8 *s2;
    u8 *s3;
    u8 *v1;
    s32 s1;
    s32 s4;
    s32 s5;
    s32 s6;

    base = D_003B26B0;
    if (arg0 == 0) {
        s0 = base + 0x38;
        func_002A0010(0x65);
        s3 = base + 0x58;
        *(s32 *)(s0 + 0x0) = Gsc_GetInt();
        s6 = 0;
        *(s32 *)(s0 + 0x4) = Gsc_GetInt();
        *(s32 *)(s0 + 0x8) = Gsc_GetInt();
        *(s32 *)(s0 + 0xC) = Gsc_GetInt();
        *(s32 *)(s0 + 0x10) = Gsc_GetInt();
        func_002A0010(0x69);
        *(s32 *)(s0 + 0x14) = Gsc_GetInt();
        *(s32 *)(s0 + 0x18) = Gsc_GetInt();
        *(s32 *)(s0 + 0x1C) = Gsc_GetInt();
        Gsc_CountOption(0x63);
        Gsc_CountOption(0x63);
        while (Gsc_FindOptionN(0x63, s6) != 0) {
            s5 = 0;
            *(s32 *)(s3 + 0x0) = Gsc_GetInt();
            s4 = 0;
            s2 = s3 + 0x14;
            *(s32 *)(s3 + 0x4) = Gsc_GetInt();
            *(u8 *)(s3 + 0x8) = (u8)Gsc_GetInt();
            do {
                s1 = 6;
                *(s32 *)s2 = Gsc_GetInt();
                v1 = s3 + (s4 * 4);
                s0 = v1 + 0x20;
                do {
                    s1 -= 1;
                    *(s32 *)s0 = Gsc_GetInt();
                    s0 += 4;
                } while (s1 >= 0);
                s5 += 1;
                s4 += 7;
                s2 += 4;
            } while (s5 < 3);
            s3 += 0x78;
            s6 += 1;
        }
    }
    return 1;
}
