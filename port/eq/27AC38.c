#include "common.h"

extern s32 **D_00387AEC;

s32 *func_0027AC38(void) {
    s32 *base;
    s32 *found;
    s32 a1;
    s32 *elem;

    found = NULL;
    base = *D_00387AEC;
    if (*base == 0) {
        return base;
    }
    a1 = 1;
    while (a1 < 0xA) {
        elem = (s32 *)((u8 *)*D_00387AEC + a1 * 0x460);
        if (*elem == 0) {
            found = elem;
            break;
        }
        a1 += 1;
    }
    return found;
}
