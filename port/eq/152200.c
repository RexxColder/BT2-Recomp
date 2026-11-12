#include "common.h"

/* 0x00152200: obj = *arg0; count = obj->0x550 (u8). For two blocks k = 0, 1 at arg1 + 0xF0 + k * 0x364, if count != 0
 * test the count words at block + 0x280; returns 1 when any of them is non-zero, else 0. */
s32 func_00152200(u8 *arg0, s32 arg1) {
    u8 *obj = *(u8 **)arg0;
    s32 count = *(u8 *)(obj + 0x550);
    s32 a1 = arg1 + 0xF0;
    s32 a3 = 0;
    s32 t1;

    for (t1 = 1; t1 >= 0; t1--) {
        if (count != 0) {
            s32 *p = (s32 *)(a1 + 0x280);
            s32 v1 = count;

            do {
                s32 v = *p;

                p++;
                v1--;
                if (v != 0) {
                    a3 = 1;
                }
            } while (v1 != 0);
        }
        a1 += 0x364;
    }
    return a3;
}
