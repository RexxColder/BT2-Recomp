#include "common.h"

s32 BtlScene_IsCharInView(s32 arg0);
s32 func_00126560(s32 arg0);
s32 func_00126588(void);
s32 func_00126698(void);
s32 func_00126EC0(void);
extern u8 *D_003876A0;

s32 func_00126598(s32 arg0) {
    if (func_00126560(arg0) != 0) {
        return 1;
    }
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 2) == 0) {
        return BtlScene_IsCharInView(arg0);
    }
    if (func_00126698() != 0) {
        if (func_00126EC0() != 0) {
            return 1;
        }
        return BtlScene_IsCharInView(arg0);
    }
    return func_00126588() == arg0;
}
