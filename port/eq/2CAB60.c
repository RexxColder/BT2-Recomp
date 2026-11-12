#include "m2c_macros.h"

void *func_002CAB60(void *arg0, s32 arg1) {
    s32 i = 0;
    u8 *p = *(u8 **)((u8 *)arg0 + 0x1FC0) + 0x180;
    u8 *v0;
    s32 v1 = *(s32 *)(p + 0x58);

    while (1) {
        v0 = p;
        p += 0xF0;
        if (v1 == arg1) {
            return v0;
        }
        i++;
        if (i >= 0x10) {
            return NULL;
        }
        v1 = *(s32 *)(p + 0x58);
    }
}
