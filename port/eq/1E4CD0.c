#include "common.h"

s64 EftVram_AddClut(u8 *arg0);
s64 EftVram_AddImage(u8 *arg0, s32 arg1, s32 arg2);
s64 EftVram_AddTex(u8 *arg0, s32 arg1, s32 arg2);
void *memset(void *, s32, u32);

void func_001E4CD0(u8 *arg0, u8 *arg1) {
    u8 sp[0x20];
    u8 *a1;
    u8 *s1;
    u8 *s2;
    u32 s3;
    u32 s4;
    u32 s6;
    u32 s7;
    u32 bit;
    s32 cnt;
    s32 temp_a0;
    s32 i;
    s64 img;
    s64 clut;

    s6 = 0;
    s7 = 0;
    memset(sp, 0, 0x20);
    s3 = 0;
    do {
        sp[s3] = 0xFF;
        s3 += 1;
    } while (s3 < 0x20);

    s3 = 0;
    cnt = *(s32 *)(arg0 + 0x1A0);
    if (cnt > 0) {
        a1 = arg0;
        do {
            temp_a0 = *(s32 *)(arg1 + 0x204);
            bit = (u32)1 << (a1[0x168] & 31);
            *(s32 *)(arg1 + 0x204) = (s32)((u32)temp_a0 | bit);
            if (((u32)temp_a0 & bit) == 0) {
                s6 |= bit;
            }
            if (a1[0x16A] != 0) {
                sp[a1[0x168]] = a1[0x169];
            }
            s3 += 1;
            a1 += 0x1B0;
        } while ((s32)s3 < *(s32 *)(arg0 + 0x1A0));
    }

    s3 = 0;
    if (cnt > 0) {
        a1 = arg0;
        s3 = (u32)cnt;
        do {
            if (a1[0x16A] == 0) {
                i = a1[0x168];
                if (sp[i] != 0xFF) {
                    s7 |= (u32)1 << (i & 31);
                }
            }
            s3 -= 1;
            a1 += 0x1B0;
        } while (s3 != 0);
        s3 = 0;
    }

    s2 = arg1;
    do {
        s4 = (u32)1 << (s3 & 31);
        s1 = sp + s3;
        if ((s6 & s4) != 0) {
            if (*s1 == 0xFF) {
                *(s64 *)s2 = EftVram_AddTex(s2, 1, 0);
            } else {
                img = EftVram_AddImage(s2, 1, 0);
                clut = EftVram_AddClut(arg1 + ((s3 + *s1) * 0x10));
                img = img | (clut << 37);
                *(s64 *)(arg1 + ((s3 + *s1) * 0x10)) = img;
                if ((s7 & s4) != 0) {
                    *(s64 *)s2 = EftVram_AddTex(s2, 1, 0);
                }
            }
        }
        s3 += 1;
        s2 += 0x10;
    } while (s3 < 0x20);
}
