#include "common.h"

void func_002F1188(u8 *arg0) {
    s32 sp[4];
    s32 s1;
    s32 s3;
    s32 s4;
    void *obj;
    u8 *vt;
    u8 *pp;

    s3 = 0;
    s1 = *(s32 *)(arg0 + 0xA4) * 2;
    if (*(s8 *)(arg0 + 2) > 0) {
        pp = arg0 + 0xC;
        do {
            obj = *(void **)pp;
            s3 += 1;
            vt = *(u8 **)obj;
            (*(void (**)(void *, s32, s32, void *))(vt + 0x18))(obj, 1, 0x7FFFFFFF, sp);
            obj = *(void **)pp;
            vt = *(u8 **)obj;
            pp += 4;
            s1 = (s1 >= sp[1]) ? sp[1] : s1;
            (*(void (**)(void *, s32, void *, void *))(vt + 0x1C))(obj, 1, sp, vt);
        } while (s3 < *(s8 *)(arg0 + 2));
    }
    s4 = s1 / 2;
    s1 = s4 * 2;
    if (s1 > 0) {
        s3 = 0;
        if ((s32)((u32)*(u8 *)(arg0 + 2) << 24) > 0) {
            pp = arg0 + 0xC;
            do {
                obj = *(void **)pp;
                s3 += 1;
                vt = *(u8 **)obj;
                (*(void (**)(void *, s32, s32, void *))(vt + 0x18))(obj, 1, s1, sp);
                obj = *(void **)pp;
                vt = *(u8 **)obj;
                pp += 4;
                (*(void (**)(void *, s32, void *))(vt + 0x20))(obj, 0, sp);
            } while (s3 < *(s8 *)(arg0 + 2));
        }
        *(s32 *)(arg0 + 0xA4) = *(s32 *)(arg0 + 0xA4) - s4;
    }
}
