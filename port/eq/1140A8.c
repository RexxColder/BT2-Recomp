#include "common.h"

void func_00113FD0(void *arg0, s32 arg1, s32 arg2, s32 arg3);

/* 0x001140A8: for each of the t0 records (0x60 bytes) at a0 whose first word has bit 0 set, call
 * func_00113FD0(record, a1, a2, a3) with the three arguments reduced to bytes. */
void func_001140A8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *p = arg0;
    s32 i;
    u8 b1 = (u8)arg1;
    u8 b2 = (u8)arg2;
    u8 b3 = (u8)arg3;

    for (i = 0; i < arg4; i++) {
        if (*(s32 *)p & 1) {
            func_00113FD0(p, b1, b2, b3);
        }
        p += 0x60;
    }
}
