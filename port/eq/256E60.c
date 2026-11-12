#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
extern u8 *D_003879F8;
extern u8 D_00376290 __attribute__((section(".data")));

void func_00256E60(void) {
    u8 frame[0x20];
    s32 i;

    memcpy(frame, &D_00376290, 0x14);
    for (i = 0; i < 5; i++) {
        u8 *a2 = D_003879F8;

        if (i < *(s32 *)(a2 + 0xB8)) {
            s32 idx = *(s32 *)(frame + 4 * i);
            u8 *ent = *(u8 **)(a2 + 0x118) + 16 * i;
            u8 *base = *(u8 **)(a2 + 8);
            u32 w = *(u32 *)(base + 4 * *(s32 *)(ent + 8) + 4);
            u8 *p2 = base + (w & ~3u);

            *(s32 *)(a2 + 4 * idx + 0x44) = *(s32 *)(p2 + 0x10);
        }
    }
}
