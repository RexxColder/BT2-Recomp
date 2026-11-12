#include "common.h"

typedef void (*Fn4)(s32, s32, s32, s32);
typedef void (*Fn3)(s32, s32, s32);

void memset(void *arg0, s32 arg1, s32 arg2);

void func_002F1038(u8 *arg0) {
    s32 sp[4];
    u8 **pp;
    u8 *o;
    u8 *vt;
    s32 s1;
    s32 s3;
    s32 s4;
    s32 t;
    s32 i;
    s32 count;

    s3 = 0;
    s1 = *(s32 *)(arg0 + 0xA0) * 2;
    count = *(s8 *)(arg0 + 2);
    pp = (u8 **)(arg0 + 0xC);
    if (count > 0) {
        i = 0;
        do {
            o = pp[i];
            s3 += 1;
            ((Fn4)(*(s32 *)(*(u8 **)o + 0x18)))((s32)o, 0, 0x7FFFFFFF, (s32)sp);
            o = pp[i];
            t = sp[1];
            vt = *(u8 **)o;
            i += 1;
            if (!(s1 < t)) {
                s1 = t;
            }
            ((Fn4)(*(s32 *)(vt + 0x1C)))((s32)o, 0, (s32)sp, (s32)vt);
        } while (s3 < (s32)*(s8 *)(arg0 + 2));
    }

    s4 = s1 / 2;
    s1 = s4 * 2;
    if (s1 > 0) {
        s3 = 0;
        if ((s32)((u32)*(u8 *)(arg0 + 2) << 24) > 0) {
            i = 0;
            do {
                o = pp[i];
                s3 += 1;
                ((Fn4)(*(s32 *)(*(u8 **)o + 0x18)))((s32)o, 0, s1, (s32)sp);
                memset((void *)sp[0], 0, s1);
                o = pp[i];
                vt = *(u8 **)o;
                ((Fn3)(*(s32 *)(vt + 0x20)))((s32)o, 1, (s32)sp);
                i += 1;
            } while (s3 < (s32)*(s8 *)(arg0 + 2));
        }
        *(s32 *)(arg0 + 0xA0) = *(s32 *)(arg0 + 0xA0) - s4;
    }
}
