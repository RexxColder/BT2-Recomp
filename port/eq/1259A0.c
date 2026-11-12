#include "common.h"

s32 func_00126040(s32 arg0);
f32 BtlCharApi_GetHeight(s32 arg0);
s32 BtlChar_GetPos(s32 arg0);
f32 sinf(f32 arg0);
f32 cosf(f32 arg0);
void func_001257E0(f32 farg0, s32 arg0, s32 arg1);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
s32 func_003126C8(s32 arg0, s32 arg1);

void func_001259A0(s32 arg0) {
    f32 sp[24];
    s32 s1;
    s32 p;
    f32 height;
    f32 sin1;
    f32 cos1;
    f32 sin2;
    f32 cos2;

    s1 = func_00126040(arg0);
    height = BtlCharApi_GetHeight(*(s32 *)(s1 + 0x1534));

    sin1 = sinf(*(f32 *)(s1 + 0x150)) * 100.0f;
    cos1 = cosf(*(f32 *)(s1 + 0x150)) * 100.0f;
    sp[0] = sin1;
    sp[1] = 0.0f;
    sp[2] = cos1;
    sp[3] = 0.0f;
    sp[4] = cos1;
    sp[5] = 0.0f;
    sp[6] = -sin1;
    sp[7] = 0.0f;
    sp[8] = 0.0f;
    sp[9] = -100.0f;
    sp[10] = 0.0f;
    sp[11] = 0.0f;

    p = BtlChar_GetPos(s1);
    sin2 = sinf(*(f32 *)(p + 0xB4)) * 100.0f;
    sp[12] = sin2;
    sp[13] = 0.0f;
    p = BtlChar_GetPos(s1);
    cos2 = cosf(*(f32 *)(p + 0xB4)) * 100.0f;
    sp[14] = cos2;
    sp[15] = 0.0f;

    func_003126C8((s32)&sp[16], *(s32 *)(*(s32 *)(s1 + 0x1530) + 0xF40));

    func_00312638((s32)&sp[20], (s32)&sp[16], (s32)&sp[0]);
    func_001257E0(height, arg0 + 0x1080, (s32)&sp[16]);
    func_00312650((s32)&sp[20], (s32)&sp[16], (s32)&sp[0]);
    func_001257E0(height, arg0 + 0x1084, (s32)&sp[16]);
    func_00312638((s32)&sp[20], (s32)&sp[16], (s32)&sp[4]);
    func_001257E0(height, arg0 + 0x108C, (s32)&sp[16]);
    func_00312650((s32)&sp[20], (s32)&sp[16], (s32)&sp[4]);
    func_001257E0(height, arg0 + 0x1088, (s32)&sp[16]);
    func_00312638((s32)&sp[20], (s32)&sp[16], (s32)&sp[8]);
    func_001257E0(height, arg0 + 0x1090, (s32)&sp[16]);
    func_00312650((s32)&sp[20], (s32)&sp[16], (s32)&sp[8]);
    func_001257E0(height, arg0 + 0x1094, (s32)&sp[16]);
    func_00312638((s32)&sp[20], (s32)&sp[16], (s32)&sp[12]);
    func_001257E0(height, arg0 + 0x1098, (s32)&sp[16]);
}
