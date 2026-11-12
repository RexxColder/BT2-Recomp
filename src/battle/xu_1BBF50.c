#include "common.h"
void func_001BB928(s32 arg0, s32 arg1, s32 arg2, s64 arg3, f32 farg0, f32 farg1);
void func_001BBF50(s32 arg0) {
    u8 *s0;
    u8 *t;
    s0 = *(u8 **)arg0;
    if (s0 != NULL) {
        do {
            func_001BB928(arg0, (s32)s0, (s32)(s0 + 0xA0), *(s64 *)(arg0 + 0x280), *(f32 *)(s0 + 0x40), *(f32 *)(s0 + 0x40));
            t = *(u8 **)(s0 + 0x120);
            s0 = t;
        } while (t != NULL);
    }
}
