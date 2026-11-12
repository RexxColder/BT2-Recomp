#include "common.h"

void func_002BFE48(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002BFE68(s32 arg0);

void func_002BFDF8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *p = arg0 + 116 * arg3;

    func_002BFE48((s32)p, 3, 1, arg3);
    func_002BFE68((s32)(p + 0x10));
}
