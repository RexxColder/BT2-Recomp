#include "common.h"

void func_0014E970(u8 *arg0);

void func_0015E4A8(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x38);

    func_0014E970(obj);
    *(s32 *)(*(u8 **)(obj + 0x1E84) + 0x204) = 0;
}
