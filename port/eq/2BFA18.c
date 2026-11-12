#include "common.h"

s32 func_002BFAD8(void *a0, s32 a1, s32 a2, void *a3);
void func_002BFFF8(void *a0, void *a1, void *a2, s32 a3);
void func_002BFE48(void *a0, s32 a1, s32 a2);

s32 func_002BFA18(void *arg0, void *arg1, void *arg2, s32 arg3, void *arg4) {
    u8 *s0;
    u8 *s1;
    u8 *p1;
    u8 *p2;
    u8 buf[0x20];
    s32 v1;
    s32 v0;
    s32 s2;
    s32 s3;

    s0 = (u8 *)arg0 + 116 * arg3;
    s1 = s0 + 0x10;
    p1 = (u8 *)arg1 + 4 * arg3;
    p2 = (u8 *)arg2 + 4 * arg3;
    v1 = *(s32 *)p2;
    if (v1 != 0) {
        s3 = 1;
        s2 = 5;
        v0 = func_002BFAD8(buf, *(s32 *)p1, v1, arg4);
        if (v0 != 0) {
            return v0;
        }
        func_002BFFF8(s1, buf, s0, 1);
    } else {
        s3 = 0;
        s2 = 4;
    }
    func_002BFE48(s0, s2, s3);
    return 0;
}
