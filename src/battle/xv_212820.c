#include "common.h"

s32 BtlMember_IsHealthEmpty_2127F8(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);

/* 1 when the member (arg0) is not health-empty, func_00211310(obj, 0, 0x4000) is zero and the s32 at +0xB74 is < 1;
 * 0 otherwise */
s32 func_00212820(s32 arg0) {
    if (BtlMember_IsHealthEmpty_2127F8(arg0) != 0) {
        return 0;
    }
    if (func_00211310(arg0, 0, 0x4000) != 0) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + 0xB74) < 1;
}
