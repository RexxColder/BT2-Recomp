#include "m2c_macros.h"

extern u8 D_00378300[] __attribute__((section(".data")));
extern u8 D_00378328[] __attribute__((section(".data")));
void *memset(void *dst, s32 c, u32 n);
s32 Rand_Range(void *arg0);
void func_002C1598(void *a0, s32 a1, void *a2);
s32 func_002B49F8(u8 *arg0);
void func_002B5B90(void *a0, s32 a1, void *a2, s32 a3, s32 t0, s32 t1, s32 t2);
s32 func_002B4A48(void *a0);

/* Clears arg2 (0x2C bytes); when arg0 and arg1 > 0 a 0x2C-byte record is built in a local: a state record from
 * func_002C1598 (kind 0x101 takes the func_002B49F8 path), then func_002B5B90 and func_002B4A48 fill it and it is
 * copied out. Otherwise a random entry is returned. */
s32 BtlRand_PickEntry(void *arg0, s32 arg1, u8 *arg2) {
    u8 fr[0x70];   /* tamano de locales del original (antes 0x60) */
    u8 *tmp;
    u8 *st;
    s32 r;

    tmp = fr;
    st = fr + 0x30;
    memset(fr, 0, 0x2C);
    memset(arg2, 0, 0x2C);
    if (arg0 == NULL || arg2 == NULL) {
        return Rand_Range(D_00378300);
    }
    if (arg1 <= 0) {
        return Rand_Range(D_00378328);
    }

    func_002C1598(arg0, arg1, st);
    if (*(u16 *)(st + 0x0) != 0x101) {
        *(u64 *)(arg2 + 0x00) = *(u64 *)(tmp + 0x00);
        *(u64 *)(arg2 + 0x08) = *(u64 *)(tmp + 0x08);
        *(u64 *)(arg2 + 0x10) = *(u64 *)(tmp + 0x10);
        *(u64 *)(arg2 + 0x18) = *(u64 *)(tmp + 0x18);
        *(u64 *)(arg2 + 0x20) = *(u64 *)(tmp + 0x20);
        *(s32 *)(arg2 + 0x28) = *(s32 *)(tmp + 0x28);
        *(s32 *)arg2 = 0;
        return *(s32 *)(tmp + 0x20);
    }

    r = func_002B49F8(st);
    *(s32 *)(tmp + 0xC) = *(s32 *)(st + 0x18);
    *(s32 *)(tmp + 0x4) = r;
    *(s32 *)(tmp + 0x8) = *(s32 *)(st + 0x14);
    *(s32 *)(tmp + 0x10) = *(s32 *)(st + 0x20);
    *(s32 *)(tmp + 0x24) = *(s32 *)(st + 0x2C);
    *(s32 *)(tmp + 0x28) = (s8)st[0x28];
    func_002B5B90(arg0, arg1, tmp, *(s32 *)(st + 0x20), *(s32 *)(st + 0x2C), (s8)st[0x28],
                  *(s32 *)(st + 0x14));
    *(s32 *)tmp = func_002B4A48(tmp);

    *(u64 *)(arg2 + 0x00) = *(u64 *)(tmp + 0x00);
    *(u64 *)(arg2 + 0x08) = *(u64 *)(tmp + 0x08);
    *(u64 *)(arg2 + 0x10) = *(u64 *)(tmp + 0x10);
    *(u64 *)(arg2 + 0x18) = *(u64 *)(tmp + 0x18);
    *(u64 *)(arg2 + 0x20) = *(u64 *)(tmp + 0x20);
    *(s32 *)(arg2 + 0x28) = *(s32 *)(tmp + 0x28);
    return *(s32 *)(tmp + 0x20);
}
