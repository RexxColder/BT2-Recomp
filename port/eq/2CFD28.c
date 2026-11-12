#include "common.h"

void func_002CF9A0(s32 arg0, s32 arg1);

void func_002CFD28(u8 *arg0, s32 *arg1) {
    s32 sp[4];

    *arg1 = 0;
    if (arg0 != NULL) {
        func_002CF9A0((s32)arg0, (s32)sp);
        if (sp[0] != 0) {
            if ((*(s32 *)(arg0 + 0xDC0) != 0) || (*(s32 *)(arg0 + 0xDA8) > 0)) {
                *arg1 = 1;
            }
        }
    }
}
