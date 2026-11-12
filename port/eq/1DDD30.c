#include "common.h"

void func_00129C38(void *arg0, void *arg1, void *arg2);
extern s32 func_001DDA10[] __attribute__((section(".data")));

#ifdef __mips__
#define GEYSER_IS_UPDATE(p) ((void *)(p) == (void *)func_001DDA10)
#else
#define GEYSER_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001DDA10u)
#endif

s32 func_001DDD30(void *arg0, void *arg1) {
    void *temp_a2;

    if (arg0 != NULL && GEYSER_IS_UPDATE(*(void **)*(u8 **)((u8 *)arg0 + 0x28))) {
        temp_a2 = *(void **)((u8 *)arg0 + 0x38);
        if (*(s32 *)((u8 *)temp_a2 + 0x40) & 1) {
            func_00129C38((u8 *)temp_a2 + 0x20, arg1, temp_a2);
            return 1;
        }
    }
    return 0;
}
