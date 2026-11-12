#include "common.h"

void EftRibbon_SetTexPair(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 EftRibbon_Update[] __attribute__((section(".data")));

s32 EftRibbon_SetTexFrame(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *temp_t1;

    if (arg0 != NULL) {
        if (**(s32 **)((u8 *)arg0 + 0x28) == 0x001C6E40 /* PS2 address of EftRibbon_Update */) {
            temp_t1 = *(void **)((u8 *)arg0 + 0x38);
            if (*(s32 *)((u8 *)temp_t1 + 0x50) & 1) {
                EftRibbon_SetTexPair(temp_t1, arg1, arg2, arg3, arg4);
                return 1;
            }
        }
    }
    return 0;
}
