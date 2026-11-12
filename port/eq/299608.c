#include "common.h"

extern s32 D_00344BD0[] __attribute__((section(".data")));
extern s32 D_00344BD4[] __attribute__((section(".data")));
extern u8 D_00387D98[] __attribute__((section(".data")));
extern u8 D_0038B058[] __attribute__((section(".data")));

void func_002987A0(s32 arg0);
void func_0026EB78(s32 arg0, s32 arg1);
void func_002711A0(void);
void func_0028B090(void);
void func_0028BDA0(void);
void func_00298A20(void);
void func_00299380(void);
void func_002711E8(void);
void func_00299110(void);
void func_0028B218(void);
s32 func_00100FC8(s32 arg0);
void *memset(void *arg0, s32 arg1, s32 arg2);

void func_00299608(s32 arg0) {
    s32 s1;
    s32 s2;
    s32 s7;
    s32 i;
    u8 *st;
    u8 *tbl;

    tbl = (u8 *)D_00344BD0;
    st = D_0038B058;
    s2 = 0;
    func_002987A0(arg0);
    s7 = 0;
    if (*(s32 *)tbl == 0) {
        goto block_3;
    }
block_2:
    ((void (*)(void))*(s32 *)(tbl + s7))();
    goto block_4;
block_3:
block_4:
    s1 = s2 + 1;
    func_00100FC8(1);
    st[0] = st[0] & 0xFE;

loop_5:
    func_002711A0();
    func_0028B090();
    func_0028BDA0();
    func_00298A20();
    func_00299380();
    func_002711E8();
    func_00299110();
    *(s32 *)(st + 4) = *(s32 *)(st + 4) + 1;
    if (func_00100FC8(0) == 0) {
        goto L299804;
    }
    if (st[0] & 1) {
        goto L2997F8;
    }
    if (s1 < 2 && *(s32 *)((u8 *)D_00344BD4 + s7) != 0) {
        goto L2997F8;
    }

    func_0026EB78(*(s32 *)(st + 8), (s32)D_00387D98);
    st[1] = 0x25;
    st[0] = st[0] | 2;
    for (i = 0; i < 7; i++) {
        *(s16 *)(st + 0x24 + 6 * i) = 3;
        *(s16 *)(st + 0x28 + 6 * i) = 1;
        *(s32 *)((u8 *)(*(s32 *)(st + 0x20)) + 0x38 * i + 0xA4) = 0x80;
    }

L2997F8:
    st[0] = st[0] | 1;
L299804:
    if ((st[0] & 1) == 0) {
        goto loop_5;
    }
    st[1] = (u8)(st[1] - 1);
    if (st[1] != 0xFF) {
        goto loop_5;
    }

    if (*(s32 *)(tbl + s7 + 8) != 0) {
        ((void (*)(void))*(s32 *)(tbl + s7 + 8))();
    }
    s2 = s1;
    if (s1 >= 2) {
        goto L29986C;
    }
    s7 = s1 << 2;
    if (*(s32 *)(tbl + s7) != 0) {
        goto block_2;
    }
L29986C:
    memset(tbl, 0, 0x10);
    func_0028B218();
}
