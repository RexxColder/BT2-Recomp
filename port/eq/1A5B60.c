#include "common.h"

void *memset(void *arg0, s32 arg1, s32 arg2);
void func_00129C28(s32 arg0, s32 arg1);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
s32 EftPtcl3_Create(s32 arg0);
void EftPtcl3_SetTexture(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void EftPtcl3_SetFront(s32 arg0);
void EftPtcl3_SetType(s32 arg0, s32 arg1);

s32 func_001A5B60(u8 *arg0) {
    u8 sp[0xB0];
    s32 i;
    s32 count;
    s32 handle;
    s32 a0v;
    s32 a1v;
    s32 a2v;
    s32 a3v;
    s32 v1v;
    f32 f0;
    f32 f1;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *p;
    s32 k;

    if (*(s32 *)(arg0 + 0x10) == 0) {
        return 0;
    }
    if (*(s32 *)(arg0 + 0x14) == 0) {
        return 0;
    }
    p = *(u8 **)(arg0 + 0xC);
    if (p == NULL) {
        return 0;
    }
    if (*(s32 *)(p + 0x100) == 0) {
        return 0;
    }
    count = *(s32 *)(arg0 + 0x68);
    if (count <= 0) {
        return 1;
    }

    *(s32 *)(sp + 0xA4) = (s32)(arg0 + 0x30);
    *(s32 *)(sp + 0xA8) = (s32)(arg0 + 0x40);
    *(s32 *)(sp + 0xA0) = (s32)(arg0 + 0xC);

    i = 0;
    do {
        s1 = arg0 + 4 * i;
        s2 = arg0 + 0x6F + i;
        s3 = arg0 + 0x5C + 4 * i;
        s4 = arg0 + 0x6C + i;

        f1 = *(f32 *)s3;
        f0 = *(f32 *)(s1 + 0x50);
        *(f32 *)(sp + 0x50) = f1;
        *(f32 *)(sp + 0x54) = f0;
        memset(sp + 0x60, 0, 0x10);
        memset(sp + 0x70, 0, 0x10);

        a3v = *(u8 *)s2;
        a0v = *(s32 *)(arg0 + 0x10) + i * 0x164;
        a1v = *(s32 *)(arg0 + 0xC);
        a2v = *(s32 *)(arg0 + 0x80);
        v1v = *(s32 *)(arg0 + 0x14) + 0x50 * i;
        *(s32 *)(sp + 0x84) = a1v;
        *(s32 *)(sp + 0x88) = a0v;
        *(s32 *)(sp + 0x8C) = v1v;
        *(s32 *)(sp + 0x90) = a2v;
        *(s32 *)(sp + 0x80) = a3v;

        for (k = 0; k < 8; k++) {
            *(s64 *)(sp + 8 * k) = *(s64 *)(sp + 0x50 + 8 * k);
        }
        *(s64 *)(sp + 0x40) = *(s64 *)(sp + 0x90);
        *(s64 *)(sp + 0x48) = *(s64 *)(sp + 0x98);

        func_00129C28((s32)(sp + 0x10), *(s32 *)(sp + 0xA4));
        func_00129C28((s32)(sp + 0x20), *(s32 *)(sp + 0xA8));
        if (*s4 != 0) {
            func_00129BD0((s32)(sp + 0x20), (s32)(sp + 0x20), -1.0f);
        }

        handle = EftPtcl3_Create((s32)sp);
        *(s32 *)s1 = handle;
        if ((*(u16 *)(arg0 + 0x88) & 0x8) != 0) {
            EftPtcl3_SetTexture(handle, *(s32 *)(arg0 + 0xC), *s2, *(s32 *)(arg0 + 0x84));
        }
        if ((*(u16 *)(arg0 + 0x88) & 0x10) != 0) {
            EftPtcl3_SetFront(handle);
        }
        EftPtcl3_SetType(handle, 2);

        i++;
    } while (i < *(s32 *)(arg0 + 0x68));
    return 1;
}
