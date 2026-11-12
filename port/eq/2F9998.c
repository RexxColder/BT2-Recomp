#include "common.h"

extern s32 D_0037D1E8 __attribute__((section(".data")));
extern s32 D_0037D208 __attribute__((section(".data")));
extern s32 D_0037D250 __attribute__((section(".data")));
extern s32 D_0037D270 __attribute__((section(".data")));
extern s32 D_0037D288 __attribute__((section(".data")));

void func_002F9300(s32 arg0);
s32 func_002F9AC0();
s32 func_002F98F0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002F9B28(s32 arg0);
void func_002F9B38(s32 arg0, s32 arg1, s32 arg2);

/* 0x002F9998: opens a handle for arg0 (a name or path, 0 = fail). A 0x130-byte probe block is
 * filled by func_002F9B38; when its first byte is 0 the call fails with a message. Otherwise a
 * new record s0 comes from func_002F9AC0 and is initialised by func_002F98F0. When that record's
 * dispatch pointer (+0x10) is set, it is called with (frame block, arg1, arg2) and its result is
 * kept at s0+4. Failures report a message through func_002F9300 and return 0; success returns s0. */
s32 func_002F9998(s32 arg0, s32 arg1, s32 arg2) {
    u8 frame[0x260];   /* tamano de locales del original (antes 0x200) */
    u8 *s2 = frame + 0x130;
    u8 *s0;
    s32 ret;
    s32 fn;

    if (arg0 == 0) {
        func_002F9300((s32)&D_0037D1E8);
        return 0;
    }

    func_002F9B38((s32)frame, (s32)s2, arg0);
    if (*(s8 *)s2 == 0) {
        func_002F9300((s32)&D_0037D1E8);
        return 0;
    }

    s0 = (u8 *)(s32)func_002F9AC0();
    if (s0 == NULL) {
        func_002F9300((s32)&D_0037D208);
        return 0;
    }

    ret = func_002F98F0((s32)frame, (s32)s2, arg0);
    *(s32 *)s0 = ret;
    if (ret == 0) {
        func_002F9B28((s32)s0);
        func_002F9300((s32)&D_0037D250);
        return 0;
    }

    fn = *(s32 *)((u8 *)(s32)ret + 0x10);
    if (fn == 0) {
        func_002F9B28((s32)s0);
        func_002F9300((s32)&D_0037D270);
        return 0;
    }

    *(s32 *)(s0 + 0x4) = ((s32 (*)(s32, s32, s32))fn)((s32)s2, arg1, arg2);
    if (*(s32 *)(s0 + 0x4) != 0) {
        return (s32)s0;
    }
    func_002F9B28((s32)s0);
    func_002F9300((s32)&D_0037D288);
    return 0;
}
