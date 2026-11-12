#include "common.h"
#include "vu0_state.h"

typedef struct Pkt80 { u32 w[20]; } Pkt80;

u8 *func_00269A40(u8 *ctx, s32 key);
s32 func_00269CD8(u8 *ctx, s32 arg1);
s32 func_002674A8(u8 *ctx);
void Dma_AddData(void *data, s32 size);
u8 *Vu1Pkt_CallProg0(u8 *a0);
u8 *Vu1Pkt_CallProg1(u8 *a0);
u8 *Vu1Pkt_CallProg2(u8 *a0);
void Vu0Screen_StoreMtx(u8 *a0);
void Vu0Clip_StoreMtx(u8 *a0);
void ObjDraw_MakeFacingMtx(f32 *out, f32 *vec);
void sceVu0InversMatrix(f32 *out, f32 *in);
void sceVu0CopyMatrix(void *out, void *in);
void sceVu0MulMatrix(f32 *out, f32 *a, f32 *b);
void sceVu0NormalLightMatrix(u8 *out, u8 *a, u8 *b, u8 *c);
extern u8 *gBtlCamView;
extern u8 *D_003876A0;
extern u8 gGfx[] __attribute__((section(".data")));
extern u8 D_002C3630[];
extern u8 D_00344730[];

/* lqc2 / sqc2 through a vf register */
#define LQ(k, p) __builtin_memcpy(gVu0.vf[k], (p), 16)
#define SQ(k, p) __builtin_memcpy((p), gVu0.vf[k], 16)
/* copy a 4x4 matrix with vf1..vf4 */
#define MTXCOPY(dst, src)             \
    LQ(1, (src) + 0x00);              \
    LQ(2, (src) + 0x10);              \
    LQ(3, (src) + 0x20);              \
    LQ(4, (src) + 0x30);              \
    SQ(1, (dst) + 0x00);              \
    SQ(2, (dst) + 0x10);              \
    SQ(3, (dst) + 0x20);              \
    SQ(4, (dst) + 0x30)
/* the common tail: matrices and the two vectors of the record into packet r */
#define FILLPKT(r)                    \
    MTXCOPY((r) + 0x50, s1 + 0x40);   \
    MTXCOPY((r) + 0x10, s1);          \
    LQ(1, s2 + 0x10);                 \
    SQ(1, (r) + 0x90);                \
    LQ(1, s2 + 0x20);                 \
    SQ(1, (r) + 0xA0)

s32 func_00264540(u8 *ctx, u8 *mat, s32 mode, s64 a3, s32 col, u32 shade) {
    f32 m0[16];
    f32 m1[16];
    f32 m2[16];
    f32 vec[4];
    Pkt80 pa;
    Pkt80 pb;
    Pkt80 pc;
    u8 *s2;
    u8 *s1;
    u8 *r;
    s32 ok;
    s32 key;
    s32 res;
    u64 cc;
    u8 *pfx;
    f32 f20;
    s32 bmask;

    shade = shade & 0xFF;
    if (mode == 1) {
        f32 *cv = (f32 *)gBtlCamView;
        vec[0] = cv[2];
        vec[1] = cv[6];
        vec[2] = cv[10];
        vec[3] = 1.0f;
        ObjDraw_MakeFacingMtx(m0, vec);
        sceVu0InversMatrix(m0, m0);
    }
    cc = (u32)(col | 0xFF000000);
    s2 = *(u8 **)(ctx + 0x48);
    pfx = ctx + 0x1C;
    f20 = 128.0f;
    do {
        if (*(u16 *)(s2 + 8) != 0) {
            ok = 1;
            key = *(u16 *)(s2 + 0xA);
            s1 = func_00269A40(ctx, key);
            if (key == 0x76) {
                if ((*(u64 *)(ctx + 0xAF0) & 0x10000002) == 0x10000002) {
                    ok = 0;
                }
            }
            res = func_00269CD8(ctx, *(s32 *)(s1 + 0xD4));
            if (res == 1 && ok != 0) {
                if (mode == 0) {
                    u8 *a0;
                    if (*(u16 *)(s2 + 0xA) == 0x33) {
                        bmask = (*(s32 *)(gGfx + 0x234) & 1) ? 0x80000 : 0x80070;
                        pb.w[0] = 0x10000004;
                        pb.w[1] = 0;
                        pb.w[2] = 0x10000000;
                        pb.w[3] = 0x50000004;
                        pb.w[4] = 0x8003;
                        pb.w[5] = 0x10000000;
                        pb.w[6] = 0xE;
                        pb.w[7] = 0;
                        pb.w[8] = bmask;
                        pb.w[9] = (s32)cc;
                        pb.w[10] = 0x4C;
                        pb.w[11] = 0;
                        pb.w[12] = 0x44;
                        pb.w[13] = 0;
                        pb.w[14] = 0x42;
                        pb.w[15] = 0;
                        pb.w[16] = 0x50000;
                        pb.w[17] = 0;
                        pb.w[18] = 0x47;
                        pb.w[19] = 0;
                        pa = pb;
                        Dma_AddData(&pa, 0x50);
                    }
                    if (*(u16 *)(s2 + 0xA) != 0x30) {
                        a0 = s2 + 0x60;
                    } else if (func_002674A8(ctx) == -1) {
                        a0 = s2 + 0x60;
                    } else {
                        a0 = *(u8 **)(pfx + func_002674A8(ctx) * 4 + 0x738);
                    }
                    r = Vu1Pkt_CallProg0(a0);
                    FILLPKT(r);
                    sceVu0NormalLightMatrix(r + 0xB0, mat + 0x10, D_002C3630, D_002C3630);
                    LQ(1, mat + 0x20);
                    SQ(1, r + 0x170);
                    LQ(1, D_00344730);
                    SQ(1, r + 0x180);
                    Vu0Screen_StoreMtx(r + 0xF0);
                    Vu0Clip_StoreMtx(r + 0x130);
                    if (*(u16 *)(s2 + 0xA) == 0x33) {
                        bmask = (*(s32 *)(gGfx + 0x234) & 1) ? 0x80000 : 0x80070;
                        pc.w[0] = 0x10000004;
                        pc.w[1] = 0;
                        pc.w[2] = 0x10000000;
                        pc.w[3] = 0x50000004;
                        pc.w[4] = 0x8003;
                        pc.w[5] = 0x10000000;
                        pc.w[6] = 0xE;
                        pc.w[7] = 0;
                        pc.w[8] = bmask;
                        pc.w[9] = col;
                        pc.w[10] = 0x4C;
                        pc.w[11] = 0;
                        pc.w[12] = 0x64;
                        pc.w[13] = 0x80;
                        pc.w[14] = 0x42;
                        pc.w[15] = 0;
                        pc.w[16] = 0x50000;
                        pc.w[17] = 0;
                        pc.w[18] = 0x47;
                        pc.w[19] = 0;
                        pb = pc;
                        Dma_AddData(&pb, 0x50);
                    }
                } else if (mode == 1) {
                    if ((*(u16 *)(s2 + 0xC) & 1) != 0) {
                        r = Vu1Pkt_CallProg1(s2);
                        *(s32 *)(r + 0x1B0) = (s32)a3;
                        *(s32 *)(r + 0x1B4) = (s32)(a3 >> 32);
                        *(s32 *)(r + 0x1B8) = 7;
                        *(s32 *)(r + 0x1BC) = 0;
                        FILLPKT(r);
                        *(f32 *)(r + 0x170) = f20;
                        *(f32 *)(r + 0x174) = f20;
                        *(f32 *)(r + 0x178) = f20;
                        *(f32 *)(r + 0x17C) = *(f32 *)(mat + 0x38);
                        *(f32 *)(r + 0x180) = f20;
                        *(f32 *)(r + 0x184) = f20;
                        *(f32 *)(r + 0x188) = f20;
                        *(f32 *)(r + 0x18C) = f20;
                        sceVu0CopyMatrix(m1, s1);
                        ((s32 *)m1)[12] = 0;
                        ((s32 *)m1)[13] = 0;
                        ((s32 *)m1)[14] = 0;
                        sceVu0MulMatrix(m2, m0, m1);
                        sceVu0CopyMatrix(r + 0xB0, m2);
                        *(s32 *)(r + 0xE0) = 0;
                        *(s32 *)(r + 0xE4) = 0;
                        *(s32 *)(r + 0xE8) = 0;
                        Vu0Screen_StoreMtx(r + 0xF0);
                        Vu0Clip_StoreMtx(r + 0x130);
                    }
                } else if (mode == 2) {
                    s32 t = *(s32 *)(s1 + 0xD4);
                    s32 draw = 1;
                    if ((*(u64 *)(D_003876A0 + 0x4D8) & 3) != 0) {
                        if ((u32)(t - 0x31) < 3) {
                            draw = 0;
                        } else if ((t >= 0x15 && t <= 0x1E) || (t >= 0x23 && t <= 0x2C)) {
                            draw = 0;
                        }
                        if (draw) {
                            r = Vu1Pkt_CallProg2(s2);
                        }
                    } else {
                        r = Vu1Pkt_CallProg2(s2);
                    }
                    if (draw) {
                        FILLPKT(r);
                        *(f32 *)(r + 0xBC) = f20;
                        *(f32 *)(r + 0xB8) = (f32)(s32)shade;
                        *(f32 *)(r + 0xB0) = (f32)(s32)shade;
                        *(f32 *)(r + 0xB4) = (f32)(s32)shade;
                    }
                }
            }
        }
        if (*(u16 *)(s2 + 6) != 0) {
            break;
        }
        s2 = s2 + *(s32 *)s2;
    } while (1);
    return *(u16 *)(s2 + 6);
}
