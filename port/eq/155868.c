#include "common.h"

s32 func_0014EFA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_001513D0(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);

void func_00155868(s32 arg0, u8 *arg1, u8 **arg2) {
    u8 *obj;
    u8 *s4;
    s32 s6;
    s32 i;
    s32 j;
    s32 fp;
    s32 flags;
    s32 r;

    i = 0;
    fp = 0;
    obj = *(u8 **)(arg1 + 0x38);
    s6 = *(s32 *)(obj + 0xA0);
    do {
        s4 = *arg2 + fp;
        j = 0;
        if (*s4 != 0) {
            do {
                if (!((i == 3) || ((i == 6) && (j == 1)) || (((i == 7) || (i == 10)) && (j == 0)))) {
                    flags = *(s32 *)obj;
                    r = func_0014EFA8(arg0, (s32)arg2, (s32)(obj + 0xA4), i, j, flags & 1, flags & 4);
                    if (r != 0) {
                        func_001513D0(*(f32 *)(obj + 0x14), s6, (s32)arg2, (s32)(obj + 0xA4),
                                      (s32)(obj + 0x850), (s32)(obj + 0x70), (s32)(obj + 0x20), i, j, j, r);
                    }
                }
                j += 1;
            } while (j < (s32)*s4);
        }
        i += 1;
        fp += 0x110;
    } while (i < 0x10);
}
