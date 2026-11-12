#include "common.h"

s32 Gsc_GetInt(void);
s32 func_002A4E38(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8, s32 arg9, s32 arg10);

s32 func_002A6E68(s32 arg0) {
    u8 *temp_s0;

    if (arg0 == 0) {
        temp_s0 = (u8 *)func_002A4E38(0x21, 1, 0, 0, 0x200, 0x1C0, 0, 0, 0, 0x80, 0);
        if (Gsc_GetInt() != 0) {
            *(s8 *)(temp_s0 + 0x18) = 0;
        }
    }
    return 1;
}
