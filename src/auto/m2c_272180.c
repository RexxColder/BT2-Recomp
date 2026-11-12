#include "m2c_macros.h"

M2C_UNK sceVu0ApplyMatrix(s32, s32, s32);           /* extern */
M2C_UNK sceVu0CopyMatrix(s32);                      /* extern */

void func_00272180(s32 arg0) {
    s32 temp_s1;

    temp_s1 = arg0 + 0x50;
    sceVu0CopyMatrix(temp_s1);
    sceVu0ApplyMatrix(arg0 + 0x110, temp_s1, arg0 + 0x90);
    sceVu0ApplyMatrix(arg0 + 0x120, temp_s1, arg0 + 0xA0);
    sceVu0ApplyMatrix(arg0 + 0x130, temp_s1, arg0 + 0xB0);
    sceVu0ApplyMatrix(arg0 + 0x140, temp_s1, arg0 + 0xC0);
    sceVu0ApplyMatrix(arg0 + 0x150, temp_s1, arg0 + 0xD0);
    sceVu0ApplyMatrix(arg0 + 0x160, temp_s1, arg0 + 0xE0);
    sceVu0ApplyMatrix(arg0 + 0x170, temp_s1, arg0 + 0xF0);
    sceVu0ApplyMatrix(arg0 + 0x180, temp_s1, arg0 + 0x100);
}
