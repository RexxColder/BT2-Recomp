#include "m2c_macros.h"

extern M2C_UNK func_001DDA10 __attribute__((section(".data")));

#ifdef __mips__
#define GEYSER_IS_UPDATE(p) ((void *)(p) == (void *)&func_001DDA10)
#else
#define GEYSER_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001DDA10u)
#endif

s32 func_001DDCF0(void *arg0) {
    s32 var_v0 = 0;
    s32 *obj;
    s32 temp;

    if (arg0 != NULL) {
        obj = *(s32 **)((u8 *)arg0 + 0x28);
        if (GEYSER_IS_UPDATE(*(void **)obj)) {
            temp = *(s32 *)(*(u8 **)((u8 *)arg0 + 0x38) + 0x40);
            var_v0 = (temp & 1) ? (temp != 0) : 0;
        }
    }
    return var_v0;
}
