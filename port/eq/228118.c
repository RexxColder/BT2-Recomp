#include "m2c_macros.h"

extern f32 D_0038638C;
extern f32 D_00386390;
extern f32 D_00386394;

s32 BtlObjXf_Update(void *obj);
void *BtlChar_GetPos(void *obj);
void BtlAnim_SetBlend(void *obj, f32 w);
f32 func_00217330(void *obj);
f32 BtlCharApi_GetHeight(s32 id);
s32 func_00212878(void *obj);
void func_00212DD8(void *obj, s32 a1);
s32 func_0023C798(void *obj, s32 a1);
s32 func_00211310(void *obj, s32 a1, s32 a2);
s32 func_00218128(void *obj, s32 a1, s32 a2);
s32 func_0023BDA8(void *obj, s32 a1);

s32 func_00228118(void *obj) {
    s32 s0;
    s32 v;
    s32 r;
    s32 keep;
    s32 sel;
    f32 t;
    f32 h;
    void *p;

    if (BtlObjXf_Update(obj) == 0x1A4) {
        p = BtlChar_GetPos(obj);
        if (M2C_FIELD(p, s32 *, 0xDC) >= 0x5B) {
            BtlAnim_SetBlend(obj, D_0038638C);
            t = func_00217330(obj);
            h = BtlCharApi_GetHeight(M2C_FIELD(obj, s32 *, 0x1534));
            if (!(h + h < t)) {
                if (func_00212878(obj) == 0) {
                    return 0xA;
                }
                if (M2C_FIELD(M2C_FIELD(obj, s32 *, 0x1530), s32 *, 0xE80) & 0x80) {
                    return 0xA;
                }
            }
            func_00212DD8(obj, 0);
            return 0x21;
        }
    }

    s0 = func_0023C798(obj, 0x44F);
    if (s0 != -1) {
        BtlAnim_SetBlend(obj, D_00386390);
        return s0;
    }

    v = BtlObjXf_Update(obj);
    s0 = 0x01080783;
    if ((v ^ 0x1A4) != 0) {
        s0 = 0x019A07E3;
    }
    s0 = s0 | 0x00040000;
    s0 = s0 | 0x00200000;
    s0 = s0 | 0x00400000;
    s0 = s0 | 0x02000000;
    s0 = s0 | 0x04000000;

    /* the movz in the delay slot of the next jal picks s0|0x1C when r == 0 */
    r = func_00211310(obj, 1, 1);
    keep = s0 | 0xB800;
    sel = s0 | 0x1C;
    s0 = keep;
    if (r == 0) {
        s0 = sel;
    }
    /* 4th argument (a3) is not set by the asm: garbage after the jal above */
    r = func_00218128(obj, 3, keep);
    if (r != 0) {
        s0 = s0 | 0x10000;
    }
    r = func_0023BDA8(obj, s0);
    if (r == -1) {
        return r;
    }
    BtlAnim_SetBlend(obj, D_00386394);
    return r;
}
