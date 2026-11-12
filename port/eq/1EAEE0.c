#include "m2c_macros.h"

extern M2C_UNK func_001E9428 __attribute__((section(".data")));

#ifdef __mips__
#define STEAM_IS_UPDATE(p) ((void *)(p) == (void *)&func_001E9428)
#else
#define STEAM_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001E9428u)
#endif

void func_001EAEE0(void *arg0, f32 farg0) {
    u8 *temp;

    if (arg0 != NULL && STEAM_IS_UPDATE(*(void **)*(u8 **)((u8 *)arg0 + 0x28))) {
        temp = *(u8 **)((u8 *)arg0 + 0x38);
        if (*(u16 *)(temp + 0x124) & 1) {
            *(f32 *)(temp + 0xC4) = farg0;
        }
    }
}
