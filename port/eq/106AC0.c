#include "common.h"

u8 *func_00106AC0(u8 *arg0, s32 arg1);

u8 *func_00106AC0(u8 *arg0, s32 arg1) {
    s32 i;
    u8 *ent;
    u8 *child;
    u8 *found;

    found = NULL;
    i = 0;
    while (i < *(s32 *)(arg0 + 0x4)) {
        ent = *(u8 **)(arg0 + 0x0) + (i << 5);
        i += 1;
        if (arg1 == *(s32 *)(ent + 0x4)) {
            return arg0;
        }
        child = *(u8 **)(ent + 0x8);
        if (child != NULL) {
            found = func_00106AC0(child, arg1);
            if (found != NULL) {
                return found;
            }
        }
    }
    return found;
}
