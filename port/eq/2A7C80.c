#include "common.h"

extern u8 D_003B26B0[];
s32 Gsc_GetInt(void);
s32 func_002A0010(s32 arg0);

s32 func_002A7C80(s32 arg0) {
    if (arg0 == 0) {
        s32 g = Gsc_GetInt();

        *(s32 *)(D_003B26B0 + 0x300) = g;
        if (func_002A0010(0x6F) != 0) {
            *(s32 *)(D_003B26B0 + 0x304) = 1;
        }
    }
    return 1;
}
