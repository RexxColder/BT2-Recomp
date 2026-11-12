#include "common.h"

s32 func_002BE660(s32 arg0, s32 arg1, s32 arg2);
s32 func_002BE6A8(s32 arg0, s32 arg1);
void func_002BE6C8(s32 arg0);

s32 func_002BDB98(u8 *arg0, s32 *arg1) {
    s32 sp[4];
    u8 *s1;
    s32 var;

    *arg1 = 0;
    s1 = *(u8 **)(arg0 + 0x2004);
    var = func_002BE660((s32)arg0, (s32)&sp[0], (s32)&sp[1]);
    if (var == 0) {
        *arg1 = sp[1];
        ((void (*)(s32, s32, s32, s32))(*(s32 *)(s1 + 0x3C)))((s32)arg0, sp[0], sp[1], (s32)&sp[2]);
        var = func_002BE6A8((s32)arg0, sp[2]);
        if (var == 0) {
            func_002BE6C8((s32)arg0);
            var = 0;
        }
    }
    return var;
}
