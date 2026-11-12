#include "common.h"

s32 BtlMember_IsHealthEmpty(s32 arg0);
s32 func_00211288(s32 arg0);
extern s32 D_00387930;

s32 func_0020AE40(u32 arg0) {
    if (D_00387930 == 0) {
        return 0;
    }
    if (!(arg0 < 2U)) {
        return 0;
    }
    if (BtlMember_IsHealthEmpty(func_00211288((s32)arg0)) == 0) {
        return 0;
    }
    return 1;
}
