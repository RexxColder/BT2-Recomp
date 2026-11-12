#include "common.h"

void func_002CB340(s32 arg0);
void func_0032EC70(s32 arg0);

s32 func_002CBD60(void *arg0) {
    func_002CB340(5);
    *(s32 *)0x1000B420 = 0;
    *(s32 *)0x1000B410 = 0;
    *(s32 *)0x1000B430 = 0;
    func_0032EC70(*(s32 *)((u8 *)arg0 + 0x40));
    return 1;
}
