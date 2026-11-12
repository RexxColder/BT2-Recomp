#include "common.h"

s32 *func_002B1DD0(s32 arg0);
extern u8 *D_00387E18;

s32 func_002ADF38(s32 arg0) {
    s32 i;

    if (D_00387E18 == NULL) {
        return 0;
    }
    if (*(s32 *)(D_00387E18 + 0) == 0) {
        return 0;
    }
    for (i = 0; i < *(s32 *)(D_00387E18 + 4); i++) {
        if (*func_002B1DD0(i) == arg0) {
            return 1;
        }
    }
    return 0;
}
