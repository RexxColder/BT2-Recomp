#include "common.h"

void func_002568D8(void);
s32 func_0026EB70(u8 *arg0);
extern u8 *D_003879E8;

s32 func_00256DD0(void) {
    s32 v;

    if (D_003879E8 == NULL) {
        return 0;
    }
    if (*(s32 *)(D_003879E8 + 0x5C) == 0) {
        return 0;
    }
    if (func_0026EB70(D_003879E8 + 4) & 0x200) {
        if (*(s32 *)(D_003879E8 + 0x60) != 0) {
            *(s32 *)(D_003879E8 + 0x4C) = *(s32 *)(D_003879E8 + 0x4C) | 4;
            v = *(s32 *)(D_003879E8 + 0x4C) & ~2;
        } else {
            v = *(s32 *)(D_003879E8 + 0x4C) | 1;
        }
        *(s32 *)(D_003879E8 + 0x4C) = v;
    }
    func_002568D8();
    return (*(s32 *)(D_003879E8 + 0x4C) & 4) != 0;
}
