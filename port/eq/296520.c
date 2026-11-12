#include "common.h"

void func_00312650(void *arg0, void *arg1, void *arg2);
void func_00312490(void *arg0, void *arg1, void *arg2);

void Rigid_AddForceAt(u8 *arg0, void *arg1, void *arg2) {
    f32 buf[8];
    f32 *s1;
    u8 *a2;

    s1 = &buf[4];
    a2 = (u8 *)arg2;
    func_00312650(s1, arg1, arg0 + 0x30);
    func_00312490(buf, s1, arg2);
    *(f32 *)(arg0 + 0xB0) = *(f32 *)(arg0 + 0xB0) + *(f32 *)(a2 + 0);
    *(f32 *)(arg0 + 0xB4) = *(f32 *)(arg0 + 0xB4) + *(f32 *)(a2 + 4);
    *(f32 *)(arg0 + 0xC8) = *(f32 *)(arg0 + 0xC8) + buf[2];
    *(f32 *)(arg0 + 0xC0) = *(f32 *)(arg0 + 0xC0) + buf[0];
    *(f32 *)(arg0 + 0xC4) = *(f32 *)(arg0 + 0xC4) + buf[1];
    *(f32 *)(arg0 + 0xB8) = *(f32 *)(arg0 + 0xB8) + *(f32 *)(a2 + 8);
}
