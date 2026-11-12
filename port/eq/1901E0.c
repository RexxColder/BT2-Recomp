#include "common.h"

s64 EftVram_AddImage(s32 arg0, s32 arg1, s32 arg2);
s64 EftVram_AddClut(s32 arg0);

void func_001901E0(s32 arg0, s32 arg1) {
    s32 i;
    s32 count;
    s32 p5;
    s32 t;
    s32 t2;
    s32 s0;
    s32 s3;
    s32 varA0;
    s64 tmp;

    if (arg1 == 0) {
        return;
    }
    count = *(u8 *)(arg0 + 0x4E);
    if (count == 0) {
        return;
    }
    i = 0;
    p5 = arg0 + 0x46;
    do {
        t = *(u8 *)p5;
        if (!(*(u16 *)(arg0 + 0x44) & 0x400)) {
            s3 = (s32)(1u << (t & 31));
            s0 = arg1 + (t * 16);
            varA0 = s0;
        } else {
            t2 = t + *(u8 *)(arg0 + 0x50);
            s3 = (s32)(1u << (t2 & 31));
            varA0 = arg1 + (t * 16);
            s0 = arg1 + (t2 * 16);
        }
        if (!(*(s32 *)(arg1 + 0x84) & s3)) {
            tmp = EftVram_AddImage(varA0, 1, 0);
            *(s64 *)s0 = tmp | (EftVram_AddClut(s0) << 37);
            *(s32 *)(arg1 + 0x84) = *(s32 *)(arg1 + 0x84) | s3;
        }
        i += 1;
        p5 += 1;
    } while (i < *(u8 *)(arg0 + 0x4E));
}
