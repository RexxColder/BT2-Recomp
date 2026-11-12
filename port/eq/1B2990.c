#include "common.h"

extern s32 rand(void);
extern s32 func_001B2090(u8 *arg0, u8 *arg1);
extern f32 D_00384FAC;
extern f32 D_00384FB0;
extern f32 D_00384FB4;
extern f32 D_00384FB8;

#define CFG_F32(cfg, off) (*(f32 *)((cfg) + (off)))

/* Spawns timed emitter entries: while the countdown (+0xA5C) is <= 0, picks a burst count from the
   config, claims free 160-byte slots (func_001B2090 fills them), and random-walks the two
   4-entry position tables (+0xA68 / +0xA78) with wrap-around at the limits. */
void func_001B2990(u8 *obj) {
    u8 *st = *(u8 **)(obj + 0x38);
    u8 *cfg = *(u8 **)(st + 0x38);
    s32 noSlot = 0;
    s32 count;
    f32 divisor;
    f32 hiLimit;
    f32 wrap;
    f32 loLimit;

    if (*(f32 *)(st + 0xA5C) > 0.0f) {
        return;
    }
    for (;;) {
        count = cfg[3];
        if (cfg[4] >= 2) {
            count += rand() % cfg[4];
        }
        if (count > 0) {
            divisor = D_00384FAC;
            hiLimit = D_00384FB0;
            wrap = D_00384FB4;
            loLimit = D_00384FB8;
            for (;;) {
                u8 *slot = 0;
                s32 j;
                f32 *p;
                f32 delta;

                noSlot = 1;
                if (*(s32 *)(st + 0x48) == 0) {
                    slot = st + 0x40;
                    noSlot = 0;
                } else {
                    for (j = 1; j < 16; j++) {
                        if (*(s32 *)(st + j * 160 + 0x48) == 0) {
                            noSlot = 0;
                            slot = st + j * 160 + 0x40;
                            break;
                        }
                    }
                }
                if (noSlot || !func_001B2090(obj, slot)) {
                    break;
                }

                delta = (f32)rand() / divisor;
                delta = CFG_F32(cfg, 0xC) + CFG_F32(cfg, 0x10) * delta;
                p = (f32 *)(st + 0xA68) + *(s32 *)(st + 0xA4C);
                if (*(s32 *)(st + 0xA4C) & 1) {
                    *p = *p - delta;
                } else {
                    *p = *p + delta;
                }
                delta = (f32)rand() / divisor;
                delta = CFG_F32(cfg, 0xC) + CFG_F32(cfg, 0x10) * delta;
                p = (f32 *)(st + 0xA78) + *(s32 *)(st + 0xA4C);
                if (*(s32 *)(st + 0xA4C) & 1) {
                    *p = *p - delta;
                } else {
                    *p = *p + delta;
                }

                p = (f32 *)(st + 0xA68) + *(s32 *)(st + 0xA4C);
                if (hiLimit <= *p) {
                    *p = *p - wrap;
                } else if (*p <= loLimit) {
                    *p = *p + wrap;
                }
                p = (f32 *)(st + 0xA78) + *(s32 *)(st + 0xA4C);
                if (hiLimit <= *p) {
                    *p = *p - wrap;
                } else if (*p <= loLimit) {
                    *p = *p + wrap;
                }
                *(s32 *)(st + 0xA4C) = *(s32 *)(st + 0xA4C) + 1;
                if (*(s32 *)(st + 0xA4C) >= 4) {
                    *(s32 *)(st + 0xA4C) = 0;
                }
                if (--count <= 0) {
                    break;
                }
            }
        }
        *(f32 *)(st + 0xA5C) = *(f32 *)(st + 0xA5C) + CFG_F32(cfg, 8);
        if (noSlot || !(*(f32 *)(st + 0xA5C) <= 0.0f)) {
            return;
        }
    }
}
