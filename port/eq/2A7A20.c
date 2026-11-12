#include "common.h"

s32 StgPanBlur_Term(void);
void func_00101498(void);
s32 func_002A0010(s32 arg0);

s32 func_002A7A20(s32 arg0) {
    s32 ret = 0;

    if (arg0 == 0) {
        func_00101498();
        if (func_002A0010(0x77) == 0) {
            ret = 1;
        }
    } else if (arg0 == 2) {
        ret = StgPanBlur_Term() == 5;
    }
    return ret;
}
