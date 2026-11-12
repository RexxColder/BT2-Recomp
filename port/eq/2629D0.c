#include "common.h"

extern u8 D_002C3630[] __attribute__((section(".data")));

u8 *func_00269A08(u8 *arg0, s32 arg1);
u8 *func_00269A40(u8 *arg0, s32 arg1);
void func_002625D0(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);
void sceVu0NormalLightMatrix(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);

/* BT2 asm: no Vu0_InitAxisRegs call at the end (BT3 has one; the BT2 asm wins). */
void func_002629D0(u8 *arg0, u8 *arg1) {
    u8 work[0xD0];
    u8 *model;
    u8 *sec;
    u8 *vtx;
    s32 seamOfs;
    s32 i;

    model = *(u8 **)(arg0 + 0x44);
    seamOfs = *(s32 *)(model + 8);
    if (seamOfs == 0) {
        return;
    }
    sec = model + seamOfs;
    vtx = model + *(s32 *)(sec + 8);
    sceVu0NormalLightMatrix(work + 0x80, arg1 + 0x10, D_002C3630, D_002C3630);
    *(f32 *)(work + 0xCC) = 0.5f;
    for (i = 0; i < *(s32 *)(sec + 0); i++) {
        u8 *part = func_00269A08(arg0, *(s32 *)(vtx + 0x1C));
        u8 *node = func_00269A40(arg0, *(s32 *)(vtx + 0x1C));

        func_002625D0(vtx, work, node, part + 0x10);
        vtx += 0x70;
    }
}
