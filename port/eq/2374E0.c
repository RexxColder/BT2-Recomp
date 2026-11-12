#include "common.h"

extern s32 func_00217488(s32 obj);
extern void BattleSide_SetChara(s32 obj, s32 chara);
extern void BtlAnim_SetNoBlend(s32 obj);
extern s32 BtlAnim_SetBlend(s32 obj, f32 blend);
extern void func_001F9E38(s32 obj, s32 a1);
extern void func_00212DD8(s32 obj, s32 a1);
extern void func_002113C0(s32 obj, s32 a1, s32 a2, s32 a3);
extern s32 func_0023EAE0(s32 obj);
extern s32 BtlObjAnim_QueryEvent(s32 anim, s64 id, s32 a2, s32 a3);
extern s32 func_00210D98(s32 obj);
extern s32 Battle_GetAnnouncer(s32 obj);
extern s32 Battle_GetRuleUnk10(s32 obj);
extern s32 BattleResult_GetFlags(s32 obj);
extern f32 BtlCharApi_GetHeight(s32 arg0);
extern void func_001FC5A0(s32 obj, void *a1, void *a2, void *a3, s32 a4, s32 a5, s32 a6, s32 a7,
                          f32 f12, f32 f13, f32 f14);
extern f32 func_0023F178(s32 obj);
extern f32 func_00272FA8(void);
extern u8 *BtlChar_GetPos(s32 obj);
extern void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
extern u8 D_002C3630[];
extern f32 D_00386A48;
extern f32 D_00386A4C;
extern f32 D_00386A50;
extern f32 D_00386A54;
extern f32 D_00386A58;

void func_002374E0(s32 obj) {
    s32 isType83;
    s32 v;
    s32 ev;
    s32 d;
    s32 rem;
    s32 noAnn;
    s32 ann, rule;
    s32 e1, e2, half;
    f32 h, left, f12;
    f32 stageY, px, pz, dist;
    u8 *p1;
    u8 *p2;

    isType83 = (func_00217488(obj) ^ 0x83) == 0;
    BattleSide_SetChara(obj, isType83 ? 0x1A1 : 0xA5);
    if (*(u8 *)(obj + 0xB55) != 0) {
        BtlAnim_SetNoBlend(obj);
    } else {
        BtlAnim_SetBlend(obj, D_00386A48);
        func_001F9E38(obj, 0x34);
    }
    func_00212DD8(obj, 7);
    func_002113C0(obj, 0, 2, 1);
    func_002113C0(obj, 0x10, 0x20000, 1);
    *(s32 *)(obj + 0x1450) = *(s32 *)(obj + 0x1450) + 1;
    v = func_0023EAE0(obj);
    *(s32 *)(obj + 0x9C8) = v;
    *(s32 *)(obj + 0x9C4) = v;
    ev = BtlObjAnim_QueryEvent(*(s32 *)(obj + 0x1530), 0x200000000LL, 0, 2);
    d = *(s32 *)(obj + 0x9C4) / (ev + 5);
    *(s32 *)(obj + 0x9D0) = ev;
    *(s32 *)(obj + 0x9D4) = 0x4000;
    *(s32 *)(obj + 0x9CC) = d;
    rem = d % 10;
    if (rem != 0) {
        *(s32 *)(obj + 0x9CC) = d - rem + 10;
    }

    noAnn = func_00210D98(obj) & 0x80;
    if (noAnn == 0) {
        ann = Battle_GetAnnouncer(obj);
        rule = Battle_GetRuleUnk10(obj);
        if (ann > 0 || rule > 0) {
            e1 = BtlObjAnim_QueryEvent(*(s32 *)(obj + 0x1530), 0x20000, 0, 0);
            e2 = BtlObjAnim_QueryEvent(*(s32 *)(obj + 0x1530), 0x40000, 0, 1);
            *(s32 *)(obj + 0x9D8) = ann;
            *(s32 *)(obj + 0x9DC) = ann;
            half = (e2 - e1) / 2;
            if (!(noAnn < half)) {
                half = 1;
            }
            *(s32 *)(obj + 0x9E4) = rule;
            *(s32 *)(obj + 0x9E8) = rule;
            *(s32 *)(obj + 0x9E0) = ann / half + 1;
            *(s32 *)(obj + 0x9EC) = rule / half + 1;
            *(s32 *)(obj + 0x9F0) = e1;
        }
    }

    if (!isType83 && (BattleResult_GetFlags(obj) & 0x8000) == 0) {
        h = BtlCharApi_GetHeight(*(s32 *)(obj + 0x1534));
        f12 = D_00386A4C;
        if (!(0.0f < *(f32 *)(obj + 0x158))) {
            f12 = D_00386A50;
        }
        func_001FC5A0(obj, D_002C3630, D_002C3630, D_002C3630, 3, 3, 0x3C, 0x1E8,
                      f12, D_00386A54, h * 0.5f);
    }

    left = func_0023F178(obj);
    if (__builtin_fabsf(left) < D_00386A58) {
        stageY = func_00272FA8();
        p1 = BtlChar_GetPos(obj);
        px = *(f32 *)p1;
        p2 = BtlChar_GetPos(obj);
        pz = *(f32 *)(p2 + 8);
        dist = __builtin_sqrtf(px * px + pz * pz);
        if (stageY - 200.0f < dist) {
            if (isType83) {
                func_00215068(obj, 7, 12, 0.0f, 0.0f);
            } else {
                func_00215068(obj, 6, 12, 0.0f, 0.0f);
            }
        }
    }
}
