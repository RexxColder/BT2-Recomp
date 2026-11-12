#include "common.h"

void func_002BFBB0(s32 arg0, s32 arg1) {
    u8 *temp_a0;
    u8 *temp_s0;
    u8 *obj;
    s32 fp;

    temp_a0 = (u8 *)arg0 + 0x1310 + arg1 * 0x74;
    temp_s0 = temp_a0 + 0x10;
    if (*(s32 *)temp_a0 == 5) {
        obj = *(u8 **)(temp_s0 + 4);
        if (obj != 0) {
            fp = *(s32 *)(*(u8 **)obj + 0xC);
            ((void (*)(s32, s32, s32))fp)((s32)obj, arg1, 5);
            *(s32 *)(temp_s0 + 4) = 0;
        }
    }
}
