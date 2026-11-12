#include "common.h"

void Res_RelocateOffsets(void *arg0, void *arg1, void *arg2);
void func_0026E7F0(void *arg0, void *arg1, void *arg2);
void *func_0028BAA8(s32 arg0);
void func_002B24C8(s32 arg0, void *arg1, s32 arg2);
void *memset(void *arg0, s32 arg1, s32 arg2);
extern void *D_00387A10;

void func_00259378(s32 arg0, u8 *arg1) {
    u8 *sp[4];
    u8 *v;

    sp[0] = 0;
    D_00387A10 = func_0028BAA8(0xCC);
    memset(D_00387A10, 0, 0xCC);
    func_002B24C8(arg0, arg1, 0);

    v = arg1 + (*(u32 *)(arg1 + 0x28) & ~3u);
    sp[0] = v;
    Res_RelocateOffsets(sp, v, v);
    *(s32 *)((u8 *)D_00387A10 + 0x8C) = *(s32 *)(sp[0] + 0x10);

    v = arg1 + (*(u32 *)(arg1 + 0x24) & ~3u);
    sp[0] = v;
    Res_RelocateOffsets(sp, v, v);
    *(s32 *)((u8 *)D_00387A10 + 0x80) = *(s32 *)(sp[0] + 0x10);

    v = arg1 + (*(u32 *)(arg1 + 0x1C) & ~3u);
    sp[0] = v;
    Res_RelocateOffsets(sp, v, v);
    *(s32 *)((u8 *)D_00387A10 + 0x88) = *(s32 *)(sp[0] + 0x10);

    v = arg1 + (*(u32 *)(arg1 + 0x0C) & ~3u);
    sp[0] = v;
    Res_RelocateOffsets(sp, v, v);
    *(s32 *)((u8 *)D_00387A10 + 0x84) = *(s32 *)(sp[0] + 0x10);

    v = arg1 + (*(u32 *)(arg1 + 0x08) & ~3u);
    sp[0] = v;
    Res_RelocateOffsets(sp, v, v);
    *(s32 *)((u8 *)D_00387A10 + 0x7C) = *(s32 *)(sp[0] + 0x10);

    v = arg1 + (*(u32 *)(arg1 + 0x08) & ~3u);
    sp[0] = v;
    Res_RelocateOffsets(sp, v, v);
    *(s32 *)((u8 *)D_00387A10 + 0x7C) = *(s32 *)(sp[0] + 0x10);

    func_0026E7F0((u8 *)D_00387A10 + 4, arg1 + (*(u32 *)(arg1 + 0x04) & ~3u),
                  (u8 *)D_00387A10 + 0x7C);

    v = arg1 + (*(u32 *)(arg1 + 0x10) & ~3u);
    sp[0] = v;
    Res_RelocateOffsets(sp, v, v);
    *(s32 *)((u8 *)D_00387A10 + 0x94) = *(s32 *)(sp[0] + 0x10);

    v = arg1 + (*(u32 *)(arg1 + 0x18) & ~3u);
    sp[0] = v;
    Res_RelocateOffsets(sp, v, v);
    *(s32 *)((u8 *)D_00387A10 + 0x90) = *(s32 *)(sp[0] + 0x10);

    v = arg1 + (*(u32 *)(arg1 + 0x14) & ~3u);
    sp[0] = v;
    Res_RelocateOffsets(sp, v, v);
    *(s32 *)((u8 *)D_00387A10 + 0x98) = *(s32 *)(sp[0] + 0x10);

    func_0026E7F0((u8 *)D_00387A10 + 0x2C, arg1 + (*(u32 *)(arg1 + 0x2C) & ~3u),
                  (u8 *)D_00387A10 + 0x90);

    v = arg1 + (*(u32 *)(arg1 + 0x34) & ~3u);
    sp[0] = v;
    Res_RelocateOffsets(sp, v, v);
    *(s32 *)((u8 *)D_00387A10 + 0x9C) = *(s32 *)(sp[0] + 0x10);

    v = arg1 + (*(u32 *)(arg1 + 0x3C) & ~3u);
    sp[0] = v;
    Res_RelocateOffsets(sp, v, v);
    *(s32 *)((u8 *)D_00387A10 + 0xA0) = *(s32 *)(sp[0] + 0x10);

    v = arg1 + (*(u32 *)(arg1 + 0x38) & ~3u);
    sp[0] = v;
    Res_RelocateOffsets(sp, v, v);
    *(s32 *)((u8 *)D_00387A10 + 0xA4) = *(s32 *)(sp[0] + 0x10);

    func_0026E7F0((u8 *)D_00387A10 + 0x54, arg1 + (*(u32 *)(arg1 + 0x30) & ~3u),
                  (u8 *)D_00387A10 + 0x9C);

    *(u8 **)((u8 *)D_00387A10 + 0xC8) = arg1 + (*(u32 *)(arg1 + 0x20) & ~3u);
    *(u8 **)((u8 *)D_00387A10 + 0x00) = arg1 + (*(u32 *)(arg1 + 0x44) & ~3u);
    *(u8 **)((u8 *)D_00387A10 + 0xC4) = arg1 + (*(u32 *)(arg1 + 0x40) & ~3u) + 4;
}
