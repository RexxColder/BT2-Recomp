#include "m2c_macros.h"

void func_002BC7D0(s32 arg0, s32 arg1);
void func_002BC920(s32 arg0, s32 arg1);

void func_002BC790(void *arg0) {
    if (*(s32 *)((u8 *)arg0 + 0x284) == 1 || *(s32 *)((u8 *)arg0 + 0x2A4) == 1) {
        func_002BC7D0((s32)arg0, 1);
        return;
    }
    func_002BC920((s32)arg0, 1);
}
