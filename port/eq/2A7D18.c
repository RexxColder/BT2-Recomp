#include "common.h"

s32 Gsc_GetInt(void);
extern u8 D_003B26B0[] __attribute__((section(".data")));

s32 func_002A7D18(s32 arg0) {
    if (arg0 == 0) {
        *(s32 *)(D_003B26B0 + 4) = 4;
        *(s32 *)(D_003B26B0 + 8) = Gsc_GetInt();
    }
    return 1;
}
