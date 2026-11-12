#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
void BtlAnim_SetNoBlend(s32 arg0);
u8 *BtlChar_GetPos(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
void Quat_ToEuler(void *arg0, void *arg1);
void Quat_Unpack(void *arg0, s64 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215E30(s32 arg0, f32 farg0, f32 farg1);
s32 func_00217488(s32 arg0);
extern f32 D_00386A6C;

void func_00237A48(u8 *arg0) {
    s32 v0;
    u8 *p;
    u8 *a;
    u8 *pos;
    u16 cnt;
    u32 lo;
    u32 hi;
    s64 packed;
    s32 q[4];
    f32 e[4];
    f32 f20;

    v0 = func_00217488((s32)arg0);
    if (v0 == 0x80) {
        BattleSide_SetChara((s32)arg0, 0xA6);
    } else if (v0 == 0x84) {
        BattleSide_SetChara((s32)arg0, 0x1A2);
    }
    func_002113C0((s32)arg0, 0, 2, 1);
    if (arg0[0xB55] != 0) {
        BtlAnim_SetNoBlend((s32)arg0);
    } else {
        BtlAnim_SetBlend((s32)arg0, D_00386A6C);
    }
    p = *(u8 **)(*(u8 **)(arg0 + 0x1530) + 0xBF8);
    if (p != NULL) {
        cnt = *(u16 *)(p + 6);
        if (cnt != 0) {
            f20 = 0.0f;
            a = p + (cnt * 4);
            if (*(u16 *)(a + 2) > 0) {
                if (*(u16 *)(a + 0) & 1) {
                    hi = *(u32 *)(a + 8);
                    lo = *(u32 *)(a + 4);
                } else {
                    hi = *(u32 *)(a + 0x18);
                    lo = *(u32 *)(a + 0x14);
                }
                packed = (s64)lo + ((s64)hi << 32);
                Quat_Unpack(q, packed);
                Quat_ToEuler(e, q);
                f20 = e[1];
            }
            pos = BtlChar_GetPos((s32)arg0);
            f20 = BtlUtil_WrapAngle(*(f32 *)(pos + 0xB4) - f20);
            func_00215E30((s32)arg0, f20, 0.0f);
        }
    }
}
