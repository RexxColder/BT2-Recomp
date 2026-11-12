#include "common.h"

extern f32 D_00386464;
extern f32 D_00386468;
extern f32 D_0038646C;
extern f32 D_00386470;
extern f32 D_00386474;
extern f32 D_00386478;
extern f32 D_0038647C;
extern f32 D_00386480;
extern f32 D_00386484;
extern f32 D_00386488;
extern f32 D_0038648C;
extern f32 D_00386490;

s32 BtlObjXf_Update(void *arg0);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
s32 BtlPad_Test4C(void *arg0, s32 arg1);
s32 BtlPad_Test48(void *arg0, s32 arg1);
s32 BtlPad_TestStep(void *arg0, s32 arg1);
void BtlAnim_SetBlend(void *arg0, f32 farg0);
s32 func_0023F420(void *arg0);
s32 func_0023F410(void *arg0);
s32 func_00240438(void *arg0, s32 arg1);
s32 BtlMember_HasKi(void *arg0, s32 arg1);
s32 func_00218758(void *arg0);
u8 *BtlChar_GetPos(void *arg0);
u8 *func_002112D0(void *arg0);
void func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_001FA288(void *arg0, s32 arg1);
s32 func_00212878(void);
s32 func_0023D380(void *arg0);
s32 func_0023C710(void *arg0);

s32 func_00229CE0(void *arg0) {
    void *s0;
    s32 v;
    u8 *p;
    f32 f0;

    /* arg0 is the first argument of the first jal and is passed on */
    v = BtlObjXf_Update(arg0);
    s0 = arg0;
    if (v != 0x2C) {
        v = BtlObjXf_Update(s0);
        if (v != 0x2D) {
            goto L229FE8;
        }
    }

L229D1C:
    if (func_00211310(s0, 5, 0x10) != 0) {
        goto L229E40;
    }
    if (BtlPad_Test4C(s0, 0) != 0) {
        BtlAnim_SetBlend(s0, D_00386464);
        return 0x65;
    }
    v = func_0023F420(s0);
    if ((v & 0x800) == 0) {
        goto L229E04;
    }
    if (BtlPad_TestStep(s0, 2) != 0) {
        v = func_00240438(s0, 8);
        if (BtlMember_HasKi(s0, v) != 0) {
            BtlAnim_SetBlend(s0, D_00386468);
            return 0x89;
        }
    }
    if (BtlPad_TestStep(s0, 3) == 0) {
        goto L229E04;
    }
    v = func_00240438(s0, 0xB);
    if (BtlMember_HasKi(s0, v) == 0) {
        goto L229E04;
    }
    if (func_00218758(s0) == 0) {
        goto L229E04;
    }
    BtlAnim_SetBlend(s0, D_0038646C);
    return 0x8A;

L229E04:
    if (BtlPad_Test4C(s0, 2) != 0) {
        if ((func_0023F420(s0) & 0x100) != 0) {
            BtlAnim_SetBlend(s0, D_00386470);
            return 0x46;
        }
    }

L229E40:
    if (BtlPad_Test4C(s0, 3) != 0) {
        if (func_00211310(s0, 1, 8) == 0) {
            BtlAnim_SetBlend(s0, D_00386474);
            return func_0023D380(s0);
        }
    }
    /* L229E88 */
    if (BtlPad_Test4C(s0, 4) != 0) {
        func_002113C0(s0, 0, 2, 1);
        BtlAnim_SetBlend(s0, D_00386478);
        return func_0023C710(s0);
    }

L229ED0:
    if (BtlPad_Test48(s0, 4) != 0) {
        p = BtlChar_GetPos(s0);
        f0 = *(f32 *)(p + 0xC4);
        if (0.0f < f0) {
            p = func_002112D0(s0);
            f0 = *(f32 *)(p + 0xC4);
            if (f0 <= 0.0f) {
                func_002113C0(s0, 0, 2, 1);
                BtlAnim_SetBlend(s0, D_0038647C);
                return func_0023C710(s0);
            }
        }
    }

L229F50:
    if ((func_0023F410(s0) & 0x1000) == 0) {
        if (BtlPad_Test4C(s0, 5) != 0) {
            func_002113C0(s0, 0, 2, 1);
            BtlAnim_SetBlend(s0, D_00386480);
            return 0x12;
        }
    }

L229F9C:
    if (func_00211310(s0, 0, 0x100) != 0) {
        func_002113C0(s0, 0, 2, 1);
        BtlAnim_SetBlend(s0, D_00386484);
        return func_0023C710(s0);
    }
    goto L229FE8;

L229FE8:
    v = BtlObjXf_Update(s0);
    if (v == 0x2E) {
        if ((func_0023F420(s0) & 0x80000) != 0) {
            if (BtlPad_Test4C(s0, 1) != 0) {
                return 0x57;
            }
        }
    }
    if (func_001FA288(s0, 0x2E) != 0) {
        BtlAnim_SetBlend(s0, D_00386488);
        return func_0023C710(s0);
    }

L229FE8_tail:
    if (func_00211310(s0, 0, 0x20) != 0) {
        BtlAnim_SetBlend(s0, D_0038648C);
        func_002113C0(s0, 0, 2, 1);
        return func_0023C710(s0);
    }
    if (func_00212878() == 0) {
        return -1;
    }
    if (func_00211310(s0, 0, 0x40) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(s0, D_00386490);
    func_002113C0(s0, 0, 2, 1);
    return func_0023C710(s0);
}
