#include "m2c_macros.h"

extern M2C_UNK func_001EB270 __attribute__((section(".data")));

#ifdef __mips__
#define LOOP_IS_UPDATE(p) ((void *)(p) == (void *)&func_001EB270)
#else
#define LOOP_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001EB270u)
#endif

s32 func_001EBC30(void *arg0) {
    s32 var_v0 = 0;
    u8 *temp;

    if (arg0 != NULL && LOOP_IS_UPDATE(*(void **)*(u8 **)((u8 *)arg0 + 0x28))) {
        temp = *(u8 **)((u8 *)arg0 + 0x38);
        if (temp != NULL) {
            var_v0 = *(u16 *)(temp + 0x60) & 1;
        }
    }
    return var_v0;
}
