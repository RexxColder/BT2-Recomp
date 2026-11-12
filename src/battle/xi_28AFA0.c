#include "m2c_macros.h"

s32 func_0028BAA8(M2C_UNK);                         /* extern */
extern u8 D_00387EB0;
extern s8 D_00387EB1;
extern M2C_UNK D_0038A628 __attribute__((section(".data")));
extern s32 gDmaCur;

// Sets toggle EB0=0 and EB1=0, allocates four buffers via func_0028BAA8 (1 MB, 1 MB, 1 KB, 1 KB), and sets gDmaCur to buffer 0.
void func_0028AFA0(void) {
    D_00387EB0 = 0;
    D_00387EB1 = 0;
    M2C_FIELD(&D_0038A628, s32 *, 0) = func_0028BAA8(0x100000);
    M2C_FIELD(&D_0038A628, s32 *, 4) = func_0028BAA8(0x100000);
    M2C_FIELD(&D_0038A628, s32 *, 8) = func_0028BAA8(0x400);
    M2C_FIELD(&D_0038A628, s32 *, 0xC) = func_0028BAA8(0x400);
    gDmaCur = ((s32 *)&D_0038A628)[D_00387EB0];
}
