#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
u8 *BtlChar_GetPos(s32 arg0);
s32 BtlObjAnim_MaskToNode(s32 arg0);
s32 BtlObjAnim_QueryEvent(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
f32 BtlUtil_WrapAngle(f32 farg0);
void func_001F9D10(s32 arg0, s32 arg1);
void func_00206958(s32 arg0, s64 arg1);
void func_0020FC38(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00211418(s32 arg0, s32 arg1);
extern f32 D_003862FC;
extern f32 D_00386300;
extern f32 D_00386304;
extern f32 D_00386308;

void func_00227318(u8 *arg0) {
    f32 f1;
    s32 s1;
    s32 a1;

    s1 = 0x90;
    f1 = BtlUtil_WrapAngle(*(f32 *)(arg0 + 0x150) - *(f32 *)(BtlChar_GetPos((s32)arg0) + 0x14));
    a1 = 0x90;
    if (!(f1 < D_003862FC)) {
        if (f1 < D_00386300) {
            s1 = 0x96;
        } else if (f1 < D_00386304) {
            if (func_00211310((s32)arg0, 0, 1) != 0) {
                *(s32 *)(arg0 + 0x8DC) = *(s32 *)(arg0 + 0x8DC) | 1;
                func_002113C0((s32)arg0, 0, 2, 1);
            }
        } else if (f1 < D_00386308) {
            s1 = 0x93;
        }
        a1 = s1;
    }
    BattleSide_SetChara((s32)arg0, a1);
    func_0020FC38((s32)arg0, 0x2E);
    func_00211418((s32)arg0, 0x10000);
    if (func_00211310((s32)arg0, 1, 4) != 0) {
        func_002113C0((s32)arg0, 0, 2, 1);
    }
    func_001F9D10((s32)arg0, s1 + 2);
    *(s32 *)(arg0 + 0xA20) = BtlObjAnim_MaskToNode(BtlObjAnim_QueryEvent(*(s32 *)(arg0 + 0x1530), 4, 1, 3));
    func_00206958((s32)arg0, 0x80000);
}
