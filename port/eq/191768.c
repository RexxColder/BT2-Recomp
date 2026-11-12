#include "m2c_macros.h"

extern M2C_UNK func_00191238 __attribute__((section(".data")));

#ifdef __mips__
#define BLAST_IS_UPDATE(p) ((void *)(p) == (void *)&func_00191238)
#else
#define BLAST_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x00191238u)
#endif

s32 func_00191768(void *arg0) {
    s32 temp_a0;
    s32 var_v0 = 0;
    u8 *temp;

    if (arg0 != NULL && BLAST_IS_UPDATE(*(void **)*(u8 **)((u8 *)arg0 + 0x28))) {
        temp = *(u8 **)((u8 *)arg0 + 0x38);
        temp_a0 = *(s32 *)(temp + 0x30);
        if (temp_a0 & 1) {
            var_v0 = (temp_a0 & 4) != 0;
        }
    }
    return var_v0;
}
