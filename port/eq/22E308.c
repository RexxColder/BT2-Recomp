#include "common.h"

#define W32(o, off) (*(s32 *)((u8 *)(o) + (off)))
#define F32AT(p, off) (*(f32 *)((u8 *)(p) + (off)))

extern f32 D_003866F4;
extern f32 D_003866F8;
extern f32 D_003866FC;
extern f32 D_00386700;
extern f32 D_00386704;
extern f32 D_00386708;
extern f32 D_0038670C;
extern f32 D_00386710;
extern f32 D_00386714;

s32 BtlObjXf_Update(void *obj);
s32 func_001F9FB0(void *obj, s32 a1);
void func_002113C0(void *obj, s32 a1, s32 a2, s32 a3);
void func_00215068(f32 fa, void *obj, s32 a1, s32 a2, f32 fb);
void func_00215E88(f32 fa, void *obj, s32 a1);
void func_00216208(f32 fa, void *obj, f32 fb);
void func_00216678(void *obj);
void func_0020D7E8(f32 fa, void *obj, f32 fb);
f32 func_00240D50(void *obj, s32 a1);
s32 func_00218128(void *obj, s32 a1);
f32 func_002173E8(void *obj, f32 fa, f32 fb, f32 fc);
void func_00206958(void *obj, s64 a1);
s32 func_002174B8(void *obj);
s32 func_00211310(void *obj, s32 a1, s32 a2);
void BtlOpp_GetTargetPos(void *obj, void *out);
void func_00210868(void *obj, void *out);
void BtlOpp_GetDelta(void *obj, void *out);
void func_002109C8(void *obj, void *out);
s32 BtlChar_GetPos(void *obj);
void func_00312638(s32 a0, s32 a1, void *a2);
f32 atan2f(f32 y, f32 x);
void BtlUtil_WrapAngle(f32 a);

void func_0022E308(void *obj) {
    u8 sp[0x30];
    s32 a1;
    s32 p;
    f32 f20;
    f32 f21;

    if ((W32(obj, 0x8DC) & 2) == 0) {
        if (BtlObjXf_Update(obj) == 0x10C && func_001F9FB0(obj, 0) != 0) {
            func_002113C0(obj, 9, 0x4000, 1);
            W32(obj, 0x8DC) = W32(obj, 0x8DC) | 2;
        }
        f20 = D_003866F4;
        func_00215068(D_003866F8, obj, 1, 0xC, f20);
        func_00215E88(f20, obj, 7);
        func_00216208(0.0f, obj, D_003866FC);
    } else {
        a1 = W32(obj, 0x8C0) - 1;
        W32(obj, 0x8C0) = a1;
        if (a1 >= 2) {
            f20 = func_00240D50(obj, 0x12);
            if (func_00218128(obj, 3) != 0) {
                f20 = f20 * 1.5f;
            }
            f21 = func_002173E8(obj, f20, D_00386700, 7.0f);
        } else {
            f21 = 0.0f;
            if (a1 == 1) {
                func_00206958(obj, 0x4000);
            }
        }
        if (func_002174B8(obj) == 0x64) {
            f21 = D_00386704;
        }
        if (W32(obj, 0x8C0) == 0 && func_00211310(obj, 0, 1) != 0 && (W32(obj, 0x8DC) & 1)) {
            BtlOpp_GetTargetPos(obj, sp);
            func_00210868(obj, sp + 0x10);
            BtlOpp_GetDelta(obj, sp + 0x20);
            if (D_00386708 < fabsf(F32AT(sp, 0x20)) || D_00386708 < fabsf(F32AT(sp, 0x28))) {
                BtlUtil_WrapAngle(atan2f(F32AT(sp, 0x20), F32AT(sp, 0x28)) - F32AT(sp, 0x14));
            }
        }
        f20 = D_0038670C;
        func_00215068(D_00386710, obj, 1, 0xC, f20);
        func_00215E88(f20, obj, 7);
        func_00216208(f21, obj, D_00386714);
        if (func_00211310(obj, 0, 1) != 0) {
            func_002109C8(obj, sp);
            p = BtlChar_GetPos(obj);
            func_00312638(p, BtlChar_GetPos(obj), sp);
        }
        func_002113C0(obj, 9, 0x4000, 1);
    }
    func_00216678(obj);
    func_0020D7E8(5.0f, obj, 10.0f);
    func_002113C0(obj, 5, 1, 1);
    func_002113C0(obj, 3, 0xF, 1);
    if (func_00211310(obj, 0, 0x100) != 0) {
        func_002113C0(obj, 0, 2, 1);
    }
}
