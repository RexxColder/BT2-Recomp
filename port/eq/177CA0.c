#include "common.h"

void Vu0Screen_StoreMtx(void *a0);
void func_00177ED8(void *a0, void *a1);
void func_00178070(void *a0, void *a1, void *a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15);
extern u8 *D_00387E94;

void func_00177CA0(void) {
    u8 buf[0x80];
    u8 *s0;

    if (*(u8 *)(D_00387E94 + 0x3F50) != 0) {
        Vu0Screen_StoreMtx(buf);
        s0 = *(u8 **)(D_00387E94 + 0x3F5C);
        while (s0 != NULL) {
            if (*(s32 *)(s0 + 0x44) & 1) {
                func_00177ED8(buf + 0x40, s0);
                func_00178070(buf + 0x40, buf, D_00387E94 + 16 * *(u8 *)(s0 + 0x48) + 0x3D48,
                              *(u8 *)(s0 + 0x49), 0.0f, 0.0f, 0.0f, *(f32 *)(s0 + 0x3C));
            }
            s0 = *(u8 **)(s0 + 0x50);
        }
    }
}
