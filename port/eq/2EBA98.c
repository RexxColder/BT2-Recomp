#include "common.h"

void func_0030A430(s32 arg0, s32 arg1);
extern s32 D_003672D8 __attribute__((section(".data")));

void func_002EBA98(u8 *arg0) {
    u8 *p = *(u8 **)(arg0 + 8);

    if (p == NULL) {
        return;
    }
    if (*(s8 *)(arg0 + 2) != 0) {
        return;
    }
    if (D_003672D8 == 1) {
        func_0030A430(*(s32 *)(arg0 + 0x28), *(s32 *)(arg0 + 0x2C));
        p = *(u8 **)(arg0 + 8);
    }
    *(s32 *)(arg0 + 8) = 0;
    {
        void (*fn)(u8 *) = (void (*)(u8 *))*(u8 **)(*(u8 **)p + 0xC);

        fn(p);
    }
}
