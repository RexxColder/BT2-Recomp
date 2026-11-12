#include "common.h"

s32 func_002FA088(s32 arg0);

s32 func_002F2F70(s32 unused0, s32 *arg1) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = func_002FA088(unused0);
    temp_v1 = (s32)((temp_v0 < 0) ? (temp_v0 + 0x7FF) : temp_v0) >> 0xB;
    *arg1 = temp_v1;
    if ((temp_v0 - (temp_v1 << 0xB)) > 0) {
        *arg1 = temp_v1 + 1;
    }
    return 1;
}
