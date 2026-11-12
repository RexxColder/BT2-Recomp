#include "common.h"

#define PTR(v) ((u8 *)(s32)(v))
#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))

s32 func_002BC170(s32 arg0);
void func_002BB9C8(s32 arg0);
s32 func_002BBAA8(s32 arg0, void *arg1, void *arg2, void *arg3);
s32 func_00304760(s32 arg0, s32 arg1, s32 arg2);
s32 func_002BBB10(s32 arg0, s32 arg1, s32 arg2);
void func_002C33D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 Rand_Range();

extern u8 D_00379E50[] __attribute__((section(".data")));
extern u8 D_00379E80[] __attribute__((section(".data")));
extern u8 D_00379EA8[] __attribute__((section(".data")));

/* 0x002BBEA8: records an entry in the 32-byte slot arg1 of the table at arg0 (+0x284). Returns the result of
 * func_002BBB10 on success (after func_002C33D8 with the table's +0x3C value). Each failed check reports
 * through Rand_Range and returns 0. */
s32 func_002BBEA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *p;
    u8 *e;
    s32 buf[3];
    s32 s2;
    s32 s6;
    s32 v;
    s32 s1;

    p = PTR(arg0);
    s2 = func_002BC170(arg1);
    if (s2 == 0) {
        return 0;
    }

    func_002BB9C8(arg1);
    e = p + (arg1 << 5) + 0x284;
    s6 = LD32(p, 0x3C);
    LD32(e, 0x8) = s2;
    LD32(e, 0x4) = arg1;
    LD32(e, 0xC) = arg2;
    LD32(e, 0x10) = arg3;
    LD32(e, 0x18) = arg4;

    v = func_002BBAA8(arg1, buf, buf + 1, buf + 2);
    if (arg3 < v) {
        Rand_Range(D_00379E50);
        return 0;
    }

    s2 = func_00304760(arg2 + buf[0], buf[1], buf[2]);
    if (s2 == 0) {
        Rand_Range(D_00379E80, arg2);
        return 0;
    }
    LD32(e, 0x14) = s2;

    s1 = func_002BBB10(arg1, arg2, buf[0]);
    if (s1 != 0) {
        LD32(e, 0x0) = 1;
        LD32(e, 0x1C) = s1;
        func_002C33D8(s6, arg4 + 0xC0, s2, 0, 0);
        return s1;
    }

    Rand_Range(D_00379EA8, arg4 + 0xC0);
    return 0;
}
