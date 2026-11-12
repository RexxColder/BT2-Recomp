#include "common.h"

extern u8 *D_004279D0;
extern u8 *D_00421398;
extern u8 D_004289B0[];
extern u8 *D_00387F2C;
u8 *func_0028BAA8(s32 size);
u8 *func_002B24C8();
void Res_RelocateOffsets(s32 arg0, s32 arg1, s32 arg2);
void func_0026E7F0(s32 a0, s32 a1, s32 a2);
void func_0026EAE0(s32 a0, s32 a1);
void func_0029BB88(s32 a0, s32 a1);

#define OBJ (D_004279D0)
#define L(dst, src_off, add) *(u32 *)(OBJ + (dst)) = *(u32 *)(*(u8 **)(OBJ + (src_off)) + 0x10) + (add)
#define REL(b, o) ((b) + ((*(u32 *)((b) + (o)) >> 2) << 2))

s32 func_003E68D0(s32 arg0) {
    u8 sp[0x4C];
    s32 i;
    u8 *obj, *b;

    obj = func_0028BAA8(0x328);
    D_004279D0 = obj;
    __builtin_memset(obj, 0, 0x328);
    b = D_00421398;
    *(u8 **)OBJ = b + ((*(u32 *)(b + arg0 * 4) >> 2) << 2);
    *(u8 **)(OBJ + 4) = func_002B24C8(*(u8 **)OBJ, 0, 0);
    for (i = 0; i < 0x13; i++) {
        u8 *b4;
        u8 *r;
        __builtin_memcpy(sp, D_004289B0, 0x4C);
        b4 = *(u8 **)(OBJ + 4);
        r = REL(b4, *(u32 *)(sp + i * 4) * 4);
        Res_RelocateOffsets((s32)(OBJ + 0x38 + i * 4), (s32)r, (s32)r);
    }
    L(0x84, 0x60, 0);
    L(0x88, 0x80, 0);
    L(0x8C, 0x80, 0);
    L(0x90, 0x80, 0);
    L(0x94, 0x6C, 0);
    L(0x98, 0x6C, 0x40);
    L(0x9C, 0x70, 0);
    L(0xA0, 0x74, 0);
    L(0xA4, 0x3C, 0);
    L(0xA8, 0x48, 0);
    L(0xAC, 0x74, 0x40);
    L(0xB0, 0x48, 0x40);
    L(0xB4, 0x4C, 0);
    L(0xB8, 0x5C, 0);
    L(0xBC, 0x64, 0);
    L(0xC0, 0x54, 0);
    L(0xC4, 0x68, 0);
    L(0xC8, 0x7C, 0);
    L(0xCC, 0x78, 0);
    L(0xD0, 0x50, 0);
    L(0xD4, 0x78, 0x40);
    L(0xD8, 0x50, 0x40);
    L(0xDC, 0x40, 0);
    L(0xE0, 0x40, 0x40);
    L(0xE4, 0x58, 0);
    L(0xE8, 0x44, 0);
    b = *(u8 **)(OBJ + 4);
    func_0026E7F0((s32)(OBJ + 0x10), (s32)REL(b, 0x1C), (s32)(OBJ + 0x84));
    func_0026EAE0((s32)(OBJ + 0x10), 0x3C);
    b = *(u8 **)(OBJ + 4);
    *(u8 **)(OBJ + 8) = REL(b, 0x50);
    b = *(u8 **)(OBJ + 4);
    *(u8 **)(OBJ + 0xC) = REL(b, 0x54);
    b = *(u8 **)(OBJ + 4);
    func_0029BB88((s32)REL(b, 0x5C), (s32)*(u8 **)(OBJ + 8));
    __builtin_memcpy(OBJ + 0xFC, D_00387F2C + 0x1008, 0xAC);
    *(s32 *)(OBJ + 0xEC) = -1;
    *(f32 *)(OBJ + 0x30C) = 1.0f;
    return 0;
}
