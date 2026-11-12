#include "common.h"

void func_00312650(u8 *arg0, u8 *arg1, u8 *arg2);
void sceVu0Normalize(u8 *arg0, u8 *arg1);
void func_003126C8(u8 *arg0, u8 *arg1);

void ColCapsule_GetLongSeg(u8 *arg0, u8 *arg1) {
    f32 sp[4];
    u8 *temp_s3;

    temp_s3 = arg1 + 0x10;
    func_00312650((u8 *)sp, temp_s3, arg1);
    sceVu0Normalize((u8 *)sp, (u8 *)sp);
    func_003126C8(arg0, arg1);
    func_003126C8(arg0 + 0x10, temp_s3);
    *(f32 *)(arg0 + 0x10) = *(f32 *)(arg0 + 0x10) + (sp[0] * *(f32 *)(arg1 + 0x20));
    *(f32 *)(arg0 + 0x14) = *(f32 *)(arg0 + 0x14) + (sp[1] * *(f32 *)(arg1 + 0x20));
    *(f32 *)(arg0 + 0x18) = *(f32 *)(arg0 + 0x18) + (sp[2] * *(f32 *)(arg1 + 0x20));
    *(f32 *)(arg0 + 0) = *(f32 *)(arg0 + 0) - (sp[0] * *(f32 *)(arg1 + 0x20));
    *(f32 *)(arg0 + 4) = *(f32 *)(arg0 + 4) - (sp[1] * *(f32 *)(arg1 + 0x20));
    *(f32 *)(arg0 + 8) = *(f32 *)(arg0 + 8) - (sp[2] * *(f32 *)(arg1 + 0x20));
}
