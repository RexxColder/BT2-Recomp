#include "common.h"

extern u8 *gBtlStage;
extern f32 D_00386FCC;
extern f32 D_00386FD0;
extern f32 D_00386FD4;
extern f32 D_00386FD8;

void EftShotFx_UpdateLines(s32 arg0, s32 arg1, s32 arg2);
void Vu0Cur_StoreMtx(s32 arg0);
void func_0029C980(s32 arg0, s32 arg1, s32 arg2);
s32 func_003126C8(s32 arg0, s32 arg1);

#define S32A(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define F32A(p, off) (*(f32 *)((u8 *)(p) + (off)))

void func_00273C38(s32 arg0, s32 arg1, s32 arg2, f32 farg0) {
    f32 buf[8];
    u8 *base;
    u8 *s0;
    u8 *rec;
    u8 *v0p;
    u8 *v1p;
    u8 *t;
    s32 var_a1;
    s32 var_a2;
    f32 f3;
    f32 f7;
    f32 f4;
    f32 tt;
    f32 lo;
    f32 hi;

    base = (u8 *)S32A(gBtlStage, 0x5C);
    s0 = base + S32A(arg0, 8) * 4;
    buf[3] = 1.0f;
    buf[7] = 1.0f;
    rec = base + S32A(s0, 0x44) * 4;
    var_a1 = arg1;
    var_a2 = arg2;

    if (!((f32)S32A(s0, 0x48) <= farg0)) {
        var_a1 = 1;
        var_a2 = S32A(s0, 0x40);
        while (var_a1 < var_a2) {
            v0p = rec + (var_a1 << 5);
            v1p = v0p - 0x20;
            f3 = (f32)S32A(v1p, 0xC);
            var_a1 += 1;
            if (f3 == farg0) {
                buf[0] = F32A(v1p, 0x0);
                buf[1] = F32A(v1p, 0x4);
                buf[2] = F32A(v1p, 0x8);
                buf[4] = (F32A(v1p, 0x10) / 180.0f) * D_00386FD0;
                buf[5] = (F32A(v1p, 0x14) / 180.0f) * D_00386FD0;
                buf[6] = (F32A(v1p, 0x18) / 180.0f) * D_00386FD0;
                goto call;
            }
            if (f3 < farg0) {
                f7 = (f32)S32A(v0p, 0xC);
                if (farg0 < f7) {
                    f7 = f7 - f3;
                    tt = (farg0 - f3) / f7;
                    buf[0] = (F32A(v0p, 0x0) - F32A(v1p, 0x0)) * tt + F32A(v1p, 0x0);
                    buf[1] = (F32A(v0p, 0x4) - F32A(v1p, 0x4)) * tt + F32A(v1p, 0x4);
                    buf[2] = (F32A(v0p, 0x8) - F32A(v1p, 0x8)) * tt + F32A(v1p, 0x8);
                    f4 = F32A(v1p, 0x10);
                    lo = F32A(v0p, 0x10) + 3600.0f;
                    hi = f4 + 3600.0f;
                    buf[4] = ((((lo - hi) * tt) + f4) / 180.0f) * D_00386FD4;
                    f4 = F32A(v1p, 0x14);
                    lo = F32A(v0p, 0x14) + 3600.0f;
                    hi = f4 + 3600.0f;
                    buf[5] = ((((lo - hi) * tt) + f4) / 180.0f) * D_00386FD4;
                    f4 = F32A(v1p, 0x18);
                    lo = F32A(v0p, 0x18) + 3600.0f;
                    hi = f4 + 3600.0f;
                    buf[6] = ((((lo - hi) * tt) + f4) / 180.0f) * D_00386FD4;
                    goto call;
                }
            }
            if (farg0 == (f32)S32A(v0p, 0xC)) {
                buf[0] = F32A(v0p, 0x0);
                buf[1] = F32A(v0p, 0x4);
                buf[2] = F32A(v0p, 0x8);
                buf[4] = (F32A(v0p, 0x10) / 180.0f) * D_00386FD8;
                buf[5] = (F32A(v0p, 0x14) / 180.0f) * D_00386FD8;
                buf[6] = (F32A(v0p, 0x18) / 180.0f) * D_00386FD8;
                goto call;
            }
        }
        return;
    }

    t = rec + (S32A(s0, 0x40) << 5);
    buf[0] = F32A(t, -0x20);
    buf[1] = F32A(t, -0x1C);
    buf[2] = F32A(t, -0x18);
    buf[4] = (F32A(t, -0x10) / 180.0f) * D_00386FCC;
    buf[5] = (F32A(t, -0xC) / 180.0f) * D_00386FCC;
    buf[6] = (F32A(t, -0x8) / 180.0f) * D_00386FCC;

call:
    EftShotFx_UpdateLines((s32)rec, var_a1, var_a2);
    func_0029C980((s32)buf, (s32)(buf + 4), 2);
    Vu0Cur_StoreMtx((s32)s0);
    func_003126C8(arg1, (s32)(s0 + 0x30));
}
