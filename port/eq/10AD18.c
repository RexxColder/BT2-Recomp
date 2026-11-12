#include "common.h"

void Res_RelocateOffsets(void *arg0, void *arg1, void *arg2);
void *func_00101A88(s32 arg0);
void *func_0028BAA8(s32 arg0);
void *memset(void *, s32, u32);
extern u8 *D_003876A0;
extern u8 *D_003876C8;

void func_0010AD18(void) {
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *a;
    s32 s3;
    s32 s2n;
    s32 sp[4];
    u8 *v0;
    s32 n;

    s0 = *(u8 **)(D_003876A0 + 0x24);
    D_003876C8 = (u8 *)func_0028BAA8(0x9200);
    memset(D_003876C8, 0, 0x9200);
    s2 = D_003876C8;
    s1 = s2 + 0x1370;
    if (*(s32 *)(D_003876A0 + 0xB8) == 6) {
        a = s0 + (*(u32 *)(s0 + 4) & ~3U);
        *(u8 **)(s1 + 0x14) = a;
        Res_RelocateOffsets(s2 + 0x1384, a, a);
        s3 = 0;
    } else {
        a = s0 + (*(u32 *)(s0 + 0x10) & ~3U);
        *(u8 **)(s2 + 0x1370) = a;
        Res_RelocateOffsets(s1, a, a);
        a = s0 + (*(u32 *)(s0 + 0x14) & ~3U);
        *(u8 **)(s1 + 4) = a;
        Res_RelocateOffsets(s2 + 0x1374, a, a);
        a = s0 + (*(u32 *)(s0 + 4) & ~3U);
        *(u8 **)(s1 + 8) = a;
        Res_RelocateOffsets(s2 + 0x1378, a, a);
        a = s0 + (*(u32 *)(s0 + 8) & ~3U);
        *(u8 **)(s1 + 0xC) = a;
        Res_RelocateOffsets(s2 + 0x137C, a, a);
        a = s0 + (*(u32 *)(s0 + 0xC) & ~3U);
        *(u8 **)(s1 + 0x10) = a;
        Res_RelocateOffsets(s2 + 0x1380, a, a);
        s3 = 0;
    }
    do {
        v0 = (u8 *)func_00101A88(s3);
        n = *(s32 *)v0;
        if (n >= 2) {
            s2n = 0;
            if (n > 0) {
                s0 = v0 + 0x58;
                a = *(u8 **)(v0 + 0x58);
                do {
                    s0 += 0x58;
                    s2n += 1;
                    sp[0] = (s32)a;
                    Res_RelocateOffsets(sp, a, a);
                    if (s2n < *(s32 *)v0) {
                        a = *(u8 **)s0;
                    }
                } while (s2n < *(s32 *)v0);
            }
        }
        s3 += 1;
    } while (s3 < 2);
}
