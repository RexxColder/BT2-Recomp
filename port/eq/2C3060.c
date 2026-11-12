#include "m2c_macros.h"

void func_002C3060(void *arg0, s32 arg1) {
    u8 *p = (u8 *)arg0;
    void (*fn)(s32);

    if (*(s32 *)(p + 8) == 0) {
        *(s32 *)(p + 8) = arg1;
    }
    if (arg1 != 0) {
        fn = *(void (**)(s32))p;
        if (fn != NULL) {
            fn(*(s32 *)(p + 4));
        }
    }
}
