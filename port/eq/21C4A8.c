#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_0020FC38(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
f32 func_00210A98(s32 arg0);
f32 func_00240E20(s32 arg0);
u8 *BtlChar_GetPos(s32 arg0);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E30(s32 arg0, f32 farg0, f32 farg1);
extern f32 D_00385D2C;
extern f32 D_00385D30;
extern f32 D_00385D34;
extern f32 D_00385D38;
extern f32 D_00385D3C;

void func_0021C4A8(u8 *arg0) {
    f32 f20;
    f32 a;
    f32 b;
    u8 *p;

    BattleSide_SetChara((s32)arg0, 0x7A);
    func_002113C0((s32)arg0, 0, 2, 0);
    func_0020FC38((s32)arg0, 0x2E);
    if (func_00211310((s32)arg0, 0, 1) != 0) {
        a = func_00210A98((s32)arg0);
        f20 = (a < 0.0f) ? -a : a;
        b = func_00240E20((s32)arg0);
        if (!(f20 < b)) {
            p = BtlChar_GetPos((s32)arg0);
            func_00215E30((s32)arg0, *(f32 *)(p + 0xB4), D_00385D30);
            return;
        }
        func_00215068((s32)arg0, 1, 9, D_00385D2C, 0.0f);
        f20 = D_00385D34;
        p = BtlChar_GetPos((s32)arg0);
        if (*(f32 *)(p + 0xB0) < f20) {
            p = BtlChar_GetPos((s32)arg0);
            *(f32 *)(p + 0xB0) = f20;
        }
        f20 = D_00385D38;
        p = BtlChar_GetPos((s32)arg0);
        if (f20 < *(f32 *)(p + 0xB0)) {
            p = BtlChar_GetPos((s32)arg0);
            *(f32 *)(p + 0xB0) = f20;
        }
        *(s32 *)(arg0 + 0x8DC) = *(s32 *)(arg0 + 0x8DC) | 1;
        return;
    }
    p = BtlChar_GetPos((s32)arg0);
    func_00215E30((s32)arg0, *(f32 *)(p + 0xB4), D_00385D3C);
}
