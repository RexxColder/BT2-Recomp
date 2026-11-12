#include "common.h"

void func_003061A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

#define VCALL3(obj, off) (*(void (**)(s32, s32, s32))(*(u8 **)(obj) + (off)))

void func_002BDC58(u8 *arg0, s32 arg1, s32 arg2) {
    s32 sp[4];

    if (arg1 == 0) {
        VCALL3(arg0, 0x1C)((s32)arg0, arg1, arg2);
        return;
    }
    func_003061A8(arg2, arg1, arg2, (s32)sp);
    VCALL3(arg0, 0x20)((s32)arg0, 1, arg2);
    VCALL3(arg0, 0x1C)((s32)arg0, 0, (s32)sp);
}
