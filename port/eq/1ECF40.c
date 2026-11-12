#include "common.h"

#define FR_F(off) (*(f32 *)(fr + (off)))
#define FR_W(off) (*(s32 *)(fr + (off)))

void Vu0Screen_StoreMtx(void *m, s32 a1, s32 a2);
void sceVu0ApplyMatrix(void *dst, void *src, void *mtx);
void func_00312680(f32 w, void *dst, void *src);
void func_00312638(void *dst, void *a, void *b);
void func_00312668(void *dst, void *src, void *k);
void func_0012D868(void *a0, void *a1, void *a2, s32 a3, void *t0, void *t1);
s32 func_001EED70(void *a0);
void func_001EE8B0(void *a0, void *a1, void *a2, void *a3, void *t0, void *t1, void *t2, void *t3,
                   void *st0, s64 st8, s32 st10);

void func_001ECF40(void *arg0, s32 arg1) {
    u8 fr[0x1F0];
    u8 *s4 = (u8 *)arg0;
    s32 sp170 = arg1 & 0xFF;
    s32 sp174;
    s32 sp178;
    s32 s6;
    s32 outer;
    s32 inner;
    u8 *s5;
    u8 *s3;
    u8 *p0;
    u8 *p1;
    u8 *p2;
    f32 f20;
    f32 f21 = 1.0f;

    FR_F(0xC0) = (f32)s4[0x40] * 0.0078125f;
    FR_F(0xC4) = (f32)s4[0x41] * 0.0078125f;
    FR_F(0xC8) = (f32)s4[0x42] * 0.0078125f;
    FR_F(0xCC) = (f32)s4[0x43] * 0.0078125f;
    FR_F(0x160) = *(f32 *)(s4 + 0x50);
    FR_F(0x164) = *(f32 *)(s4 + 0x54);
    FR_W(0x168) = 0;
    FR_W(0x16C) = 0;
    s5 = (u8 *)*(s32 *)(s4 + 0x74);
    outer = *(s32 *)((u8 *)*(s32 *)(s4 + 0x70) + 4);
    sp174 = *(s32 *)(s4 + 0x78);
    sp178 = *(s32 *)(s4 + 0x48);
    s6 = *(s32 *)(s4 + 0x7C);
    f20 = *(f32 *)(s4 + 0x60);
    Vu0Screen_StoreMtx(fr + 0x20, s4[0x42], s4[0x43]);

    if (outer > 0) {
        do {
            inner = 0;
            s3 = (u8 *)(sp174 + *(s32 *)(s5 + 8) * 0x10);
            if (*(s32 *)s5 > 0) {
                do {
                    p0 = (u8 *)(s6 + *(s32 *)(s3 + 0) * 0x30);
                    p1 = (u8 *)(s6 + *(s32 *)(s3 + 4) * 0x30);
                    p2 = (u8 *)(s6 + *(s32 *)(s3 + 8) * 0x30);

                    sceVu0ApplyMatrix(fr + 0xD0, s4, p0);
                    sceVu0ApplyMatrix(fr + 0xE0, s4, p1);
                    sceVu0ApplyMatrix(fr + 0xF0, s4, p2);

                    func_00312680(f20, fr + 0x100, p0 + 0x20);
                    func_00312680(f20, fr + 0x110, p1 + 0x20);
                    func_00312680(f20, fr + 0x120, p2 + 0x20);

                    func_00312638(fr + 0x100, fr + 0x100, fr + 0x160);
                    func_00312638(fr + 0x110, fr + 0x110, fr + 0x160);
                    func_00312638(fr + 0x120, fr + 0x120, fr + 0x160);

                    func_00312668(fr + 0x90, p0 + 0x10, fr + 0xC0);
                    func_00312668(fr + 0xA0, p1 + 0x10, fr + 0xC0);
                    func_00312668(fr + 0xB0, p2 + 0x10, fr + 0xC0);

                    FR_F(0x108) = f21;
                    FR_W(0x10C) = 0;
                    FR_F(0x118) = f21;
                    FR_W(0x11C) = 0;
                    FR_F(0x128) = f21;
                    FR_W(0x12C) = 0;
                    func_0012D868(fr + 0x60, fr + 0x20, fr + 0xD0, 3, fr + 0x130, fr + 0x100);

                    if ((func_001EED70(fr + 0x60) == 0) && (func_001EED70(fr + 0x70) == 0)) {
                        if (func_001EED70(fr + 0x80) == 0) {
                            s64 st8 = *(s64 *)(sp178 + 16 * (*(s32 *)(s3 + 0xC) + *(s32 *)(s4 + 0x64)));
                            func_001EE8B0(fr + 0x60, fr + 0x70, fr + 0x80, fr + 0x90, fr + 0xA0, fr + 0xB0,
                                          fr + 0x130, fr + 0x140, fr + 0x150, st8, sp170);
                        }
                    }

                    s3 += 0x10;
                    inner += 1;
                } while (inner < *(s32 *)s5);
            }
            s5 += 0x10;
            outer -= 1;
        } while (outer != 0);
    }
}
