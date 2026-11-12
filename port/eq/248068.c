#include "common.h"

void Res_RelocateOffsets(s32 arg0, s32 arg1, s32 arg2);
void func_0026E7F0(s32 arg0, s32 arg1, s32 arg2);
s32 func_0028BAA8(s32 arg0);
s32 func_002B24C8(s32 arg0, s32 arg1, s32 arg2);
void memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_00387978;

void func_00248068(s32 arg0) {
    u8 *p;
    u8 *t;

    D_00387978 = (u8 *)func_0028BAA8(0x44);
    memset(D_00387978, 0, 0x44);
    *(s32 *)(D_00387978 + 0) = func_002B24C8(arg0, 0, 0);
    p = *(u8 **)(D_00387978 + 0);
    t = p + ((*(u32 *)(p + 4) >> 2) << 2);
    Res_RelocateOffsets((s32)(D_00387978 + 0x2C), (s32)t, (s32)t);
    *(s32 *)(D_00387978 + 0x30) = *(s32 *)(*(u8 **)(D_00387978 + 0x2C) + 0x10) + 0x40;
    *(s32 *)(D_00387978 + 0x34) = *(s32 *)(*(u8 **)(D_00387978 + 0x2C) + 0x10);
    p = *(u8 **)(D_00387978 + 0);
    func_0026E7F0((s32)(D_00387978 + 4), (s32)(p + ((*(u32 *)(p + 8) >> 2) << 2)), (s32)(D_00387978 + 0x30));
    p = *(u8 **)(D_00387978 + 0);
    *(u8 **)(D_00387978 + 0x3C) = p + ((*(u32 *)(p + 0xC) >> 2) << 2);
}
