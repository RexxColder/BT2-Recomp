#include "common.h"

extern void *memset(void *dst, s32 c, u32 n);
extern void *memcpy(void *dst, const void *src, u32 n);
extern u8 *D_003876A0;
extern u8 *D_00387A40;
extern u8 D_003764B0[];
extern f32 D_00386E74;
extern f32 D_00386E78;

u8 *func_0028BAA8(s32 arg0);
void Res_RelocateOffsets(u8 *arg0, u8 *arg1, u8 *arg2);
s32 func_002695E8(u8 *arg0, u8 *arg1);

s32 func_0025E2D0(s32 arg0) {
    u8 sp[0x20];
    u8 *s2;
    u8 *a;
    u8 *b;
    s32 s1;
    s32 count1;
    s32 count2;
    s32 i;

    s2 = D_003876A0 + 0x70;
    s1 = arg0 * 8;
    memcpy(sp, D_003764B0, 0x20);

    D_00387A40 = func_0028BAA8(229904);
    memset(D_00387A40, 0, 229904);

    count1 = *(s32 *)(sp + s1);
    if (count1 != 0) {
        *(s32 *)(D_00387A40 + 4) = count1;
        *(u8 **)(D_00387A40 + 0) = func_0028BAA8(count1 * 99712);
        memset(*(u8 **)(D_00387A40 + 0), 0, count1 * 99712);
    }

    count2 = *(s32 *)(sp + s1 + 4);
    if (count2 != 0) {
        *(s32 *)(D_00387A40 + 0xC) = count2;
        *(u8 **)(D_00387A40 + 8) = func_0028BAA8(count2 * 5408);
        memset(*(u8 **)(D_00387A40 + 8), 0, count2 * 5408);
    }

    /* first pointer table: entry i = block1 + i*99712, stored at word index 57441 + i */
    count1 = *(s32 *)(D_00387A40 + 4);
    if (count1 > 0) {
        for (i = 0; i < count1; i++) {
            *(u8 **)(D_00387A40 + 0x38184 + 4 * i) = *(u8 **)(D_00387A40 + 0) + i * 99712;
        }
    }

    /* second pointer table: entry i = block2 + i*5408, after the first table */
    count2 = *(s32 *)(D_00387A40 + 0xC);
    if (count2 > 0) {
        for (i = 0; i < count2; i++) {
            *(u8 **)(D_00387A40 + 0x38180 + 4 * count1 + 4 + 4 * i) =
                *(u8 **)(D_00387A40 + 8) + i * 5408;
        }
    }

    *(u32 *)(D_00387A40 + 0x38010) = 0;
    *(u32 *)(D_00387A40 + 0x38014) = 0;
    *(f32 *)(D_00387A40 + 0x38030) = D_00386E74;
    *(f32 *)(D_00387A40 + 0x38034) = -0.5f;
    *(f32 *)(D_00387A40 + 0x38038) = D_00386E78;
    *(f32 *)(D_00387A40 + 0x3803C) = 1.0f;

    a = *(u8 **)(s2 + 8);
    *(u8 **)(D_00387A40 + 0x38080) = a + ((*(u32 *)(a + 4) >> 2) << 2);
    Res_RelocateOffsets(D_00387A40 + 0x38080,
                        *(u8 **)(D_00387A40 + 0x38080),
                        *(u8 **)(D_00387A40 + 0x38080));

    a = *(u8 **)(s2 + 8);
    *(u8 **)(D_00387A40 + 0x38204) = a + ((*(u32 *)(a + 8) >> 2) << 2);

    a = *(u8 **)(s2 + 8);
    b = a + ((*(u32 *)(a + 0x10) >> 2) << 2);
    *(u8 **)(D_00387A40 + 0x38208) = b;
    return func_002695E8(b, D_00387A40);
}
