#include "common.h"

void func_002B4C70(s32 arg0, s32 arg1);
void func_002B4C78(s32 arg0, s32 arg1);
void func_002B4D20(s32 arg0, s32 arg1);

void func_002B4C20(u8 *arg0, s32 arg1) {
    if (*(s32 *)(arg0 + 0x1EC) != 0) {
        func_002B4C70((s32)arg0, arg1);
    } else {
        func_002B4C78(arg1, arg1);
    }
    func_002B4D20((s32)arg0, arg1);
}
