#include "common.h"

void func_002C9890(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3);
void func_002C9A08(void *arg0, void *arg1);
void *memcpy(void *arg0, void *arg1, u32 arg2);

void func_002C97E8(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 sp[3];
    s32 temp_s2;

    temp_s2 = *(s32 *)(arg0 + 0x1FC0);
    if ((u32)(*(s32 *)(arg1 + 0x74) - 1) < 2U) {
        func_002C9A08((void *)(temp_s2 + 0x1094), *(void **)(arg1 + 0x54));
    }
    func_002C9890(arg2, sp, &sp[1], &sp[2]);
    if (sp[0] == 3) {
        memcpy(*(void **)(*(u8 **)(arg1 + 0x54) + 0), (void *)sp[1], (u32)sp[2]);
        *(s32 *)(*(u8 **)(arg1 + 0x54) + 4) = sp[2];
        return;
    }
    func_002C9A08(*(void **)(arg1 + 0x54), (void *)(temp_s2 + 0x1094));
}
