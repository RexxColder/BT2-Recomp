#include "common.h"

void *func_001272E0(s32 arg0);
extern s32 D_0036CBB0[];
extern f32 D_003876E8;

/* 0x0011AC70: BT2 form of EftDet_PrepareAll. list = func_001272E0(0), count at +0x6000, 0x180-byte records from
 * list+0x70. Per record: shape+0xC0 = shape+0xC4 = D_003876E8 (FLT_MAX), shape+0xC8 = 0, then the prepare
 * function of its type (7-entry table D_0036CBB0) with the record. */
void EftDet_PrepareAll(void) {
    u8 *list;
    u8 *rec;
    s32 i;
    s32 (*prep)(u8 *);

    list = func_001272E0(0);
    for (i = 0; i < *(s32 *)(list + 0x6000); i++) {
        rec = list + 0x70 + i * 0x180;
        *(f32 *)(rec + 0xC0) = D_003876E8;
        *(f32 *)(rec + 0xC4) = D_003876E8;
        *(s32 *)(rec + 0xC8) = 0;
        prep = (s32 (*)(u8 *))(s32)D_0036CBB0[*(s32 *)rec];
        prep(rec);
    }
}
