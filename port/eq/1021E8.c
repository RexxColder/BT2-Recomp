#include "common.h"

void Font_Init(s32 arg0);
u8 *func_00100CB8(s32 arg0);
void func_00102180(void);
void func_0026E7F0(s32 arg0, s32 arg1, s32 arg2);
void func_00284B18(void);
u8 *func_0028BAA8(s32 arg0);
void memset(void *arg0, s32 arg1, s32 arg2);
extern u8 *D_003876A0;
extern u8 *D_003876A4;

void func_001021E8(void) {
    u8 *p;
    u8 *v1;
    s32 i;
    s32 off;

    p = func_0028BAA8(0x4E8);
    D_003876A0 = p;
    memset(p, 0, 0x4E8);
    p = func_0028BAA8(0x4D8);
    D_003876A4 = p;
    memset(p, 0, 0x4D8);
    *(s32 *)(D_003876A4 + 4) = 0x544;
    p = func_0028BAA8(0x6800);
    *(u8 **)(D_003876A4 + 0x14) = p;
    p = func_00100CB8(*(s32 *)(D_003876A4 + 4) + 0x16);
    *(u8 **)(D_003876A4 + 0x14) = p;
    func_00102180();
    Font_Init(1);
    func_00284B18();
    p = func_00100CB8(*(s32 *)(D_003876A4 + 4));
    *(u8 **)(D_003876A4 + 8) = p;
    p = func_0028BAA8(0x28);
    *(u8 **)(D_003876A4 + 0xC) = p;
    v1 = *(u8 **)(D_003876A4 + 8);
    func_0026E7F0((s32)*(u8 **)(D_003876A4 + 0xC),
                  (s32)(v1 + ((*(u32 *)(v1 + 8) >> 2) * 4)), 0);
    *(s32 *)(D_003876A4 + 0x1C) = 1;
    *(s32 *)(D_003876A4 + 0x18) = *(s32 *)(D_003876A4 + 0x18) | 0x40;
    i = 0;
    do {
        off = i * 4;
        i += 1;
        *(s32 *)(D_003876A4 + 0x390 + off) = 0;
        *(s32 *)(D_003876A4 + 0x3A4 + off) = 1;
    } while (i < 5);
    p = func_0028BAA8(0xB28);
    *(u8 **)(D_003876A4 + 0x4D0) = p;
    p = func_0028BAA8(0x90C);
    *(u8 **)(D_003876A4 + 0x4D4) = p;
}
