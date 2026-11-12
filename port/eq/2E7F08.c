#include "common.h"

extern void (*D_00347BE8)(u8 *a0) __attribute__((section(".data")));
void func_002F8ED8(s32 arg0);

void func_002E7F08(u8 *arg0) {
    if (*(s32 *)(arg0 + 0xE8) != 0) {
        D_00347BE8(arg0);
    }
    func_002F8ED8(*(s32 *)(arg0 + 8));
    *(s32 *)(arg0 + 4) = 0;
}
