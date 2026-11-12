#include "common.h"

extern u8 *D_00387958;

void func_00243BD8(void) {
    u8 *d;
    u8 *rec;
    u8 *rec2;
    s32 t0;
    s32 i;
    s32 t2;
    s32 a3;
    s32 flags;
    s32 idx;

    d = D_00387958;

    for (t0 = 0; t0 < 4; t0++) {
        for (i = 0; i <= 0xFF; i++) {
            *(s32 *)(d + (t0 << 10) + 0x210 + i * 4) = -1;
        }
    }

    memset(d + 0x1210, 0, 0x10);

    t0 = 0;
    t2 = 0;
    if (*(s32 *)(d + 0x124C) > 0) {
        do {
            rec = *(u8 **)(d + 0x1250) + t2;
            a3 = *(s32 *)(rec + 8);
            if (a3 < 4) {
                flags = *(s32 *)(rec + 0);
                if (!(flags & 0x41) && (flags & 2)) {
                    if (*(s32 *)(d + (*(s32 *)(d + 0x1284) * 8) + 0x1258) >= *(s32 *)(rec + 0xC)) {
                        *(s32 *)(d + (((a3 << 8) + *(s32 *)(d + a3 * 4 + 0x1210)) * 4) + 0x210) =
                            *(s32 *)(rec + 4);
                        rec2 = *(u8 **)(d + 0x1250) + t2;
                        idx = *(s32 *)(rec2 + 8);
                        *(s32 *)(d + idx * 4 + 0x1210) += 1;
                    }
                }
            }
            t0 += 1;
            t2 += 0x30;
        } while (t0 < *(s32 *)(d + 0x124C));
    }
}
