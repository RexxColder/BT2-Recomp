#include "m2c_macros.h"

extern u8 D_0036E188[];
s32 EftShot_TestBits(s32 objId, s32 mask);
void func_00208DE8(s32 arg0, u8 *arg1, s32 arg2);
void *memcpy(void *dst, const void *src, s32 n);

/* Six 0x40-byte records after arg1; a 2-bit flag pair per record in the word at arg1+0. */
void EftShot_BitTableUpdate(s32 arg0, u8 *arg1) {
    u32 tw[6];
    s32 i;
    u32 bit;
    u8 *rec;

    memcpy(tw, D_0036E188, 24);
    for (i = 0; i < 6; i++) {
        bit = 1u << (2 * i);
        rec = arg1 + 0x40 * i;
        if (*(u32 *)arg1 & bit) {
            func_00208DE8(arg0, rec + 0x20, *(s32 *)(rec + 0x10));
        } else {
            if (EftShot_TestBits(arg0, tw[i])) {
                *(u32 *)arg1 |= bit;
                *(s32 *)(rec + 0x10) = 0x23;
            }
            if (*(u32 *)arg1 & bit) {
                func_00208DE8(arg0, rec + 0x20, *(s32 *)(rec + 0x10));
            } else if (*(u32 *)arg1 & 1) {
                func_00208DE8(arg0, rec + 0x20, *(s32 *)(arg1 + 0x10));
            }
        }
        if (*(u32 *)arg1 & (1u << (2 * i + 1))) {
            func_00208DE8(arg0, rec + 0x40, *(s32 *)(rec + 0x30));
        } else if (*(u32 *)arg1 & 1) {
            func_00208DE8(arg0, rec + 0x40, *(s32 *)(arg1 + 0x10));
        }
    }
}
