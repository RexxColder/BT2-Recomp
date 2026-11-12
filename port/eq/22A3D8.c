#include "common.h"

s32 func_00211310(u8 *a0, s32 a1, s32 a2);
f32 func_00240D50(u8 *a0, s32 a1);
f32 func_00207E90(u8 *a0);
f32 func_00240DD0(u8 *a0, s32 a1);
f32 func_001FA318(u8 *a0);
void func_001F9FB0(u8 *a0, s32 a1);
void func_00215068(u8 *a0, s32 a1, s32 a2, f32 farg0, f32 farg1);
void func_00215E88(u8 *a0, s32 a1, f32 farg0);
void func_00216208(u8 *a0, f32 farg0, f32 farg1);
void func_00216890(u8 *a0, f32 farg0, f32 farg1);
s32 func_002113C0(u8 *a0, s32 a1, s32 a2, s32 a3);
void func_0020D7E8(u8 *a0, f32 farg0, f32 farg1);
u8 *BtlMember_GetActiveGauge(u8 *a0);
s32 func_00206958(u8 *a0, s64 a1);
extern f32 D_003864A8;
extern f32 D_003864AC;
extern f32 D_003864B0;

s32 func_0022A3D8(u8 *arg0) {
    s32 v0;
    s32 x;
    f32 A;
    f32 B;
    f32 C;
    f32 D;
    f32 E;
    f32 f1;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    u8 *g;

    v0 = func_00211310(arg0, 0, 0x100);
    x = (v0 != 0);
    A = func_00240D50(arg0, x);
    B = func_00207E90(arg0);
    f20 = A;
    f23 = A * B;
    C = func_00240D50(arg0, 0x10);
    f21 = C;
    D = func_00240DD0(arg0, 0);
    f20 = D;
    E = func_001FA318(arg0);
    f22 = D_003864A8;
    f1 = 1.0f - E;
    f20 = f20 * 0.5f;
    f23 = f23 * f1;
    f21 = f21 * f1;
    func_001F9FB0(arg0, 0);
    func_00215068(arg0, 0, 0xC, D_003864AC, f22);
    func_00215E88(arg0, 0, f22);
    func_00216208(arg0, f23, D_003864B0);
    func_00216890(arg0, -f21, f20);
    func_002113C0(arg0, 9, 0x80000, 1);
    func_0020D7E8(arg0, 20.0f, 50.0f);
    func_002113C0(arg0, 1, 0x800000, 1);
    g = BtlMember_GetActiveGauge(arg0);
    if (*(u8 *)(g + 0x29) != 0) {
        func_002113C0(arg0, 6, 8, 1);
    }
    return func_00206958(arg0, (s64)0x8000 << 28);
}
