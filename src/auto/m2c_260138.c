#include "m2c_macros.h"

M2C_UNK sceVu0ApplyMatrix(void *, s32, void *);     /* extern */
M2C_UNK sceVu0CopyMatrix(s32);                      /* extern */

void ColObb_Update(void *arg0) {
    s32 temp_s1;

    temp_s1 = arg0 + 0x50;
    sceVu0CopyMatrix(temp_s1);
    M2C_FIELD(arg0, f32 *, 0x20) = (f32) M2C_FIELD(arg0, f32 *, 0x50);
    M2C_FIELD(arg0, f32 *, 0x24) = (f32) M2C_FIELD(arg0, f32 *, 0x54);
    M2C_FIELD(arg0, f32 *, 0x28) = (f32) M2C_FIELD(arg0, f32 *, 0x58);
    M2C_FIELD(arg0, f32 *, 0x30) = (f32) M2C_FIELD(arg0, f32 *, 0x60);
    M2C_FIELD(arg0, f32 *, 0x34) = (f32) M2C_FIELD(arg0, f32 *, 0x64);
    M2C_FIELD(arg0, f32 *, 0x38) = (f32) M2C_FIELD(arg0, f32 *, 0x68);
    M2C_FIELD(arg0, f32 *, 0x40) = (f32) M2C_FIELD(arg0, f32 *, 0x70);
    M2C_FIELD(arg0, f32 *, 0x44) = (f32) M2C_FIELD(arg0, f32 *, 0x74);
    M2C_FIELD(arg0, f32 *, 0x48) = (f32) M2C_FIELD(arg0, f32 *, 0x78);
    M2C_FIELD(arg0, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0x80);
    M2C_FIELD(arg0, f32 *, 4) = (f32) M2C_FIELD(arg0, f32 *, 0x84);
    M2C_FIELD(arg0, f32 *, 8) = (f32) M2C_FIELD(arg0, f32 *, 0x88);
    sceVu0ApplyMatrix(arg0 + 0x110, temp_s1, arg0 + 0x90);
    sceVu0ApplyMatrix(arg0 + 0x120, temp_s1, arg0 + 0xA0);
    sceVu0ApplyMatrix(arg0 + 0x130, temp_s1, arg0 + 0xB0);
    sceVu0ApplyMatrix(arg0 + 0x140, temp_s1, arg0 + 0xC0);
    sceVu0ApplyMatrix(arg0 + 0x150, temp_s1, arg0 + 0xD0);
    sceVu0ApplyMatrix(arg0 + 0x160, temp_s1, arg0 + 0xE0);
    sceVu0ApplyMatrix(arg0 + 0x170, temp_s1, arg0 + 0xF0);
    sceVu0ApplyMatrix(arg0 + 0x180, temp_s1, arg0 + 0x100);
}
