#include "common.h"

#define FRF(off) (*(f32 *)(fr + (off)))
#define FRW(off) (*(s32 *)(fr + (off)))
#define OBJW(off) (*(s32 *)(obj + (off)))
#define OBJF(off) (*(f32 *)(obj + (off)))

void Vu0Screen_StoreMtx(void *a0, s32 a1, s32 a2, s32 a3);
void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);
void func_00312638(void *a0, void *a1, void *a2);
void func_00312668(void *a0, void *a1, void *a2);
void func_00312680(f32 f12, void *a0, void *a1, void *a2);
void func_001ED8F0(void *a0, void *a1, s64 a2, s32 a3);

void func_001EC818(u8 *obj, s32 arg1) {
    u8 fr[0x230];
    u8 *s3;
    u8 *s5;
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *base6;
    u8 *sp214;
    u8 *sp218;
    u8 *ptr;
    s32 a1b;
    s32 count;
    s32 i;
    s32 v0;
    f32 f20;

    a1b = arg1 & 0xFF;
    FRF(0x200) = OBJF(0x50);
    FRF(0x204) = OBJF(0x54);
    FRW(0x208) = 0;
    FRW(0x20C) = 0;
    FRF(0x1F0) = (f32)*(u8 *)(obj + 0x40) * 0.0078125f;
    FRW(0x210) = a1b;
    FRF(0x1F8) = (f32)*(u8 *)(obj + 0x42) * 0.0078125f;
    FRF(0x1F4) = (f32)*(u8 *)(obj + 0x41) * 0.0078125f;
    FRF(0x1FC) = (f32)*(u8 *)(obj + 0x43) * 0.0078125f;
    count = *(s32 *)(*(u8 **)(obj + 0x70) + 4);
    s5 = *(u8 **)(obj + 0x74);
    sp214 = *(u8 **)(obj + 0x78);
    sp218 = *(u8 **)(obj + 0x48);
    base6 = *(u8 **)(obj + 0x7C);
    f20 = OBJF(0x60);

    Vu0Screen_StoreMtx(fr + 0x1B0, a1b, OBJW(0x48), *(u8 *)(obj + 0x41));

    if (count > 0) {
        do {
            i = 0;
            s3 = sp214 + (*(s32 *)(s5 + 8) * 16);
            if (*(s32 *)s5 > 0) {
                do {
                    s0 = base6 + (*(s32 *)s3 * 0x30);
                    s2 = base6 + (*(s32 *)(s3 + 8) * 0x30);
                    s1 = base6 + (*(s32 *)(s3 + 4) * 0x30);
                    sceVu0ApplyMatrix(fr, obj, s0);
                    i += 1;
                    sceVu0ApplyMatrix(fr + 0x10, obj, s1);
                    sceVu0ApplyMatrix(fr + 0x20, obj, s2);
                    func_00312680(f20, fr + 0x90, s0 + 0x20, fr + 0x90);
                    func_00312680(f20, fr + 0xA0, s1 + 0x20, fr + 0x90);
                    func_00312680(f20, fr + 0xB0, s2 + 0x20, fr + 0x90);
                    func_00312638(fr + 0x90, fr + 0x90, fr + 0x200);
                    func_00312638(fr + 0xA0, fr + 0xA0, fr + 0x200);
                    func_00312638(fr + 0xB0, fr + 0xB0, fr + 0x200);
                    func_00312668(fr + 0x120, s0 + 0x10, fr + 0x1F0);
                    func_00312668(fr + 0x130, s1 + 0x10, fr + 0x1F0);
                    func_00312668(fr + 0x140, s2 + 0x10, fr + 0x1F0);
                    v0 = *(s32 *)(s3 + 0xC) + OBJW(0x64);
                    ptr = sp218 + (v0 * 16);
                    s3 += 0x10;
                    FRF(0x98) = 1.0f;
                    FRW(0x9C) = 0;
                    FRF(0xA8) = 1.0f;
                    FRW(0xAC) = 0;
                    FRF(0xB8) = 1.0f;
                    FRW(0xBC) = 0;
                    func_001ED8F0(fr, fr + 0x1B0, *(s64 *)ptr, a1b);
                } while (i < *(s32 *)s5);
            }
            s5 += 0x10;
            count -= 1;
        } while (count != 0);
    }
}
