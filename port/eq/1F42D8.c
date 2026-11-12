#include "common.h"

extern u8 *D_00387920;

s32 func_001F42D8(s32 arg0) {
    s32 result = 0;
    if (D_00387920 != NULL) {
        result = *(s32 *)(D_00387920 + arg0 * 4 + 0x30);
    }
    return result;
}
