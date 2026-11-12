#include "common.h"

void func_002F9300(s32 arg0);
s32 func_002F95C8(s32 arg0);
extern u8 D_0037DC50[] __attribute__((section(".data")));
extern u8 D_0037DC80[] __attribute__((section(".data")));
extern u8 D_0037DCB0[] __attribute__((section(".data")));

s32 func_002FAF78(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[5];
    u8 *a0;
    u8 *obj;
    s32 result;
    s32 (*fn)(s32, s32, s32, s32);

    if (arg0 == 0) {
        a0 = D_0037DC50;
    } else if (arg1 == 0) {
        a0 = D_0037DC80;
    } else {
        obj = (u8 *)func_002F95C8(arg0);
        if (obj == NULL) {
            a0 = D_0037DCB0;
            func_002F9300((s32)a0);
            return -1;
        }
        memset((void *)sp, 0, 0x14);
        result = -1;
        sp[1] = arg1;
        sp[2] = arg2;
        fn = *(s32 (**)(s32, s32, s32, s32))(obj + 0x60);
        if (fn != NULL) {
            result = fn((s32)sp, 5, 0, 0);
        }
        return result;
    }
    func_002F9300((s32)a0);
    return -1;
}
