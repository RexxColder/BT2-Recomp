#include "common.h"

void func_001DD1E8(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_001DDA10[] __attribute__((section(".data")));

#ifdef __mips__
#define GEYSER_IS_UPDATE(p) ((void *)(p) == (void *)func_001DDA10)
#else
#define GEYSER_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001DDA10u)
#endif

s32 func_001DDDF8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_t0;

    if (arg0 != NULL) {
        if (GEYSER_IS_UPDATE(*(void **)*(u8 **)((u8 *)arg0 + 0x28))) {
            temp_t0 = *(void **)((u8 *)arg0 + 0x38);
            if (*(s32 *)((u8 *)temp_t0 + 0x40) & 1) {
                func_001DD1E8(temp_t0, arg1, arg2, arg3);
                return 1;
            }
        }
    }
    return 0;
}
