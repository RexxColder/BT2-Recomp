#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 func_001F9FB0(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void BtlOpp_GetTargetPos(s32 arg0, s32 arg1);
f32 func_00273000(void);
f32 tanf(f32 farg0);
f32 sinf(f32 farg0);
f32 cosf(f32 farg0);
f32 func_0029DFD0(s32 arg0);
void sceVu0Normalize(s32 arg0, s32 arg1);
s32 func_00212878(void);
f32 func_002086B0(s32 arg0);
f32 func_00272FA8(void);
void *BtlChar_GetPos(s32 arg0);
s32 func_003126C8(s32 arg0, s32 arg1);
s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
void func_00215068(s32 a0, s32 a1, s32 a2, f32 fMax, f32 fScale);
void func_002608E8(s32 arg0);
s32 BattleSide_GetStartChara(s32 arg0);
s32 func_001F9D78(s32 arg0, s32 arg1);
void func_00206958(s32 arg0, s32 arg1);
f32 func_001FA318(s32 arg0);
void func_00215E88(s32 a0, u32 a1);
void func_00216208(f32 farg0, f32 farg1, s32 arg0);
void func_00216678(s32 a0);
extern f32 D_003867DC;
extern f32 D_003867E0;
extern f32 D_003867E4;
extern f32 D_003867E8;
extern f32 D_003867EC;
extern f32 D_003867F0;
extern f32 D_003867F4;
extern f32 D_003867F8;

#define ADDR(p) ((s32)(u32)(p))

/* 0x0022FA88: character action update. anim 0,1,50,51: short wind-up (counter at +0x8C0);
 * anim 0x10C: wait for the move to end, then warp to a spot in front of the target and restart. */
void func_0022FA88(s32 obj) {
    u8 *self = (u8 *)(u32)obj;
    s32 *count = (s32 *)(self + 0x8C0);
    s32 anim = BtlObjXf_Update(obj);
    f32 target[4];  /* sp 0x00 */
    f32 spot[4];    /* sp 0x10 */
    f32 dir[4];     /* sp 0x20 */
    f32 groundY;
    f32 angle;
    f32 t;
    f32 lim;
    f32 len;
    f32 ref;

    if (anim >= 52) {
        if (anim == 268) {
            if (func_001F9FB0(obj, 0) != 0) {
                func_002113C0(obj, 9, 0x4000, 1);
                *count = *count + 1;
                if (*count >= 9) {
                    BtlOpp_GetTargetPos(obj, ADDR(target));
                    groundY = func_00273000();
                    dir[2] = -target[2];
                    dir[0] = -target[0];
                    angle = D_003867DC;
                    dir[1] = -tanf(angle) * __builtin_sqrtf(dir[0] * dir[0] + dir[2] * dir[2]);
                    if (func_0029DFD0(ADDR(dir)) < D_003867E0) {
                        *(s32 *)&dir[0] = 0;
                        dir[1] = -sinf(angle);
                        dir[2] = cosf(angle);
                    } else {
                        sceVu0Normalize(ADDR(dir), ADDR(dir));
                    }
                    ref = 300.0f;
                    t = (groundY - target[1]) / dir[1];
                    if (t < ref) {
                        t = ref;
                    }
                    spot[1] = target[1] + dir[1] * t;
                    spot[0] = target[0] + dir[0] * t;
                    spot[2] = target[2] + dir[2] * t;
                    if (func_00212878() != 0) {
                        lim = ref - func_002086B0(*(s32 *)(self + 0x1534));
                    } else {
                        lim = func_00272FA8();
                        lim = lim - func_002086B0(*(s32 *)(self + 0x1534));
                    }
                    len = __builtin_sqrtf(spot[0] * spot[0] + spot[2] * spot[2]);
                    if (lim < len) {
                        lim = lim / len;
                        spot[2] = spot[2] * lim;
                        spot[0] = spot[0] * lim;
                    }
                    func_003126C8(ADDR(BtlChar_GetPos(obj)), ADDR(spot));
                    BtlAnim_SetBlend(obj, D_003867E4);
                    func_00215068(obj, 1, 13, D_003867E8, 1.0f);
                    func_002608E8(*(s32 *)(self + 0x1530));
                    func_002113C0(obj, 3, 0x800, 1);
                    func_002113C0(obj, 14, 0x40, 1);
                    func_002113C0(obj, 15, 0x20, 1);
                    func_002113C0(obj, 7, 0x200, 1);
                    func_001F9D78(obj, BattleSide_GetStartChara(obj));
                    *count = 0;
                }
            }
            func_002113C0(obj, 3, 0xF, 1);
        }
    } else if (anim >= 50 || (anim >= 0 && anim < 2)) {
        *count = *count + 1;
        if (*count == 5) {
            func_00206958(obj, 0x4000);
        }
        if (*count < 6) {
            func_002113C0(obj, 9, 0x4000, 1);
            func_002113C0(obj, 3, 0xF, 1);
        } else {
            func_001F9FB0(obj, 0);
            if (D_003867EC < func_001FA318(obj)) {
                *(s32 *)(self + 0x8DC) = *(s32 *)(self + 0x8DC) | 1;
            }
        }
    }
    func_00215068(obj, 5, 13, D_003867F4, D_003867F0);
    func_00215E88(obj, 7);
    func_00216208(0.0f, D_003867F8, obj);
    func_00216678(obj);
}
