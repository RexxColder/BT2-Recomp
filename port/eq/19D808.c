#include "common.h"

void func_0019C868(void);

#ifdef __mips__
#define BLAST_IS_UPDATE(p) ((void *)(p) == (void *)func_0019C868)
#else
#define BLAST_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x0019C868u)
#endif

s32 func_0019D808(u8 *arg0) {
    u8 *v1;

    if (arg0 == NULL) {
        return 0;
    }
    v1 = *(u8 **)(arg0 + 0x28);
    if (!BLAST_IS_UPDATE(*(void **)v1)) {
        return 0;
    }
    v1 = *(u8 **)(arg0 + 0x38);
    return (*(u16 *)(v1 + 0xC24) & 0x8) == 0;
}
