#include "common.h"

s32 func_00217488(s32 arg0);
s32 func_00218838(s32 arg0, s32 arg1);
void *BtlMember_GetActiveGauge(s32 arg0);
void func_00212DD8(s32 arg0, s32 arg1);
s32 rand(void);
void *BtlChar_GetPos(s32 arg0, s32 arg1);
f32 BtlUtil_WrapAngle(f32 farg0);
void BattleSide_SetChara(s32 arg0, s32 arg1);
void func_0020FC38(s32 arg0, s32 arg1);
extern f32 D_00386774;

void func_0022F0D0(s32 arg0) {
    s32 s2;
    s32 s3;
    s32 v;
    u8 *temp_s0;
    u8 *tmp;

    s2 = 0;
    s3 = -1;
    v = func_00217488(arg0);
    if (v == 0x23) {
        s2 = (func_00218838(arg0, 0) == 0) ? 0xF5 : 0xF6;
        s3 = 0x1F;
    } else if (v == 0x24) {
        s2 = (func_00218838(arg0, 0) == 0) ? 0xF7 : 0xF8;
        s3 = 0x1F;
    } else if (v == 0x25) {
        s2 = 0x114;
        s3 = 0x1F;
        if (func_00218838(arg0, 0) != 0) {
            temp_s0 = (u8 *)BtlChar_GetPos(arg0, 0x114);
            tmp = (u8 *)BtlChar_GetPos(arg0, 0x114);
            *(f32 *)(temp_s0 + 0xB4) = BtlUtil_WrapAngle(*(f32 *)(tmp + 0xB4) + D_00386774);
        }
    } else if (v == 0x22) {
        s2 = (func_00218838(arg0, 0) == 0) ? 0xF3 : 0xF4;
        if (*(u8 *)((u8 *)BtlMember_GetActiveGauge(arg0) + 0x28) != 0) {
            if (*(u8 *)((u8 *)BtlMember_GetActiveGauge(arg0) + 0x2A) == 0) {
                func_00212DD8(arg0, (rand() & 1) ? 0x20 : 0x21);
                ((u8 *)BtlMember_GetActiveGauge(arg0))[0x2A] = 1;
            }
        }
    }
    BattleSide_SetChara(arg0, s2);
    if (s3 >= 0) {
        func_0020FC38(arg0, s3);
    }
}
