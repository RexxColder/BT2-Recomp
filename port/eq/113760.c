#include "common.h"

void func_00113620(s32 *arg0, s32 arg1);

void func_00113760(s32 *arg0, s32 arg1) {
    s32 *p;

    if (!(*arg0 & 2)) {
        p = arg0;
        do {
            if (*p & 1) {
                func_00113620(p, arg1);
            }
            p = (s32 *)((u8 *)p + 0x60);
        } while (!(*p & 2));
    }
}
