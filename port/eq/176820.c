#include "common.h"

void func_0014E970(u8 *arg0);

void func_00176820(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x38);

    func_0014E970(obj);
    *(s32 *)(*(u8 **)(obj + 0x1E88) + 0x204) = 0;
}
