#include "common.h"

void *func_0026FC38(s32 arg0, s32 arg1) {
    u32 count = *(u32 *)((u8 *)arg0 + 4);
    u8 *p = (u8 *)*(s32 *)((u8 *)arg0 + 0);
    u32 i;

    for (i = 0; i < count; i++, p += 0xC0) {
        if (!(*(s32 *)(p + 0x44) & 1) && *(u16 *)(p + 0x40) == arg1) {
            return p;
        }
    }
    return 0;
}
