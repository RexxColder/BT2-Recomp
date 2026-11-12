#include "common.h"

/* 0x0017D658: lays out the particles of a lightning-like bolt between p0 and p1. rec+0 is the head of a linked
 * list of particles (next at +0x30, count rec+8 = number of segments); every particle gets a jittered position
 * (+0x10), a colour (+0x20), a flag (+0, bit 0 always, bit 5 on branch particles) and sizes (+4 / +8). The jitter
 * axes are the bolt direction (p1 - p0), its cross products with rec+0x80, and scale is the argument. */
s32 rand(void);
void func_00312650(u8 *dst, u8 *a, u8 *b);
extern void sceVu0Normalize(u8 *dst, u8 *src);
void func_00312490(u8 *dst, u8 *a, u8 *b);
void func_003126C8(u8 *dst, u8 *src);
void func_00312638(u8 *dst, u8 *a, u8 *b);

extern f32 D_00384A60, D_00384A64, D_00384A68, D_00384A6C, D_00384A70, D_00384A74, D_00384A78, D_00384A7C;
extern f32 D_00384A80, D_00384A84, D_00384A88, D_00384A8C, D_00384A90, D_00384A94, D_00384A98, D_00384A9C;
extern f32 D_00384AA0;

void func_0017D658(u8 *rec, u8 *p0, u8 *p1, f32 scale) {
    u8 sp[0x70];
    f32 *A = (f32 *)sp;
    f32 *B = (f32 *)(sp + 0x10);
    f32 *C = (f32 *)(sp + 0x20);
    f32 *D = (f32 *)(sp + 0x30);
    f32 *n1 = (f32 *)(sp + 0x40);
    f32 *n2 = (f32 *)(sp + 0x50);
    u8 *dir = sp + 0x60;
    u8 *e;
    s32 count;
    s32 i = 0;
    s32 k = 1;
    f32 sgn;
    f32 rdiv = D_00384A60;
    f32 r1, r2, a, b, f;

    r1 = (f32)rand();
    r2 = (f32)rand();
    count = *(s32 *)(rec + 8);
    func_00312650(dir, p1, p0);
    sceVu0Normalize(dir, dir);
    func_00312490(sp + 0x40, dir, rec + 0x80);
    func_00312490(sp + 0x50, sp + 0x40, dir);
    a = (r1 / rdiv + 1.0f) * scale;
    b = (r2 / rdiv + 1.0f) * scale;
    func_003126C8(sp, p0);
    func_003126C8(sp + 0x10, p1);
    sgn = scale;
    e = *(u8 **)rec;
    B[0] = B[0] + n2[0] * a;
    B[1] = B[1] + n2[1] * a;
    B[2] = B[2] + n2[2] * a;
    C[3] = 1.0f;
    C[2] = n2[2] * b;
    C[0] = n2[0] * b;
    C[1] = n2[1] * b;
    if (e == 0) {
        return;
    }

    do {
        *(u32 *)e |= 1;
        if (i == 0) {
            r1 = (f32)rand();
            r2 = (f32)rand();
            f = (r1 / rdiv - r2 / rdiv) * D_00384A74 * scale;
            C[2] = C[2] + n1[2] * f;
            C[0] = C[0] + n1[0] * f;
            C[1] = C[1] + n1[1] * f;
        } else {
            f = ((f32)rand() / rdiv * 0.5f + D_00384A78) * sgn;
            sgn = -sgn;
            count = count - 1;
            if (!(0 < count)) {
                count = 1;
            }
            C[0] = C[0] + n1[0] * f;
            C[2] = C[2] + n1[2] * f;
            C[1] = C[1] + n1[1] * f;
            func_00312638(sp + 0x30, sp, sp + 0x20);
            func_00312650(sp + 0x30, sp + 0x10, sp + 0x30);
            D[2] = D[2] / (f32)count;
            D[0] = D[0] / (f32)count;
            D[1] = D[1] / (f32)count;
            a = ((1.0f - (f32)((count - 1) / *(s32 *)(rec + 8))) * D_00384A7C) + D_00384A68;
            f = ((f32)rand() / rdiv * D_00384A80 + D_00384A84) * a;
            C[2] = C[2] + D[2] * f;
            C[0] = C[0] + D[0] * f;
            C[1] = C[1] + D[1] * f;
        }

        *(f32 *)(e + 0x10) = C[0];
        *(f32 *)(e + 0x14) = C[1];
        *(f32 *)(e + 0x1C) = 1.0f;
        *(f32 *)(e + 0x18) = C[2];
        a = (f32)(count / *(s32 *)(rec + 8));
        f = (((f32)rand() / D_00384A88) * 0.5f + D_00384A8C) * a * sgn;
        C[2] = C[2] + n1[2] * f;
        C[0] = C[0] + n1[0] * f;
        C[1] = C[1] + n1[1] * f;
        f = (((f32)rand() / D_00384A88) * D_00384A68 + D_00384A90) * a * sgn;
        C[0] = C[0] + n2[0] * f;
        C[1] = C[1] + n2[1] * f;
        C[2] = C[2] + n2[2] * f;
        f = (((f32)rand() / D_00384A94) * D_00384A68 + D_00384A98) * scale;
        C[2] = C[2] + n2[2] * f;
        C[0] = C[0] + n2[0] * f;
        C[1] = C[1] + n2[1] * f;
        *(f32 *)(e + 0x20) = 1.0f * 50.0f / 255.0f;
        *(f32 *)(e + 0x24) = 1.0f * 30.0f / 255.0f;
        *(f32 *)(e + 0x28) = 1.0f * 150.0f / 255.0f;
        *(f32 *)(e + 0x0C) = D_00384A9C;
        *(s32 *)(e + 0x2C) = 0;

        if (i != 0 && *(s32 *)(e + 0x30) != 0) {
            k = k + 1;
            *(u32 *)e |= 0x20;
            if (k == 1) {
                *(f32 *)(e + 4) = (f32)rand() / D_00384A94 * D_00384A6C + D_00384A64;
                *(f32 *)(e + 8) = (f32)rand() / D_00384A94 * D_00384A6C + D_00384A64;
            } else {
                *(f32 *)(e + 4) = (f32)rand() / D_00384A94 * D_00384A64 + D_00384A70;
                *(f32 *)(e + 8) = (f32)rand() / D_00384A94 * D_00384A64 + D_00384A70;
            }
            if (!(k < 3)) {
                k = 0;
            }
        } else {
            *(f32 *)(e + 8) = D_00384AA0;
            *(f32 *)(e + 4) = D_00384AA0;
        }
        i = i + 1;
        f = scale * 3.0f;
        *(f32 *)(e + 8) = *(f32 *)(e + 8) * f;
        *(f32 *)(e + 4) = *(f32 *)(e + 4) * f;
        e = *(u8 **)(e + 0x30);
    } while (e != 0);
}
