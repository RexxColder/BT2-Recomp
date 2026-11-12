#include "common.h"

void EftPtcl3_PickTexture(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 EftPtcl3_Update[] __attribute__((section(".data")));

s32 EftPtcl3_SetTexture(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_t0;

    if (arg0 != NULL) {
        if (**(s32 **)((u8 *)arg0 + 0x28) == 0x001BC188 /* PS2 address of EftPtcl3_Update */) {
            temp_t0 = *(void **)((u8 *)arg0 + 0x38);
            if (*(s32 *)((u8 *)temp_t0 + 0x60) & 1) {
                EftPtcl3_PickTexture(temp_t0, arg1, arg2, arg3);
                return 1;
            }
        }
    }
    return 0;
}
