#include "common.h"

void func_00195E70(void);

#ifdef __mips__
#define BLAST_IS_UPDATE(p) ((void *)(p) == (void *)func_00195E70)
#else
#define BLAST_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x00195E70u)
#endif

s32 func_00195A58(u8 *arg0) {
    u8 *v1;

    if (arg0 == NULL) {
        return 0;
    }
    v1 = *(u8 **)(arg0 + 0x28);
    if (!BLAST_IS_UPDATE(*(void **)v1)) {
        return 0;
    }
    return (*(u8 *)arg0 & 1) ^ 1;
}
