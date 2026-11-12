#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void BtlAnim_SetNoBlend(s32 arg0);
void BtlAnim_SetBlend(f32 farg0, s32 arg1);
s32 BtlChar_GetPos(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
void Quat_Unpack(s32 arg0, s64 arg1);
void Quat_ToEuler(s32 arg0, s32 arg1);
void func_00215E30(f32 farg0, f32 farg1, s32 arg0);
extern f32 D_00386ABC;

void func_00238200(void *arg0) {
    u8 *s0;
    u8 *base;
    u8 *tp;
    u8 *e;
    u16 count;
    u32 aa;
    u32 vv;
    f32 sp[4];
    f32 sp10[4];
    f32 f20;

    s0 = (u8 *)arg0;
    BattleSide_SetChara((s32)arg0, 0xA6);
    func_002113C0((s32)arg0, 0, 2, 1);
    if (*(u8 *)(s0 + 0xB55) != 0) {
        BtlAnim_SetNoBlend((s32)arg0);
    } else {
        BtlAnim_SetBlend(D_00386ABC, (s32)arg0);
    }

    base = (u8 *)(*(s32 *)(s0 + 0x1530));
    tp = (u8 *)(*(s32 *)(base + 0xBF8));
    if (tp != NULL) {
        count = *(u16 *)(tp + 6);
        if (count != 0) {
            f20 = 0.0f;
            e = tp + (count * 4);
            if ((s32)*(u16 *)(e + 2) > 0) {
                if (*(u16 *)(e + 0) & 1) {
                    vv = *(u32 *)(e + 8);
                    aa = *(u32 *)(e + 4);
                } else {
                    vv = *(u32 *)(e + 0x18);
                    aa = *(u32 *)(e + 0x14);
                }
                Quat_Unpack((s32)sp, (s64)aa + ((s64)vv << 32));
                Quat_ToEuler((s32)sp10, (s32)sp);
                f20 = sp10[1];
            }
            func_00215E30(BtlUtil_WrapAngle(*(f32 *)((u8 *)BtlChar_GetPos((s32)arg0) + 0xB4) - f20), 0.0f,
                          (s32)arg0);
        }
    }
}
