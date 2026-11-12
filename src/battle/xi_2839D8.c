#include "m2c_macros.h"

M2C_UNK func_003126C8(void *);                      /* extern */
extern u8 gGfxLens __attribute__((section(".data")));

// Lens entry setter: if index < 8, calls func_003126C8 on the 0x30-byte entry gGfxLens[index].
void GfxLens_SetPos(u32 arg0) {
    if (arg0 < 8U) {
        func_003126C8((u8 *)&gGfxLens + (arg0 * 0x30));
    }
}
