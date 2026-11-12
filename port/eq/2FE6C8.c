#include "common.h"

s32 strlen(s32 arg0);

s32 func_002FE6C8(u8 *arg0) {
    s32 v = 0;

    if (strlen((s32)arg0) == 0x11) {
        v = ((s8)arg0[8] == 0x2E);
    }
    return v;
}
