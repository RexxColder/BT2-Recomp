#include "common.h"

extern s32 D_00347600 __attribute__((section(".data")));
extern s32 func_002DCB88(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_002DCC38(void *arg0);
extern s32 func_002DCA68(s32 arg0, s32 arg1);

s32 func_002DCAF0(u8 *obj, s32 arg1, s32 arg2) {
    s32 ret;

    if (obj == 0) {
        ret = func_002DCB88(D_00347600, arg1, arg2);
    } else if (func_002DCC38(obj) != 0) {
        return func_002DCA68(0, (s32)0xFF020101);
    } else {
        func_002DCB88((s32)(obj + 4), arg1, arg2);
        ret = 0;
    }
    return ret;
}
