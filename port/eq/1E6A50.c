#include "common.h"

s32 func_001DFC78(s32 arg0);
s32 func_001E0990(s32 arg0);

void func_001E6A50(s32 arg0) {
    s32 temp_v0;

    if ((*(s32 *)arg0 & 4) == 0) {
        switch (*(s32 *)(arg0 + 8)) {
        case 0:
            temp_v0 = func_001DFC78(*(s32 *)(arg0 + 0x40));
            break;
        case 1:
            temp_v0 = func_001E0990(*(s32 *)(arg0 + 0x44));
            break;
        default:
            return;
        }
        if (temp_v0 == 0) {
            *(s32 *)arg0 = *(s32 *)arg0 | 4;
        }
    }
}
