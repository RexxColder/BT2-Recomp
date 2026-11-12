#include "common.h"

s32 BtlCharApi_IsHidden(s32 arg0);
s32 EftStage_IsDrawOn(void);
void func_00145368(u8 *arg0);
void func_00145528(u8 *arg0);
s32 func_0020A440(s32 arg0);
s32 func_0020A758(s32 arg0);
s32 func_0020B3D0(s32 arg0);
extern u8 *gEftBound;

void func_00145828(u8 *arg0) {
    u8 *temp_s0;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    if ((EftStage_IsDrawOn() != 0) && (BtlCharApi_IsHidden(*(s32 *)temp_s0) == 0) && ((func_0020A440(*(s32 *)temp_s0) == 0) || ((func_0020A758(*(s32 *)temp_s0) == 0) && (func_0020A758(func_0020B3D0(*(s32 *)temp_s0)) == 0))) && (gEftBound[1] == 1)) {
        if (temp_s0[0x30] != 0) {
            func_00145368(temp_s0 + 0x30);
        }
        if (temp_s0[0x840] != 0) {
            func_00145528(temp_s0 + 0x840);
        }
    }
}
