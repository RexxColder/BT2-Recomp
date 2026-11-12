#include "common.h"

s32 Gsc_GetInt(void);
extern u8 D_003B26B0[] __attribute__((section(".data")));

s32 func_002A7CD0(s32 arg0) {
    if (arg0 == 0) {
        *(s32 *)(D_003B26B0 + 0x24) = Gsc_GetInt();
        *(s32 *)(D_003B26B0 + 0x28) = Gsc_GetInt();
        *(s32 *)(D_003B26B0 + 0x2C) = Gsc_GetInt();
    }
    return 1;
}
