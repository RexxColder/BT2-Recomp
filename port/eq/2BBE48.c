#include "common.h"

s32 func_002BC1A0(s32 arg0);

void func_002BBE48(u8 *arg0, s32 arg1) {
    u8 *obj;
    void (*fn)(s32, s32);

    if (func_002BC1A0((s32)arg0) == 1) {
        obj = *(u8 **)(arg0 + 0x8);
        if (obj != NULL) {
            fn = (void (*)(s32, s32))(*(s32 *)(obj + 0x30));
            if (fn != NULL) {
                fn(*(s32 *)(arg0 + 0x1C), arg1);
            }
        }
    }
}
