#include "common.h"

void *func_0028BAA8(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);
void func_002B24C8(s32 arg0, s32 arg1, s32 arg2);
void Res_RelocateOffsets(s32 arg0, s32 arg1, s32 arg2);
void func_0026E7F0(s32 arg0, s32 arg1, s32 arg2);
void func_00250BF0(s32 arg0, s32 arg1);
extern void *D_003879E8;

void func_00256360(s32 arg0, u8 *arg1) {
    s32 sp[4];
    s32 tmp;

    D_003879E8 = func_0028BAA8(0x98);
    memset(D_003879E8, 0, 0x98);
    func_002B24C8(arg0, (s32)arg1, 0);

    /* each Res_RelocateOffsets call writes its result through sp[0]: read it after each call */
    sp[0] = (s32)arg1 + (s32)((*(u32 *)(arg1 + 0x14) >> 2) * 4);
    Res_RelocateOffsets((s32)sp, sp[0], sp[0]);
    *(s32 *)((u8 *)D_003879E8 + 0x30) = *(s32 *)((u8 *)sp[0] + 0x10);
    *(s32 *)((u8 *)D_003879E8 + 0x2C) = *(s32 *)((u8 *)sp[0] + 0x10) + 0x40;

    sp[0] = (s32)arg1 + (s32)((*(u32 *)(arg1 + 0x10) >> 2) * 4);
    Res_RelocateOffsets((s32)sp, sp[0], sp[0]);
    *(s32 *)((u8 *)D_003879E8 + 0x48) = *(s32 *)((u8 *)sp[0] + 0x10);

    sp[0] = (s32)arg1 + (s32)((*(u32 *)(arg1 + 0x20) >> 2) * 4);
    Res_RelocateOffsets((s32)sp, sp[0], sp[0]);
    *(s32 *)((u8 *)D_003879E8 + 0x34) = *(s32 *)((u8 *)sp[0] + 0x10);

    sp[0] = (s32)arg1 + (s32)((*(u32 *)(arg1 + 0x24) >> 2) * 4);
    Res_RelocateOffsets((s32)sp, sp[0], sp[0]);
    *(s32 *)((u8 *)D_003879E8 + 0x40) = *(s32 *)((u8 *)sp[0] + 0x10);

    sp[0] = (s32)arg1 + (s32)((*(u32 *)(arg1 + 0x1C) >> 2) * 4);
    Res_RelocateOffsets((s32)sp, sp[0], sp[0]);
    *(s32 *)((u8 *)D_003879E8 + 0x38) = *(s32 *)((u8 *)sp[0] + 0x10);

    func_0026E7F0((s32)((u8 *)D_003879E8 + 4),
                  (s32)arg1 + (s32)((*(u32 *)(arg1 + 0xC) >> 2) * 4),
                  (s32)((u8 *)D_003879E8 + 0x2C));

    tmp = (s32)arg1 + (s32)((*(u32 *)(arg1 + 0x18) >> 2) * 4);
    *(s32 *)((u8 *)D_003879E8 + 0x80) = *(s32 *)tmp;
    *(s32 *)((u8 *)D_003879E8 + 0x84) = tmp + 4;

    tmp = (s32)arg1 + (s32)((*(u32 *)(arg1 + 0x2C) >> 2) * 4);
    *(s32 *)((u8 *)D_003879E8 + 0x88) = *(s32 *)tmp;
    *(s32 *)((u8 *)D_003879E8 + 0x8C) = tmp + 4;

    *(s32 *)((u8 *)D_003879E8 + 0) = (s32)arg1 + (s32)((*(u32 *)(arg1 + 8) >> 2) * 4);
    *(s32 *)((u8 *)D_003879E8 + 0x58) = (s32)arg1 + (s32)((*(u32 *)(arg1 + 4) >> 2) * 4) + 4;

    func_00250BF0((s32)arg1 + (s32)((*(u32 *)(arg1 + 0x28) >> 2) * 4), (s32)D_003879E8);
}
