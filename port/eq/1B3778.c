#include "common.h"

void EftChain2_SetTex(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 EftChain2_Update[] __attribute__((section(".data")));

s32 EftChain2_SetRes(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_t0;

    if (arg0 != NULL) {
        if (**(s32 **)((u8 *)arg0 + 0x28) == 0x001B2FD0 /* PS2 address of (void *)0x001B2FD0u */) {
            temp_t0 = *(void **)((u8 *)arg0 + 0x38);
            if (*(s32 *)((u8 *)temp_t0 + 0xA40) & 1) {
                EftChain2_SetTex(temp_t0, arg1, arg2, arg3);
                return 1;
            }
        }
    }
    return 0;
}
