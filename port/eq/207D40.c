#include "common.h"

s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 BtlPad_Test50(s32 arg0, s32 arg1);
s32 BtlPad_GetCount11C(s32 arg0, s32 arg1);

s32 BtlPad_TestStep(s32 arg0, s32 arg1) {
    s32 count;

    if ((u32)arg1 >= 10) {
        return 0;
    }
    switch (arg1) {
        case 0:
            if (BtlPad_Test50(arg0, 0) == 0) {
                return 0;
            }
            count = BtlPad_GetCount11C(arg0, 0);
            return count < 7;
        case 1:
            if (BtlPad_Test48(arg0, 0) == 0) {
                return 0;
            }
            count = BtlPad_GetCount11C(arg0, 0);
            return count == 6;
        case 2:
            if (BtlPad_Test50(arg0, 1) == 0) {
                return 0;
            }
            count = BtlPad_GetCount11C(arg0, 1);
            if (count >= 7) {
                return 0;
            }
            return BtlPad_Test48(arg0, 7) == 0;
        case 3:
            if (BtlPad_Test48(arg0, 1) == 0) {
                return 0;
            }
            count = BtlPad_GetCount11C(arg0, 1);
            if (count != 6) {
                return 0;
            }
            return BtlPad_Test48(arg0, 7) == 0;
        default:
            return 0;
    }
}
