#include "common.h"

s32 func_002DDD70(s32 arg0, s32 arg1);
extern s32 D_0037B070 __attribute__((section(".data")));
extern u8 D_0037B080 __attribute__((section(".data")));

s32 func_002DFFD8(void) {
    if (D_0037B070 != 0x5A5A5A5A) {
        return func_002DDD70(0, 0xFF03FF02);
    }
    if (D_0037B080 != 4) {
        for (;;) {
            ((void (*)(void))(s32)-1)();
        }
    }
    return 0;
}
