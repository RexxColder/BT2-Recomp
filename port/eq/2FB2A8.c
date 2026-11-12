#include "common.h"

void func_002F9B38(void *arg0, void *arg1, s32 arg2);
void *func_002F98F0(void *arg0, void *arg1, s32 arg2);

s64 func_002FB2A8(s32 arg0) {
    s32 buf[160];
    void *sp;
    u8 *s3;
    u8 *s2;
    s64 s0;
    u64 hi;

    sp = buf;
    s3 = (u8 *)buf + 0x130;
    s0 = 0;
    func_002F9B38(sp, s3, arg0);
    s2 = (u8 *)func_002F98F0(sp, s3, arg0);
    if (*(s64 (**)(s32, s32, void *, s32))(s2 + 0x60) != NULL) {
        s0 = (*(s64 (**)(s32, s32, void *, s32))(s2 + 0x60))(arg0, 0xCA, s3, 0);
        hi = (u64)s0 << 32;
        s0 = (s64)hi;
        hi = (u64)(*(s64 (**)(s32, s32, void *, s32))(s2 + 0x60))(arg0, 0xCB, s3, 0);
        s0 = s0 + (s64)(hi & 0xFFFFFFFFULL);
    }
    return s0;
}
