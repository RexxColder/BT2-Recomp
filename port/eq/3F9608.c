#include "common.h"

extern u8 *D_0042A580;
extern u8 *D_0042139C;
extern u8 *D_003876A4;
u8 *func_0028BAA8(s32 size);
u8 *func_002B24C8();
void Res_RelocateOffsets();
void func_0026E7F0();
void func_0026EAE0();
void func_0024BED8();

#define O D_0042A580
#define OW(off) (*(s32 *)(O + (off)))
#define R(b, off) ((b) + ((*(u32 *)((b) + (off)) >> 2) << 2))
#define LOADREL(off) do { \
        u8 *b_ = *(u8 **)(O + 4); \
        sp[0] = (s32)R(b_, off); \
        Res_RelocateOffsets(sp, sp[0], sp[0]); \
    } while (0)
#define SP16 (*(s32 *)(sp[0] + 0x10))

s32 func_003F9608(s32 arg0) {
    s32 sp[4];
    u8 *obj, *s1;

    sp[0] = 0;
    obj = func_0028BAA8(0xF4);
    D_0042A580 = obj;
    __builtin_memset(obj, 0, 0xF4);
    {
        u8 *t = D_0042139C;
        *(u8 **)O = R(t, arg0 * 4);
    }
    *(u8 **)(O + 4) = func_002B24C8(*(u8 **)O, 0, 0);
    LOADREL(0x8);
    OW(0x8C) = sp[0];
    LOADREL(0x18);
    OW(0xB4) = SP16;
    LOADREL(0xC);
    OW(0xA4) = SP16;
    LOADREL(0x28);
    OW(0xA8) = SP16;
    OW(0xB0) = SP16 + 0x40;
    LOADREL(0x2C);
    OW(0x98) = SP16;
    OW(0xAC) = SP16;
    LOADREL(0x34);
    OW(0x94) = SP16;
    OW(0x90) = SP16 + 0x40;
    LOADREL(0x24);
    OW(0x9C) = SP16;
    OW(0xA0) = SP16;
    {
        u8 *b = *(u8 **)(O + 4);
        s1 = O + 0x64;
        func_0026E7F0(s1, R(b, 4), O + 0x90);
    }
    func_0026EAE0(s1, 0x3C);
    LOADREL(0x10);
    OW(0xC8) = SP16;
    LOADREL(0x30);
    OW(0xC0) = SP16;
    OW(0xBC) = SP16 + 0x40;
    LOADREL(0x3C);
    OW(0xC4) = SP16;
    {
        u8 *b = *(u8 **)(O + 4);
        s1 = O + 0x14;
        func_0026E7F0(s1, R(b, 0x14), O + 0xBC);
    }
    func_0026EAE0(s1, 0x3C);
    LOADREL(0x1C);
    OW(0xCC) = SP16;
    {
        u8 *b = *(u8 **)(O + 4);
        s1 = O + 0x3C;
        func_0026E7F0(s1, R(b, 0x20), O + 0xCC);
    }
    func_0026EAE0(s1, 0x3C);
    {
        u8 *b = *(u8 **)(O + 4);
        *(u8 **)(O + 0xC) = R(b, 0x48);
    }
    {
        u8 *b = *(u8 **)(O + 4);
        *(u8 **)(O + 8) = R(b, 0x40);
    }
    {
        u8 *b = *(u8 **)(O + 4);
        *(u8 **)(O + 0x10) = R(b, 0x44);
    }
    LOADREL(0x38);
    {
        u8 *b = *(u8 **)(O + 4);
        func_0024BED8(R(b, 0x4C), SP16);
    }
    OW(0xD8) = -1;
    OW(0xD4) = *(s32 *)(D_003876A4 + 0x54);
    *(s32 *)(D_003876A4 + 0x40) = 0;
    *(s32 *)(D_003876A4 + 0x44) = 0;
    *(s32 *)(D_003876A4 + 0x48) = 0;
    *(s32 *)(D_003876A4 + 0x4C) = 0;
    *(s32 *)(D_003876A4 + 0x50) = 0;
    *(s32 *)(D_003876A4 + 0x58) = 0;
    *(s32 *)(D_003876A4 + 0x5C) = 0;
    *(s32 *)(D_003876A4 + 0x60) = 0;
    *(s32 *)(D_003876A4 + 0x64) = 0;
    return (s32)D_003876A4;
}
