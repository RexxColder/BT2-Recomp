#include "common.h"

void func_00307028(s32 arg0, s32 arg1);
s32 strncpy(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00348C50 __attribute__((section(".data")));
extern s32 D_00348C54 __attribute__((section(".data")));
extern u8 D_00348C58[] __attribute__((section(".data")));
extern u8 D_0037BAB8[] __attribute__((section(".data")));

void func_002EA050(s32 arg0) {
    void (*fn)(s32, s32);

    if (arg0 == 0) {
        func_00307028((s32)D_0037BAB8, 0);
        return;
    }
    strncpy((s32)D_00348C58, arg0, 0xFF);
    fn = (void (*)(s32, s32))D_00348C50;
    if (fn != NULL) {
        fn(D_00348C54, (s32)D_00348C58);
    }
    func_00307028((s32)D_00348C58, arg0);
}
