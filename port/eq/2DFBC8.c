#include "common.h"

s32 func_002DCE50(s32 arg0);
s32 func_002DCFE8(s32 arg0, s32 arg1, s32 arg2);
void func_003061A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* vtable slots: obj->vt[off] */
#define VT3(obj, off) ((s32 (*)(s32, s32, s32))(*(s32 *)((*(s32 *)(obj)) + (off))))
#define VT4(obj, off) ((s32 (*)(s32, s32, s32, s32))(*(s32 *)((*(s32 *)(obj)) + (off))))

s32 func_002DFBC8(s32 arg0) {
    u8 buf[0x20];
    u8 *sp;
    u8 *sp10;
    s32 count;
    s32 s1;
    s32 s2;

    sp = buf;
    sp10 = buf + 0x10;
    s2 = 0;
    for (;;) {
        VT4(arg0, 0x18)(arg0, 1, 0x7FFFFFFF, (s32)sp);
        count = *(s32 *)(sp + 4);
        if (count < 4) {
            VT3(arg0, 0x1C)(arg0, 1, (s32)sp);
            return 0;
        }
        s1 = func_002DCFE8(*(s32 *)sp, count, -1);
        if (s1 == 0) {
            func_003061A8((s32)sp, count - 3, (s32)sp, (s32)sp10);
            VT3(arg0, 0x20)(arg0, 0, (s32)sp);
            VT3(arg0, 0x1C)(arg0, 1, (s32)sp10);
            continue;
        }
        s2 = func_002DCE50(s1);
        func_003061A8((s32)sp, s1 - *(s32 *)sp, (s32)sp, (s32)sp10);
        VT3(arg0, 0x20)(arg0, 0, (s32)sp);
        VT3(arg0, 0x1C)(arg0, 1, (s32)sp10);
        return s2;
    }
}
