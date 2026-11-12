#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_00387958;
extern u8 *D_00387F2C;

void func_00243D18(void) {
    s32 i;
    s32 k;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 a1;
    s32 flags;
    u8 *rec;

    for (i = 0; i < 4; i++) {
        for (k = 0; k < 256; k++) {
            *(s32 *)(D_00387958 + (i << 10) + 0x210 + k * 4) = -1;
        }
    }
    memset(D_00387958 + 0x1210, 0, 0x10);
    t2 = 0x1F30;
    t1 = 0;
    t0 = 0x242;
    do {
        rec = (u8 *)(*(s32 *)(D_00387958 + 0x1250) + t1);
        a1 = *(s32 *)(rec + 8);
        if (a1 < 4) {
            flags = *(s32 *)rec;
            if (!(flags & 0x41)) {
                if (flags & 4) {
                    if (*(s16 *)(D_00387F2C + t2 + 2) > 0) {
                        *(s32 *)(D_00387958 + ((((a1 << 8) + *(s32 *)(D_00387958 + 0x1210 + a1 * 4)) * 4)) + 0x210) = *(s32 *)(rec + 4);
                        *(s32 *)(D_00387958 + (*(s32 *)(rec + 8) * 4) + 0x1210) += 1;
                    }
                }
            }
        }
        t0 -= 1;
        t2 += 4;
        t1 += 0x30;
    } while (t0 >= 0);
}
