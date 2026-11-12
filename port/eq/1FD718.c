#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00203888(s32 arg0, s32 arg1, s32 arg2);
s32 func_00203C58(s32 arg0, s64 arg1);
s32 func_0023F420(s32 arg0);
s32 func_0023F430(s32 arg0);
void BtlMember_SubBlast(s32 arg0, s32 arg1);

s32 func_001FD718(u8 *arg0, u8 *arg1) {
    s32 v0;
    s32 t;

    v0 = func_00211310((s32)arg0, 3, 0x100000);
    if (v0 != 0) {
        v0 = func_00211310((s32)arg1, 0, 1);
        if (v0 != 0) {
            v0 = func_00211310((s32)arg0, 1, 1);
            if (v0 != 0) {
                v0 = 0;
                if (func_00211310((s32)arg0, 0, 0x400) == 0) {
                    if ((func_00211310((s32)arg1, 0, 0x4000) == 0) && !(func_0023F430((s32)arg1) & 0x80)) {
                        if (func_0023F420((s32)arg0) & 0x100000) {
                            func_00203888((s32)arg1, 0x4E20, 0);
                        }
                        if (func_00203C58((s32)arg0, 0x400000) != 0) {
                            func_00203888((s32)arg1, 0x4E20, 0);
                        }
                    }
                    if (func_00203C58((s32)arg0, 0x1000000) != 0) {
                        *(s32 *)(arg1 + 0x1188) = 0;
                    }
                    if (func_00203C58((s32)arg0, (s64)0x8000 << 29) != 0) {
                        t = *(s32 *)(arg1 + 0x1188) + (s32)0xFFFF3CB0;
                        *(s32 *)(arg1 + 0x1188) = (t < 0) ? 0 : t;
                    }
                    if (func_00203C58((s32)arg0, 0x4000000) != 0) {
                        BtlMember_SubBlast((s32)arg1, 0x186A0);
                    }
                    v0 = 1;
                }
            }
        }
    }
    return v0;
}
