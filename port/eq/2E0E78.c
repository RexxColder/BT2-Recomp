#include "common.h"

void func_002E0E78(u8 *arg0, s32 arg2) {
    void (*fn)(s32, u8, u8, u8) = *(void (**)(s32, u8, u8, u8))(arg0 + 0x1C);

    if (fn != NULL) {
        fn(arg2, *(u8 *)(arg0 + 0x14), *(u8 *)(arg0 + 0x15), *(u8 *)(arg0 + 0x16));
    }
}
