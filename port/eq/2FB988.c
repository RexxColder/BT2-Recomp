#include "common.h"

s32 func_002FC550(s32 arg0);
s32 sceCdStatus(void);
extern s32 D_003553B4 __attribute__((section(".data")));
extern s32 D_003553B8 __attribute__((section(".data")));

void func_002FB988(void) {
    D_003553B8 = 1;
    func_002FC550(0x2600);
    D_003553B4 = sceCdStatus();
    func_002FC550(0x2601);
    D_003553B8 = 0;
}
