#include "common.h"

extern u8 *D_0042A574 __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 D_0042AEA0[], D_0042AEA8[], D_0042AEB8[], D_0042AEC8[], D_0042AED8[], D_0042AEE8[];
extern u8 D_0042AEF8[], D_0042AF08[], D_0042AF18[], D_0042AF28[];

void func_00277E70(u8 *arg0, s32 arg1, s64 arg2);
void func_0026EBC0(u8 *arg0, u8 *arg1, u8 *arg2);
void func_0026EFC8(u8 *arg0, u8 *arg1, s32 arg2);
void func_0026ED60(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, s32 arg4, f32 f0, f32 f1);
void func_00249778(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
void func_00249FB8(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_0026EC48(u8 *arg0, u8 *arg1, u8 *arg2);
void func_0026EC18(u8 *arg0, u8 *arg1, s32 arg2);
void func_00325830(u8 *arg0, u8 *arg1, s32 arg2);
void func_0024A8A0(u8 *arg0, s32 arg1, s32 arg2);
void func_0024A9D0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0024AB10(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, u8 *arg5);
void func_0024A598(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_0026EA58(u8 *arg0);
void func_0024C060(void);
s32 func_003F4298(s32 arg0);

#define W(o) (*(s32 *)(sp + (o)))
#define GW(o) (*(s32 *)(D_0042A574 + (o)))
#define HW(o) (*(s32 *)(D_003876A4 + (o)))

void func_003F5180(void) {
    u8 sp[0x120];
    u8 *s3;
    s32 i, v, q;

    func_00277E70(*(u8 **)(D_0042A574 + 0x6C), 0, 0x80);
    s3 = D_0042A574 + 0x1C;
    func_0026EBC0(s3, D_0042AEA0, sp);
    func_0026EFC8(s3, sp, 0x80);
    W(0x1C) = 0x80;
    W(0x18) = 0x200;
    W(0x14) = 0;
    W(0x10) = 0;
    func_0026EBC0(s3, D_0042AEA8, sp);
    func_0026ED60(s3, sp, sp + 0x10, D_0042A574 + 0x11C, 0, 1.0f, 0.0f);
    s3 = D_0042A574 + 0x44;
    func_0026EBC0(s3, D_0042AEB8, sp);
    func_00249778(s3, sp, D_0042A574 + 0x120, 1);
    func_0026EBC0(s3, D_0042AEC8, sp);
    func_00249FB8(s3, sp, 0, 0, GW(8), GW(0x118), 2);
    W(0x14) = 0x20;
    W(0x18) = 0x100;
    W(0x1C) = 0x40;
    W(0x10) = 0;
    func_0026EBC0(s3, D_0042AED8, sp);
    func_0026EC48(s3, sp, sp + 0x10);
    v = HW(0x64);
    q = (v < 0 ? v + 3 : v) >> 2;
    W(0x10) = (q % 2) << 8;
    W(0x18) = W(0x10) + 0x100;
    v = HW(0x64);
    q = v % 4;
    W(0x14) = q << 6;
    W(0x1C) = (q << 6) + 0x40;
    func_0026EBC0(s3, D_0042AEE8, sp);
    func_0026EC48(s3, sp, sp + 0x10);
    v = HW(0x64);
    func_0026EC18(s3, sp, (v < 0 ? v + 7 : v) >> 3);
    for (i = 0; i < 7; i++) {
        func_00325830(sp + 0x40, D_0042AEF8, 6 - i);
        func_0026EBC0(s3, sp + 0x40, sp + 0x60 + i * 8);
    }
    func_0024A8A0(sp + 0x30, HW(0x60) * 100, 7);
    sp[0x37] = 0xFF;
    func_0024AB10(s3, sp + 0x60, 0, 0, GW(0x12C), sp + 0x30);
    memset(sp + 0xA0, 0, 6);
    for (i = 0; i < 5; i++) {
        func_00325830(sp + 0xB0, D_0042AF08, 4 - i);
        func_0026EBC0(s3, sp + 0xB0, sp + 0xF0 + i * 8);
    }
    func_0024A9D0(sp + 0xA0, GW(0x138), 5, 1);
    sp[0xA5] = 0xFF;
    func_0024AB10(s3, sp + 0xF0, 0, 0, GW(0x12C), sp + 0xA0);
    func_0026EBC0(s3, D_0042AF18, sp);
    func_0024A598(s3, sp, 0, 0, GW(0x10), GW(0x134) + 0x52, 1);
    func_0026EBC0(s3, D_0042AF28, sp);
    v = func_003F4298(HW(0x64));
    func_0024A598(s3, sp, 0, 0, GW(0x14), v + 1, 1);
    for (i = 0; i < 2; i++) {
        func_0026EA58(D_0042A574 + i * 0x28 + 0x1C);
    }
    func_0024C060();
}
