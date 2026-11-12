#include "common.h"

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define F(p, o) (*(f32 *)((u8 *)(p) + (o)))

void *BtlChar_GetPos(void *);
s32 BtlObjXf_Update(void *arg0);
s32 BtlPad_Test4C(void *, s32);
f32 BtlUtil_WrapAngle(f32);
void BtlAnim_SetBlend(f32, void *);
void BtlChar_Vibrate(f32, f32, void *);
void func_001F9D78(void *, s32);
void func_001F9FB0(void *, s32);
void func_001FA110(void *, s32);
s32 func_001FA1D0(f32, void *);
void func_00203310(void *, s32, s32);
s32 func_00211310(void *, s32, s32);
void func_002113C0(void *, s32, s32, s32);
void func_00212DD8(void *, s32);
void func_00215550(f32, f32, f32, f32, f32, f32, f32, void *, s32);
void func_00215E88(f32, void *, s32);
void func_00216208(f32, f32, void *);
void func_00216678(void *);
extern f32 D_00386834;
extern f32 D_00386838;
extern f32 D_0038683C;
extern f32 D_00386840;
extern f32 D_00386844;
extern f32 D_00386848;
extern f32 D_0038684C;

void func_00230768(void *arg0) {
    s32 v;
    f32 f20;
    f32 f21;
    void *s0;
    void *tmp;
    f32 wa;

    v = BtlObjXf_Update(arg0);
    if (v == 0x18C) {
        func_001F9FB0(arg0, 0);
    } else if (v == 0x18D) {
        func_001F9FB0(arg0, 0);
        if (func_001FA1D0(0.5f, arg0) != 0) {
            func_00203310(arg0, 0xFA0, 0);
            func_00212DD8(arg0, 0x1A);
        }
        func_002113C0(arg0, 6, 4, 1);
        func_002113C0(arg0, 6, 8, 1);
    } else if (v == 0x18A || v == 0x18B) {
        func_001FA110(arg0, 0);
        func_002113C0(arg0, 0xF, 0x10, 1);
        if (BtlPad_Test4C(arg0, 0x1E) != 0) {
            W(arg0, 0xA3C) += 1;
        } else if (BtlPad_Test4C(arg0, 0x1F) != 0) {
            W(arg0, 0xA3C) += 1;
        } else {
            W(arg0, 0xA3C) += (W(arg0, 0x8CC) % 7 == 0);
        }
        if (W(arg0, 0x8DC) & 1) {
            W(arg0, 0xA3C) += (W(arg0, 0x8CC) % 20 == 0);
        }
        if (W(arg0, 0xA3C) >= 0x63) {
            W(arg0, 0xA3C) = 0x62;
        }
        if (func_00211310(arg0, 7, 0x8000) != 0) {
            BtlAnim_SetBlend(D_00386834, arg0);
            func_001F9D78(arg0, 0x18C);
            W(arg0, 0xA40) = 0x1E;
            W(arg0, 0xA3C) += 1;
        }
        if (func_00211310(arg0, 7, 0x10000) != 0) {
            BtlAnim_SetBlend(D_00386838, arg0);
            func_001F9D78(arg0, 0x18D);
        }
    }

    f21 = D_0038683C;
    f20 = D_00386840;
    func_00215550(f21, 0.0f, 0.0f, 0.0f, 0.0f, D_00386844, f20, arg0, 1);
    s0 = BtlChar_GetPos(arg0);
    tmp = BtlChar_GetPos(arg0);
    wa = F(tmp, 0xB4) + 0.5f;
    F(s0, 0xB4) = BtlUtil_WrapAngle(wa);
    func_00215E88(f20, arg0, 3);
    func_00216208(f21, D_00386848, arg0);
    func_00216678(arg0);
    func_002113C0(arg0, 0xD, 8, 1);
    func_002113C0(arg0, 0xD, 1, 1);
    func_002113C0(arg0, 0xD, 0x10, 1);
    func_002113C0(arg0, 9, 0x200000, 1);
    BtlChar_Vibrate(1.0f, D_0038684C, arg0);
    func_002113C0(arg0, 9, 0x1000, 1);
    func_002113C0(arg0, 3, 0xF, 1);
    func_002113C0(arg0, 0xF, 0x100000, 1);
}
