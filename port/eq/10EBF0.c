#include "common.h"

#define PTR(v) ((u8 *)(s32)(v))
#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))

void *memcpy(void *dst, const void *src, u32 n);
void func_00113D80(s32 arg0, s32 arg1);
s32 func_00113B00(s32 arg0, s32 arg1, s32 arg2);

extern u8 D_0036C748[] __attribute__((section(".data")));

/* 0x0010EBF0: copies a 0x40-byte table to the stack, takes the 10-byte record at index arg1 (8 bytes + one
 * halfword) into the object arg0 (+0xC and +0x14), calls func_00113D80, sets flag 0x100 in +0 and calls
 * func_00113B00 with arg3 and arg4. */
void func_0010EBF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 sp[0x70];
    u8 *p;
    u8 *rec;

    (void)arg2;
    p = PTR(arg0);
    memcpy(sp, D_0036C748, 0x50); /* asm 0x10EBF0: 0x40 loop + 0x10 tail at 0x10ECC0 = 8 digit records (was 0x40: level 6 read stack garbage, B17) */
    rec = sp + arg1 * 10;
    memcpy(p + 0xC, rec, 8);
    *(s16 *)(p + 0x14) = *(s16 *)(rec + 8);

    func_00113D80(arg0, 0);
    LD32(p, 0) = LD32(p, 0) | 0x100;
    func_00113B00(arg0, arg3, arg4);
}
