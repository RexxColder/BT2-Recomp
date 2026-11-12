#include "common.h"

void func_001A2308(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 func_001A45B0[] __attribute__((section(".data")));

#ifdef __mips__
#define BLAST_IS_UPDATE(p) ((void *)(p) == (void *)func_001A45B0)
#else
#define BLAST_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001A45B0u)
#endif

s32 func_001A4AC8(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *temp_t1;

    if (arg0 != NULL) {
        if (BLAST_IS_UPDATE(*(void **)*(u8 **)((u8 *)arg0 + 0x28))) {
            temp_t1 = *(void **)((u8 *)arg0 + 0x38);
            if (*(s32 *)((u8 *)temp_t1 + 0x50) & 1) {
                func_001A2308(temp_t1, arg1, arg2, arg3, arg4);
                return 1;
            }
        }
    }
    return 0;
}
