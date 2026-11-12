#include "common.h"

s32 func_002FC550(s32 arg0);
s32 sceCdSync(s32 arg0);
void func_00306F28(void);
void func_00306FA0(void);
extern void *memcpy(void *dst, const void *src, u32 n);

/* 0x002FB678: func_002FC550(0x1200), sceCdSync(1), s0 = func_002FC550(0x1201); s0 == 1 -> return 0. Else func_00306F28();
 * if obj+2 (signed byte) is 0, 3 or 9: obj+2 = obj+1 = 1, result 1, obj+8 = arg1, obj+0x14 = 4 bytes at arg4,
 * obj+0xC = arg2, obj+0x10 = arg3, obj+4 = 0. Then func_00306FA0() and return the result. */
s32 func_002FB678(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4) {
    s32 s4;
    s32 s0;
    s32 v;

    s4 = 0;
    func_002FC550(0x1200);
    sceCdSync(1);
    s0 = func_002FC550(0x1201);
    if (s0 == 1) {
        return 0;
    }
    func_00306F28();
    v = *(signed char *)(arg0 + 2);
    if (v == 0 || v == 3 || v == 9) {
        arg0[2] = 1;
        s4 = 1;
        arg0[1] = 1;
        *(s32 *)(arg0 + 8) = arg1;
        memcpy(arg0 + 0x14, arg4, 4);
        *(s32 *)(arg0 + 0xC) = arg2;
        *(s32 *)(arg0 + 0x10) = arg3;
        *(s32 *)(arg0 + 4) = 0;
    }
    func_00306FA0();
    return s4;
}
