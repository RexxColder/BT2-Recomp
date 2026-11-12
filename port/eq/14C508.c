#include "common.h"

void func_00182AB8(s32 arg0);

void func_0014C508(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x38);
    s32 n = *(s32 *)(obj + 0xB14);
    s32 i;
    u8 *slot;

    if (n > 0) {
        slot = obj + 0xAB0;
        i = 0;
        do {
            s32 v = *(s32 *)slot;
            if (v != 0) {
                func_00182AB8(v);
                *(s32 *)slot = 0;
                n = *(s32 *)(obj + 0xB14);
            }
            i++;
            slot += 4;
        } while (i < n);
    }
    *(s32 *)(obj + 0xB14) = 0;
    *(s32 *)(obj + 0xB10) = 0;
}
