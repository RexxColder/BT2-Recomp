#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))

s32 BtlObjXf_Update(s32 arg0);
s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
void func_001F9D78(s32 arg0, s32 arg1);
void func_001F9FB0(s32 arg0, s32 arg1);
s32 func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
s32 func_001FA2E0(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00212DD8(s32 arg0, s32 arg1);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(s32 arg0, s32 arg1, f32 farg0);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
s32 func_00218580(s32 arg0, f32 farg0, f32 farg1);

extern f32 D_003861BC;
extern f32 D_003861C0;
extern f32 D_003861C4;
extern f32 D_003861C8;

void func_002252A8(u8 *arg0) {
    s32 v;
    s32 flags;
    s32 p;

    p = (s32)arg0;
    v = BtlObjXf_Update(p);

    if ((v == 0x32) || (v == 0)) {
        func_001F9FB0(p, 1);
        if (BtlPad_Test4C(p, 2) != 0) {
            if ((u32)(func_00218580(p, 10.0f, 0.0f) - 1) < 2U) {
                flags = W(arg0, 0x8DC);
                func_001F9D78(p, ((flags & 1) != 0) ? 0x10F : 0x110);
                W(arg0, 0x8DC) = W(arg0, 0x8DC) ^ 1;
            }
        }
    } else if ((v == 0x10F) || (v == 0x110)) {
        if (func_001FA2E0(p) != 0) {
            func_00212DD8(p, 5);
        }
        flags = W(arg0, 0x8DC);
        if (flags & 2) {
            if (func_001FA0A0(p, ((flags & 1) != 0) ? 0x10F : 0x110, 0) != 0) {
                W(arg0, 0x8DC) = (W(arg0, 0x8DC) ^ 1) & ~2;
            }
        } else {
            if (func_001FA0A0(p, (func_00211310(p, 0, 2) != 0) ? 0x32 : 0, 0) != 0) {
                BtlAnim_SetBlend(p, D_003861BC);
            }
        }
        if (BtlPad_Test4C(p, 2) != 0) {
            if ((u32)(func_00218580(p, 10.0f, 0.0f) - 1) < 2U) {
                W(arg0, 0x8DC) = W(arg0, 0x8DC) | 2;
            }
        }
        func_002113C0(p, 3, 0x40, 1);
        func_002113C0(p, 3, 0x80, 1);
    }

    func_00215068(p, 5, 0xC, D_003861C4, D_003861C0);
    func_00215E88(p, 7, D_003861C0);
    func_00216208(p, 0.0f, D_003861C8);
    func_00216678(p);
    if (func_00211310(p, 0, 0x100) != 0) {
        func_002113C0(p, 0, 2, 1);
    }
}
