#include "m2c_macros.h"

extern u8 D_003876D8[] __attribute__((section(".data")));
extern u8 D_0036C800[] __attribute__((section(".data")));
void func_00113D80(void *arg0, s32 arg1);
void func_00113B00(void *arg0, s32 arg1, s32 arg2);

/* Copies a 10-byte record (selected by arg1 from a small stack table) into arg0+0xC, sets up the two
 * 0x60-byte copies of arg0 (to +0x120 and +0xC0), then moves the +0xC4/+0xC8 halfwords by the scaled
 * word of the table entry. arg4 is the float scale (f12). */
void Obj_ApplyRecord(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    u8 tmp[0x24];
    u8 *rec;
    s32 k;
    s32 w;
    s32 h;
    s32 q;
    s32 a0v;
    s32 a2v;

    *(u64 *)(tmp + 0x00) = *(u64 *)D_003876D8;
    *(u64 *)(tmp + 0x10) = *(u64 *)D_0036C800;
    *(u64 *)(tmp + 0x18) = *(u64 *)(D_0036C800 + 8);
    *(u32 *)(tmp + 0x20) = *(u32 *)(D_0036C800 + 0x10);

    rec = tmp + arg1 * 10 + 0x10;
    *(u64 *)(arg0 + 0xC) = *(u64 *)rec;
    *(u16 *)(arg0 + 0x14) = *(u16 *)(rec + 8);

    func_00113D80(arg0, 0);
    func_00113B00(arg0, arg2, arg3);

    for (k = 0; k < 0x60; k += 8) {
        *(u64 *)(arg0 + 0x120 + k) = *(u64 *)(arg0 + k);
    }
    *(u32 *)(arg0 + 0x120) |= 0x10000;

    for (k = 0; k < 0x60; k += 8) {
        *(u64 *)(arg0 + 0xC0 + k) = *(u64 *)(arg0 + k);
    }

    w = *(s32 *)(tmp + arg1 * 4);
    h = *(u16 *)(tmp + arg1 * 4);
    q = (s32)((f32)w * arg4);
    *(u32 *)(arg0 + 0xC0) |= 0x80;

    a2v = *(u16 *)(arg0 + 0xC4) + h;
    a0v = *(u16 *)(arg0 + 0xC8) + h;
    w = w - q;
    a2v = a2v - w;
    a0v = a0v - w;
    *(u16 *)(arg0 + 0xC8) = (u16)a0v;
    *(u16 *)(arg0 + 0xC4) = (u16)a2v;
}
