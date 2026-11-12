#include "common.h"

void func_002E1CE8(s32 *arg0, s32 arg1) {
    void (*fn)(s32);

    arg0[2] = arg1;
    if (arg1 != 0) {
        fn = (void (*)(s32))arg0[0];
        if (fn != NULL) {
            fn(arg0[1]);
        }
    }
}
