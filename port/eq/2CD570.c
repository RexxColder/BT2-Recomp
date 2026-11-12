#include "common.h"

s32 func_002CD650(u8 *arg0);
s32 func_002CDB38(u8 *arg0);

s32 func_002CD570(u8 *arg0) {
    s32 a1;

    if (func_002CDB38(arg0) != 0) {
        return *(s32 *)(arg0 + 0x48);
    }
    if (func_002CD650(arg0) != 0) {
        return *(s32 *)(arg0 + 0x48);
    }
    a1 = *(s32 *)(arg0 + 0x4C);
    if (a1 == 6) {
        return 6;
    }
    return *(s32 *)(arg0 + 0x48);
}
