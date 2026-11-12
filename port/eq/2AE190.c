#include "common.h"

void BtlMenu_EndDraw(f32 farg0, s32 arg0);
s32 func_002B0DA0(s32 arg0, s32 arg1);
s32 func_002B0DB0(s32 arg0, s32 arg1);
s32 func_002B20B0(void);
extern f32 D_00387330;
extern f32 D_00387334;
extern f32 D_00387338;
extern f32 D_0038733C;
extern f32 D_00387340;
extern f32 D_00387344;

s32 func_002AE190(s32 arg0) {
    if (func_002B0DB0(arg0, 0x05000000) == 0) {
        if (func_002B0DA0(arg0, 0x400) == 0) {
            if (func_002B0DB0(arg0, 0x100) == 0) {
                if (func_002B0DB0(arg0, 0x800) == 0) {
                    if (func_002B0DB0(arg0, 0x200) == 0) {
                        if (func_002B0DA0(arg0, 0x4000) == 0) {
                            return -1;
                        }
                        if (func_002B20B0() < 0) {
                            return -1;
                        }
                        BtlMenu_EndDraw(D_00387344, arg0);
                        return 7;
                    }
                    BtlMenu_EndDraw(D_00387340, arg0);
                    return 5;
                }
                BtlMenu_EndDraw(D_0038733C, arg0);
                return 4;
            }
            BtlMenu_EndDraw(D_00387338, arg0);
            return 3;
        }
        BtlMenu_EndDraw(D_00387334, arg0);
        return 6;
    }
    BtlMenu_EndDraw(D_00387330, arg0);
    return 2;
}
