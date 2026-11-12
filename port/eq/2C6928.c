#include "common.h"

#define FLD(p, off) (*(s32 *)((u8 *)(p) + (off)))

s32 func_002DCE50(void *arg0);
s32 func_002DCEE8(s32 arg0, s32 arg1, s32 arg2);

s32 func_002C6928(void *arg0, s32 arg1, s32 *arg2) {
    u8 buf[16];
    s32 s0, s0c, s1, s3, s3c, lim, i, r;

    *arg2 = 0;
    s0 = FLD(arg0, 0xC);
    if (s0 != 0) {
        s1 = func_002DCEE8(FLD(arg0, 8) + s0, s0, arg1);
        if (s1 == 0) {
            s3 = FLD(arg0, 4);
            s3c = (s3 >= 4) ? 3 : s3;
            s0c = (s0 >= 4) ? 3 : s0;
            memcpy(buf, (void *)(FLD(arg0, 0) + s3 - s3c), s3c);
            lim = (s3c + s0c) - 3;
            memcpy(buf + s3c, (void *)FLD(arg0, 8), s0c);
            i = 0;
            if (0 < lim) {
                do {
                    r = func_002DCE50(buf + i);
                    if (r & arg1) {
                        *arg2 = r;
                        return FLD(arg0, 0) + FLD(arg0, 4) - s3c + i;
                    }
                    i++;
                } while (i < lim);
            }
        } else {
            *arg2 = func_002DCE50((void *)s1);
            return s1;
        }
    }
    s3 = FLD(arg0, 4);
    s1 = func_002DCEE8(FLD(arg0, 0) + s3, s3, arg1);
    if (s1 != 0) {
        *arg2 = func_002DCE50((void *)s1);
    }
    return s1;
}
