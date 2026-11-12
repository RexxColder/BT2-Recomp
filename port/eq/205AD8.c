#include "common.h"

s32 func_001A5EF0(s32 arg0, s32 arg1, s32 arg2);
s32 BtlObjXf_Update(s32 arg0);
s32 func_001FA3A8(s32 arg0);
s32 func_001FBE80(s32 arg0, f32 farg0, f32 farg1);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
s32 BtlCharApi_IsInTechnique(s32 arg0);
void func_0020FC38(s32 arg0, s32 arg1);
s32 func_00210DD8(s32 arg0);
s32 func_00211288(s32 arg0);
s32 func_00212320(s32 arg0);
s32 BtlChar_FrameMod(s32 arg0);
s32 func_00212DD8(s32 arg0, s32 arg1);
s32 func_0023F410(s32 arg0);
s32 func_002411E0(s32 arg0, s32 arg1);
s32 func_0025FBE8(s32 arg0, s64 arg1);
s32 BtlObjAnim_GetEventArg(s32 arg0, s32 arg1);
s32 BtlObjAnim_MaskToNode(s32 arg0);
extern f32 D_00385938;
extern f32 D_0038593C;

#define O1530(a) (*(s32 *)((u8 *)(a) + 0x1530))
#define O1534(a) (*(s32 *)((u8 *)(a) + 0x1534))

s32 func_00205AD8(s32 arg0) {
    u8 sp[0x10];
    s32 s2, s0, v;

    if (func_0025FBE8(O1530(arg0), 0x100) != 0) {
        s2 = 1;
        if ((*(u32 *)((u8 *)O1530(arg0) + 0xAF0) & 2) != 0) {
            v = BtlObjAnim_MaskToNode(BtlObjAnim_GetEventArg(O1530(arg0), 0x100));
            func_00208DE8(O1534(arg0), (s32)sp, v);
            func_001A5EF0(0, (s32)sp, O1534(arg0));
            func_001FBE80(arg0, 5.0f, D_00385938);
            if ((func_0023F410(arg0) & 0x40) != 0 &&
                (*(u64 *)((u8 *)O1530(arg0) + 0xAF0) & 0x22) == 0x22) {
                func_0020FC38(arg0, 0x4D);
            } else {
                func_0020FC38(arg0, BtlChar_FrameMod(2) + 2);
            }
        }
        if ((func_001FA3A8(BtlObjXf_Update(arg0)) & 0x10) != 0) {
            s0 = func_00211288(func_00210DD8(arg0));
            if (BtlCharApi_IsInTechnique(O1534(s0)) != 0) {
                s2 = (func_002411E0(s0, func_00212320(s0)) & 0x20000000) == 0;
            }
            if (s2 != 0) func_00212DD8(arg0, 0);
        } else {
            if (BtlCharApi_IsInTechnique(O1534(arg0)) != 0) {
                s2 = (func_002411E0(arg0, func_00212320(arg0)) & 0x20000000) == 0;
            }
            if (s2 != 0) {
                func_00212DD8(func_00211288(func_00210DD8(arg0)), 0);
            }
        }
    }
    if (func_0025FBE8(O1530(arg0), 0x80) == 0) return 0;
    s2 = 1;
    if ((*(u32 *)((u8 *)O1530(arg0) + 0xAF0) & 2) != 0) {
        v = BtlObjAnim_MaskToNode(BtlObjAnim_GetEventArg(O1530(arg0), 0x80));
        func_00208DE8(O1534(arg0), (s32)sp, v);
        func_001A5EF0(6, (s32)sp, O1534(arg0));
        func_001FBE80(arg0, 10.0f, D_0038593C);
    }
    if ((func_0023F410(arg0) & 0x40) != 0 &&
        (*(u64 *)((u8 *)O1530(arg0) + 0xAF0) & 0x22) == 0x22) {
        func_0020FC38(arg0, 0x36);
    } else {
        func_0020FC38(arg0, 0x49);
    }
    if ((func_001FA3A8(BtlObjXf_Update(arg0)) & 0x10) != 0) {
        s0 = func_00211288(func_00210DD8(arg0));
        if (BtlCharApi_IsInTechnique(O1534(s0)) != 0) {
            s2 = (func_002411E0(s0, func_00212320(s0)) & 0x20000000) == 0;
        }
        if (s2 != 0) return func_00212DD8(arg0, 1);
    } else {
        if (BtlCharApi_IsInTechnique(O1534(arg0)) != 0) {
            s2 = (func_002411E0(arg0, func_00212320(arg0)) & 0x20000000) == 0;
        }
        if (s2 != 0) return func_00212DD8(func_00211288(func_00210DD8(arg0)), 1);
    }
    return 0;
}
