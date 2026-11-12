#include "common.h"

void *func_0028BAA8(s32 arg0);
void *func_002B24C8(s32 arg0, s32 arg1, s32 arg2);
void Res_RelocateOffsets(void *arg0, void *arg1, void *arg2);
void func_0026E7F0(void *arg0, void *arg1, void *arg2);
extern u8 *D_00387DA0;

void Port_TextoAplicarTabla(u32 tabla);   /* F5: port/full/plat_text.c */

void func_0029BB88(s32 arg0, s32 arg1) {
    void *sp[4];
    u8 *temp_a2;
    u8 *temp_v0;

    D_00387DA0 = func_0028BAA8(0x78);
    memset(D_00387DA0, 0, 0x78);
    *(u8 **)D_00387DA0 = func_002B24C8(arg0, 0, 0);

    temp_a2 = *(u8 **)D_00387DA0;
    temp_a2 = temp_a2 + (((u32)*(u32 *)(temp_a2 + 8) >> 2) * 4);
    sp[0] = temp_a2;
    Res_RelocateOffsets(sp, temp_a2, temp_a2);
    *(s32 *)(D_00387DA0 + 0x30) = *(s32 *)((u8 *)sp[0] + 0x10);

    temp_a2 = *(u8 **)D_00387DA0;
    temp_a2 = temp_a2 + (((u32)*(u32 *)(temp_a2 + 0x10) >> 2) * 4);
    sp[0] = temp_a2;
    Res_RelocateOffsets(sp, temp_a2, temp_a2);
    *(s32 *)(D_00387DA0 + 0x34) = *(s32 *)((u8 *)sp[0] + 0x10);
    *(s32 *)(D_00387DA0 + 0x38) = *(s32 *)((u8 *)sp[0] + 0x10);

    temp_a2 = *(u8 **)D_00387DA0;
    temp_a2 = temp_a2 + (((u32)*(u32 *)(temp_a2 + 0xC) >> 2) * 4);
    sp[0] = temp_a2;
    Res_RelocateOffsets(sp, temp_a2, temp_a2);
    *(s32 *)(D_00387DA0 + 0x4C) = *(s32 *)((u8 *)sp[0] + 0x10);
    *(s32 *)(D_00387DA0 + 0x3C) = *(s32 *)((u8 *)sp[0] + 0x10) + 0x40;

    temp_v0 = *(u8 **)D_00387DA0;
    func_0026E7F0(D_00387DA0 + 8, temp_v0 + (((u32)*(u32 *)(temp_v0 + 4) >> 2) * 4), D_00387DA0 + 0x30);

    temp_v0 = *(u8 **)D_00387DA0;
    *(u8 **)(D_00387DA0 + 0x50) = temp_v0 + (((u32)*(u32 *)(temp_v0 + 0x14) >> 2) * 4);
    *(s32 *)(*(u8 **)(D_00387DA0 + 0x50) + 0x34) = 0;
    *(s32 *)(D_00387DA0 + 4) = arg1;
    if (arg1 != 0) {
        Port_TextoAplicarTabla((u32)arg1);   /* F5: reescribe los textos en RAM */
    }
    *(s32 *)(D_00387DA0 + 0x5C) = -1;
    *(s32 *)(D_00387DA0 + 0x68) = -1;
    *(s32 *)(D_00387DA0 + 0x74) = 0;
}
