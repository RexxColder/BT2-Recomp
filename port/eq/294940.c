#include "common.h"

void func_003126C8(s32 arg0, s32 arg1);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void sceVu0Normalize();

/* 0x00294940 ColRay_FromSeg (BT3 name, fuzzy): func_003126C8(arg0, arg1); func_00312650(arg0 + 0x10, arg1 + 0x10,
 * arg1); then sceVu0Normalize(arg0 + 0x10, arg0 + 0x10) (tail). The first call passes the arguments through. */
void ColRay_FromSeg(s32 arg0, s32 arg1) {
    func_003126C8(arg0, arg1);
    func_00312650(arg0 + 0x10, arg1 + 0x10, arg1);
    sceVu0Normalize(arg0 + 0x10, arg0 + 0x10);
}
