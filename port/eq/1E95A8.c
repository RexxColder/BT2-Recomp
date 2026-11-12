#include "common.h"

void func_001EA4B0(void *arg0, void *arg1, void *arg2);

void func_001E95A8(u8 *arg0) {
    u8 *obj;
    u8 *p;

    obj = *(u8 **)(arg0 + 0x38);
    p = *(u8 **)(obj + 0x180);
    if (p != NULL) {
        *(s16 *)(p + 0x14) = 0;
        for (;;) {
            func_001EA4B0(obj + 0x180, obj + 0x184, p);
            p = *(u8 **)(p + 0x18);
            if (p == NULL) {
                break;
            }
            *(s16 *)(p + 0x14) = 0;
        }
    }
}
