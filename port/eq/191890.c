#include "common.h"

extern u8 func_00191238[] __attribute__((section(".data")));

#ifdef __mips__
#define BLAST_IS_UPDATE(p) ((void *)(p) == (void *)func_00191238)
#else
#define BLAST_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x00191238u)
#endif

s32 func_00191890(u8 *arg0, s32 arg1) {
    u8 *obj;
    s32 flags;
    s32 ret;

    ret = 0;
    if (arg0 != NULL && BLAST_IS_UPDATE(*(void **)*(u8 **)(arg0 + 0x28))) {
        obj = *(u8 **)(arg0 + 0x38);
        flags = *(s32 *)(obj + 0x30);
        if (flags & 1) {
            if ((arg1 & 0xFF) == 0) {
                flags = flags & ~0x40;
            } else {
                flags = flags | 0x40;
            }
            *(s32 *)(obj + 0x30) = flags;
            ret = 1;
        }
    }
    return ret;
}
