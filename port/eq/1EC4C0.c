#include "common.h"

#define F32AT(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define S32AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define U8AT(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define PTRAT(p, o) (*(u8 **)((u8 *)(p) + (o)))

void Vu0Screen_StoreMtx(void *);
void sceVu0ApplyMatrix(void *, void *, void *);
void func_00312680(f32, void *, void *);
void func_00312638(void *, void *, void *);
void func_00312668(void *, void *, void *);
void func_001ED648(void *, void *, s32, s32, s32, s32, s32, s64, s32);

void func_001EC4C0(void *arg0) {
    u8 sp[0x2B0];
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s5;
    u8 *s6;
    u8 *fp;
    u8 *base220;
    u8 *p224;
    s32 outer;
    s32 cnt;
    s32 cnt2;
    s32 k0;
    s32 k1;
    s32 k2;
    s32 v1;
    s32 a2v;
    s32 v68;
    s32 t0v;
    s32 t1v;
    s32 t2v;
    s32 sp228v;
    s32 sp22Cv;
    s64 sp240;
    f32 f20;
    f32 f21;

    f21 = 1.0f;
    F32AT(sp, 0x200) = (f32)U8AT(arg0, 0x40) * 0.0078125f;
    F32AT(sp, 0x204) = (f32)U8AT(arg0, 0x41) * 0.0078125f;
    F32AT(sp, 0x208) = (f32)U8AT(arg0, 0x42) * 0.0078125f;
    F32AT(sp, 0x20C) = (f32)U8AT(arg0, 0x43) * 0.0078125f;
    F32AT(sp, 0x210) = F32AT(arg0, 0x50);
    F32AT(sp, 0x214) = F32AT(arg0, 0x54);
    S32AT(sp, 0x218) = 0;
    S32AT(sp, 0x21C) = 0;
    sp240 = 0;

    v68 = U8AT(arg0, 0x68);
    cnt = S32AT(PTRAT(arg0, 0x70), 4);
    t0v = v68 & 1 & 0xFF;
    t2v = v68 & 4;
    t1v = v68 & 2;
    base220 = PTRAT(arg0, 0x78);
    s5 = PTRAT(arg0, 0x74);
    p224 = PTRAT(arg0, 0x48);
    s6 = PTRAT(arg0, 0x7C);
    sp228v = S32AT(arg0, 0x44);
    sp22Cv = S32AT(arg0, 0x6C);
    f20 = F32AT(arg0, 0x60);

    Vu0Screen_StoreMtx(sp + 0x1C0);
    if (cnt <= 0) {
        return;
    }

    outer = cnt;
    do {
        S32AT(sp, 0x24C) = 0;
        cnt2 = S32AT(s5, 0);
        if (cnt2 > 0) {
            s3 = base220 + S32AT(s5, 8) * 0x10;
            fp = sp + 0x210;
            s0 = sp + 0x200;   /* only used as a2 below, set per use */
            do {
                k0 = S32AT(s3, 0);
                k1 = S32AT(s3, 4);
                k2 = S32AT(s3, 8);
                s0 = s6 + k0 * 0x30;
                s1 = s6 + k1 * 0x30;
                s2 = s6 + k2 * 0x30;
                sceVu0ApplyMatrix(sp + 0x10, arg0, s0);
                sceVu0ApplyMatrix(sp + 0x20, arg0, s1);
                sceVu0ApplyMatrix(sp + 0x30, arg0, s2);
                func_00312680(f20, sp + 0xA0, s0 + 0x20);
                func_00312680(f20, sp + 0xB0, s1 + 0x20);
                func_00312680(f20, sp + 0xC0, s2 + 0x20);
                func_00312638(sp + 0xA0, sp + 0xA0, fp);
                func_00312638(sp + 0xB0, sp + 0xB0, fp);
                func_00312638(sp + 0xC0, sp + 0xC0, fp);
                func_00312668(sp + 0x130, s0 + 0x10, sp + 0x200);
                func_00312668(sp + 0x140, s1 + 0x10, sp + 0x200);
                func_00312668(sp + 0x150, s2 + 0x10, sp + 0x200);
                a2v = 0;
                v1 = S32AT(s3, 0xC);
                s3 += 0x10;
                if (v1 >= 0) {
                    if (p224 != 0) {
                        a2v = 1;
                        sp240 = *(s64 *)(p224 + (v1 + S32AT(arg0, 0x64)) * 0x10);
                    }
                }
                S32AT(sp, 0x24C) += 1;
                F32AT(sp, 0xA8) = f21;
                S32AT(sp, 0xAC) = 0;
                F32AT(sp, 0xB8) = f21;
                S32AT(sp, 0xBC) = 0;
                F32AT(sp, 0xC8) = f21;
                S32AT(sp, 0xCC) = 0;
                /* 9th argument (sp22C) goes to the stack at sp+0 */
                func_001ED648(sp + 0x10, sp + 0x1C0, a2v, sp228v, t0v, t1v, t2v, sp240, sp22Cv);
            } while (S32AT(sp, 0x24C) < S32AT(s5, 0));
        }
        s5 += 0x10;
        outer -= 1;
    } while (outer != 0);
}
