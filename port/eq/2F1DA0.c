#include "common.h"

void func_002F1C48(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_0030A5F0(void);

void func_002F1DA0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_002F1C48((s32)arg0, arg1, arg2, arg3, arg4);
    do {
        func_0030A5F0();
    } while (*(s8 *)(arg0 + 0x45) != 0);
}
