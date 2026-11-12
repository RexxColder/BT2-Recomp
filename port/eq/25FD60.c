#include "common.h"

s32 func_0025FD60(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *p = arg0 + 0xBD0;
    u8 *t0 = NULL;
    u8 *e;
    s32 t1 = -1;
    s32 t2 = 0;
    s32 t3 = 0;
    s32 t4 = 0;
    s32 t5 = -1;
    s32 cnt;

    if (arg2 == 0) {
        t0 = *(u8 **)(p + 0x28);
    }
    if (arg2 == 1) {
        t0 = *(u8 **)(p + 0x2C);
    }
    if (t0 == NULL) {
        return 0;
    }
    cnt = *(u8 *)(t0 + 1);
    if (cnt != 0) {
        e = t0 + 0x94;
        do {
            u64 key = (u64)*(u32 *)(e + 0) | ((u64)*(u32 *)(e + 4) << 32);

            if ((key & (u64)(s64)arg1) != 0) {
                if (t1 >= 0) {
                    t5 = *(u16 *)(e + 8);
                    t4 = *(s32 *)(e + 0xC);
                } else {
                    t1 = *(u16 *)(e + 8);
                    t2 = *(s32 *)(e + 0xC);
                    t5 = t1;
                    t4 = t2;
                }
                t3 += 1;
            }
            cnt -= 1;
            e += 0x10;
        } while (cnt != 0);
    }
    switch (arg3) {
    case 0:
        return t1;
    case 1:
        return t5;
    case 2:
        return t3;
    case 3:
        return t2;
    case 4:
        return t4;
    default:
        return 0;
    }
}
