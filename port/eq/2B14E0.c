#include "common.h"

f32 func_00273000(void);
f32 func_002AD640(void);
s32 func_002ADFC8(s32 arg0);
u8 *func_002B1DD0(s32 arg0);
extern f32 D_0038760C;
extern f32 D_00387610;
extern f32 D_00387614;
extern f32 D_00387618;
extern f32 D_0038761C;
extern f32 D_00387620;
extern f32 D_00387624;
extern f32 D_00387628;

#define FF(p, o) (*(f32 *)((u8 *)(p) + (o)))

void func_002B14E0(u8 *arg0) {
    f32 f20;
    f32 f0;
    f32 f3;
    f32 f4;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f3;
    f32 var_f3_2;
    s32 cond;
    u8 *v;

    f20 = D_0038760C;
    if (*(s32 *)(arg0 + 0x10) == 0) {
        var_f3 = FF(arg0, 0xD0);
        f4 = -f20;
        if (f20 < var_f3) {
            var_f3 = var_f3 - D_00387610;
            FF(arg0, 0xD0) = var_f3;
            FF(arg0, 0x120) = FF(arg0, 0x120) - D_00387610;
            FF(arg0, 0x50) = FF(arg0, 0x50) - D_00387610;
        }
        if (var_f3 < f4) {
            FF(arg0, 0xD0) = var_f3 + D_00387614;
            FF(arg0, 0x120) = FF(arg0, 0x120) + D_00387614;
            FF(arg0, 0x50) = FF(arg0, 0x50) + D_00387614;
        }
        var_f3_2 = FF(arg0, 0xD8);
        if (f20 < var_f3_2) {
            var_f3_2 = var_f3_2 - D_00387618;
            FF(arg0, 0xD8) = var_f3_2;
            FF(arg0, 0x128) = FF(arg0, 0x128) - D_00387618;
            FF(arg0, 0x58) = FF(arg0, 0x58) - D_00387618;
        }
        cond = var_f3_2 < f4;
    } else {
        v = func_002B1DD0(0);
        f3 = FF(arg0, 0xD0);
        var_f0 = f3 - FF(v, 0xD0);
        f4 = -f20;
        if (f20 < var_f0) {
            f3 = f3 - D_0038761C;
            FF(arg0, 0xD0) = f3;
            FF(arg0, 0x120) = FF(arg0, 0x120) - D_0038761C;
            FF(arg0, 0x50) = FF(arg0, 0x50) - D_0038761C;
            var_f0 = f3 - FF(v, 0xD0);
        }
        if (var_f0 < f4) {
            FF(arg0, 0xD0) = f3 + D_00387620;
            FF(arg0, 0x120) = FF(arg0, 0x120) + D_00387620;
            FF(arg0, 0x50) = FF(arg0, 0x50) + D_00387620;
        }
        f3 = FF(arg0, 0xD8);
        var_f3_2 = f3;
        var_f0_2 = var_f3_2 - FF(v, 0xD8);
        if (f20 < var_f0_2) {
            var_f3_2 = var_f3_2 - D_00387624;
            FF(arg0, 0xD8) = var_f3_2;
            FF(arg0, 0x128) = FF(arg0, 0x128) - D_00387624;
            FF(arg0, 0x58) = FF(arg0, 0x58) - D_00387624;
            var_f0_2 = var_f3_2 - FF(v, 0xD8);
        }
        cond = var_f0_2 < f4;
    }
    if (cond) {
        FF(arg0, 0xD8) = var_f3_2 + D_00387628;
        FF(arg0, 0x128) = FF(arg0, 0x128) + D_00387628;
        FF(arg0, 0x58) = FF(arg0, 0x58) + D_00387628;
    }
    if (func_002ADFC8((s32)arg0) != 7) {
        f0 = func_00273000();
        if (FF(arg0, 0xD4) < f0) {
            FF(arg0, 0xD4) = f0;
        }
        f0 = func_002AD640();
        if (f0 < FF(arg0, 0xD4)) {
            FF(arg0, 0xD4) = f0;
        }
    }
}
