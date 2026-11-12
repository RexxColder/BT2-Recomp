#include "common.h"

void func_002C32B0(s32 arg0, s32, s32, s32);
void func_002C32C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

u8 *func_002CACB8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];
    u8 *tbl;
    u8 *s0;
    s32 count;
    s32 v1;

    func_002C32B0((s32)sp, arg1, arg2, arg3);
    tbl = *(u8 **)(arg0 + 0x1FC0);
    v1 = 0;
    count = *(s32 *)(tbl + 0x178);
    s0 = tbl + 0x180;
    if (count > 0) {
        for (;;) {
            if (*(s64 *)s0 != 0) {
                v1 += 1;
                s0 += 0xF0;
                if (v1 < count) {
                    continue;
                }
                break;
            }
            *(s32 *)s0 = 1;
            break;
        }
    }
    if ((v1 ^ count) == 0) {
        s0 = NULL;
    }
    func_002C32C8((s32)sp, arg1, arg2, arg3);
    return s0;
}
