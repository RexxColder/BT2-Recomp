#include "common.h"

s32 func_002F3280(s32 arg0);

s32 func_002F8BA8(u8 *arg0) {
    s32 t;
    u8 *a;
    s32 v;

    if (arg0 == NULL) {
        return 0;
    }
    t = *(s32 *)(arg0 + 0x8);
    if (t != 0) {
        return func_002F3280(t);
    }
    a = *(u8 **)(arg0 + 0x94);
    if (a == NULL) {
        return 0;
    }
    v = *(s32 *)(a + 0x28);
    if (v == 0) {
        return 0;
    }
    return func_002F3280(v);
}
