#include "common.h"

void func_002C7148(s32 arg0, s32 arg1);
s32 func_002DCE50(s32 arg0);

void func_002C7088(s32 arg0, s32 arg1) {
    s32 sp[4];
    u8 *obj;
    s32 vt;

    obj = (u8 *)arg1;
loop_3:
    vt = *(s32 *)obj;
    ((s32 (*)(s32, s32, s32, s32))(*(s32 *)((u8 *)vt + 0x18)))((s32)obj, 1, 4, (s32)sp);
    if ((sp[1] == 4) && (func_002DCE50(sp[0]) == 0x80)) {
        vt = *(s32 *)obj;
        ((s32 (*)(s32, s32, s32))(*(s32 *)((u8 *)vt + 0x20)))((s32)obj, 0, (s32)sp);
        func_002C7148(arg0, 4);
        goto loop_3;
    }
    vt = *(s32 *)obj;
    ((s32 (*)(s32, s32, s32))(*(s32 *)((u8 *)vt + 0x1C)))((s32)obj, 1, (s32)sp);
}
