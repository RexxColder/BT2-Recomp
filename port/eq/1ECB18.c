#include "common.h"

#define SPF(o) (*(f32 *)(fr + (o)))
#define SPW(o) (*(s32 *)(fr + (o)))
#define SPA(o) ((void *)(fr + (o)))
#define OBJW(o) (*(s32 *)(obj + (o)))
#define OBJF(o) (*(f32 *)(obj + (o)))
#define OBJB(o) (*(u8 *)(obj + (o)))

void Vu0Screen_StoreMtx(void *a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2);
void sceVu0ApplyMatrix(void *a0, u8 *a1, void *a2);
void func_00312680(f32 farg0, void *a0, void *a1);
void func_00312638(void *a0, void *a1, void *a2);
void func_00312668(void *a0, void *a1, void *a2);
void func_0012D868(void *a0, void *a1, void *a2, s32 a3, void *t0, void *t1);
s32 func_001EED70(void *a0);
void func_001EDD98(void *a0, void *a1, void *a2, void *a3, void *t0, void *t1, void *t2, void *t3,
                   void *p9, s32 p10, s32 p11, s32 p12, s32 p13, s32 p14, s64 p15);

void func_001ECB18(u8 *obj) {
    u8 fr[0x220] __attribute__((aligned(8)));
    s64 p1b0;
    f32 f20;
    f32 f21;
    s32 cnt;
    s32 ctr;
    s32 t4;
    s32 s0v;
    s32 v;
    s32 vv;
    s32 ix;
    s32 iy;
    s32 iz;
    s32 sp1a0;
    s32 sp1a4;
    s32 sp1a8;
    s32 sp198;
    s32 sp19c;
    u8 *sp190;
    u8 *sp194;
    u8 *s4;
    u8 *s5;
    u8 *s6;
    u8 *A;
    u8 *B;
    u8 *C;

    p1b0 = 0;
    SPF(0x180) = OBJF(0x50);
    SPF(0x184) = OBJF(0x54);
    SPW(0x188) = 0;
    SPW(0x18C) = 0;
    SPF(0xE0) = (f32)OBJB(0x40) * 0.0078125f;
    SPF(0xE4) = (f32)OBJB(0x41) * 0.0078125f;
    SPF(0xE8) = (f32)OBJB(0x42) * 0.0078125f;
    SPF(0xEC) = (f32)OBJB(0x43) * 0.0078125f;

    v = OBJB(0x68);
    sp1a0 = (v & 1) & 0xFF;
    sp1a4 = v & 2;
    sp1a8 = v & 4;
    sp190 = *(u8 **)(obj + 0x78);
    s5 = *(u8 **)(obj + 0x74);
    sp194 = *(u8 **)(obj + 0x48);
    sp198 = OBJW(0x44);
    sp19c = OBJW(0x6C);
    s6 = *(u8 **)(obj + 0x7C);
    f20 = OBJF(0x60);

    /* a1..a3, t0..t2 hold the object's fields at the first jal; passed on (GUESS arity) */
    Vu0Screen_StoreMtx(SPA(0x40), sp1a0, OBJB(0x43), OBJW(0x78), OBJW(0x48), OBJW(0x44), OBJW(0x6C));

    cnt = *(s32 *)(*(u8 **)(obj + 0x70) + 4);
    if (cnt > 0) {
        do {
            ctr = 0;
            s4 = sp190 + (*(s32 *)(s5 + 8) << 4);
            if (*(s32 *)s5 > 0) {
                f21 = 1.0f;
                do {
                    ix = *(s32 *)(s4 + 0);
                    iy = *(s32 *)(s4 + 4);
                    iz = *(s32 *)(s4 + 8);
                    A = s6 + ((u32)(ix * 3) << 4);
                    B = s6 + ((u32)(iy * 3) << 4);
                    C = s6 + ((u32)(iz * 3) << 4);

                    sceVu0ApplyMatrix(SPA(0xF0), obj, A);
                    sceVu0ApplyMatrix(SPA(0x100), obj, B);
                    sceVu0ApplyMatrix(SPA(0x110), obj, C);
                    func_00312680(f20, SPA(0x120), A + 0x20);
                    func_00312680(f20, SPA(0x130), B + 0x20);
                    func_00312680(f20, SPA(0x140), C + 0x20);
                    func_00312638(SPA(0x120), SPA(0x120), SPA(0x180));
                    func_00312638(SPA(0x130), SPA(0x130), SPA(0x180));
                    func_00312638(SPA(0x140), SPA(0x140), SPA(0x180));
                    func_00312668(SPA(0xB0), A + 0x10, SPA(0xE0));
                    func_00312668(SPA(0xC0), B + 0x10, SPA(0xE0));
                    func_00312668(SPA(0xD0), C + 0x10, SPA(0xE0));

                    SPF(0x128) = f21;
                    SPW(0x12C) = 0;
                    SPF(0x138) = f21;
                    SPW(0x13C) = 0;
                    SPF(0x148) = f21;
                    SPW(0x14C) = 0;
                    func_0012D868(SPA(0x80), SPA(0x40), SPA(0xF0), 3, SPA(0x150), SPA(0x120));

                    s0v = SPW(0x88) >> 8;
                    if (sp1a8 != 0) {
                        s0v = 0x1000 - s0v;
                    }
                    if (((u32)s0v < 0x1000u) && (func_001EED70(SPA(0x80)) == 0) && (func_001EED70(SPA(0x90)) == 0)
                        && (func_001EED70(SPA(0xA0)) == 0)) {
                        vv = *(s32 *)(s4 + 0xC);
                        t4 = 0;
                        if (vv >= 0) {
                            if (sp194 != NULL) {
                                t4 = 1;
                                p1b0 = *(s64 *)(sp194 + ((vv + OBJW(0x64)) << 4));
                            }
                        }
                        func_001EDD98(SPA(0x80), SPA(0x90), SPA(0xA0), SPA(0xB0), SPA(0xC0), SPA(0xD0),
                                      SPA(0x150), SPA(0x160), SPA(0x170), sp1a0, sp1a4, t4, sp198,
                                      s0v + sp19c, p1b0);
                    }
                    s4 += 0x10;
                    ctr += 1;
                } while (ctr < *(s32 *)s5);
            }
            s5 += 0x10;
            cnt -= 1;
        } while (cnt != 0);
    }
}
