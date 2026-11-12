#include "common.h"

extern u8 *func_0028BAA8(s32 size);
extern s32 func_00100D58(s32 arg0, s32 arg1, s32 arg2);
extern u8 *func_002B24C8(u8 *arg0, s32 arg1, s32 arg2);
extern void func_0029BB88(u8 *arg0, u8 *arg1);
extern s32 func_0024B468(s32 arg0);
extern void func_0028A0B8(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 t0);
extern s32 McCard_Checksum(u8 *arg0, s32 arg1, s32 arg2);
extern u8 *D_00387A00;
extern u8 *D_003876A4;
extern u8 *D_00387F2C;
extern u8 D_003B2600[];
extern u8 D_00387A08[];
extern u8 D_00376380[];

s32 func_00258418(void) {
    u8 *tbl;
    s32 i;
    u8 *ent;
    u8 *p;
    s32 h;

    D_00387A00 = func_0028BAA8(0x444);
    __builtin_memset(D_00387A00, 0, 0x444);
    if (*(s32 *)D_00387A00 == 0) {
        func_00100D58(*(s32 *)(D_003876A4 + 4) + 0x12, 0, 1);
        do {
            h = func_00100D58(0, 0, 0);
            *(s32 *)D_00387A00 = h;
        } while (h == 0);
    }
    *(u8 **)(D_00387A00 + 4) = func_002B24C8(*(u8 **)D_00387A00, 0, 0);
    p = *(u8 **)(D_00387A00 + 4);
    *(u8 **)(D_00387A00 + 8) = p + (*(u32 *)(p + 8) & ~3U);
    func_0029BB88(*(u8 **)(D_00387A00 + 4) + (*(u32 *)(*(u8 **)(D_00387A00 + 4) + 4) & ~3U),
                  *(u8 **)(D_00387A00 + 8));
    *(s32 *)(D_00387A00 + 0x14) = 8;
    *(s32 *)(D_00387A00 + 0x1C) = -1;
    *(s32 *)(D_00387F2C + 0xD8) = *(s32 *)(D_003B2600);
    *(s32 *)(D_00387F2C + 0xDC) = *(s32 *)(D_003B2600 + 4);
    __builtin_memcpy(D_00387F2C + 0xE0, D_003B2600 + 8, 0x4C);

    tbl = D_003B2600;
    i = *(s32 *)(D_003876A4 + 0x34);
    if (i < *(s32 *)(tbl + 4)) {
        do {
            ent = D_00387F2C + func_0024B468(*(s32 *)(D_003876A4 + 0x30)) + i;
            if (*(s8 *)(ent + 0xC) < *(s32 *)(D_003876A4 + 0x38) + 1) {
                *(u8 *)(D_00387F2C + func_0024B468(*(s32 *)(D_003876A4 + 0x30)) + i + 0xC) =
                    *(u8 *)(D_003876A4 + 0x38) + 1;
            }
            i++;
        } while (i < *(s32 *)(tbl + 4));
    }
    *(s32 *)(D_003876A4 + 0x34) = *(s32 *)(D_003B2600 + 4);

    p = *(u8 **)(D_00387A00 + 4);
    *(u8 **)(D_00387A00 + 0x24) = p + (*(u32 *)(p + 0xC) & ~3U);
    *(s32 *)(D_00387A00 + 0x30) = 0xD74E;
    __builtin_memcpy(D_00387A00 + 0x33C, D_00376380, 0x2D);
    *(s32 *)(D_00387A00 + 0x440) = 0x18;
    func_0028A0B8(D_00387A00 + 0x24, D_00387A08, -1, -1, 1);
    return McCard_Checksum(D_00387F2C, 0x4000, 1);
}
