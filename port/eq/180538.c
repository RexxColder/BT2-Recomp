#include "common.h"

s32 func_00180538(u8 *arg0) {
    u8 *p = arg0;
    u8 *v = *(u8 **)p;
    s32 n = 0;

    for (;;) {
        p += 4;
        if (v != NULL && (*(s32 *)(*(u8 **)(v + 0x38) + 0x48) & 1)) {
            return 1;
        }
        n++;
        if (n >= 0x1E) {
            return 0;
        }
        v = *(u8 **)p;
    }
}
