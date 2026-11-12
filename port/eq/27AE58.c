#include "common.h"

#define FL(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))

extern u8 *D_00387AEC;

void func_0027AE58(void *arg0) {
    u8 *P;
    u8 *D;
    u8 *t0;
    u8 *a0;
    u8 *v1;
    u8 *a0_2;
    u8 *v1_2;
    u8 *a0_3;
    u8 *v1_3;
    u8 *a0_4;
    s32 t4;
    s32 t1;
    s32 done;
    f32 temp_f1;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 f5;
    f32 f3;
    f32 f7;
    f32 f3_2;
    f32 f3_3;
    f32 q;

    P = (u8 *)arg0;
    temp_f1 = FL(P, 0x8) - 1.0f;
    FL(P, 0x8) = temp_f1;
    done = 0;
    if (temp_f1 <= 0.0f) {
        done = 1;
    } else {
        temp_f0 = FL(P, 0xC) + FL(P, 0x10);
        FL(P, 0xC) = temp_f0;
        if (600.0f < temp_f0) {
            done = 1;
        }
    }
    if (done) {
        W(P, 0x0) = 0;
        if (W(P, 0x4) == 0) {
            W(D_00387AEC, 0xA8) = W(D_00387AEC, 0xA8) - 1;
            return;
        }
        W(D_00387AEC, 0xAC) = W(D_00387AEC, 0xAC) - 1;
        return;
    }

    t4 = 0;
    while (t4 < 0x14) {
        D = D_00387AEC;
        t1 = t4 * 8;
        f5 = FL(P, 0xC);
        t0 = P + 8;
        f3 = FL(P, 0x18);
        a0 = t0 + (t1 + 0x250);
        v1 = t0 + (t1 + 0x254);
        f7 = f5 + f3;
        f3_2 = f5 + (f3 * 0.5f);
        *(f32 *)a0 = FL(P, 0x450) + ((*(f32 *)(D + t1 + 4) * f5) * 0.5f);
        *(f32 *)v1 = FL(P, 0x454) + ((*(f32 *)(D + t1 + 8) * f5) * 0.5f);
        if (*(f32 *)a0 < 0.0f) {
            *(f32 *)a0 = 0.0f;
        }
        if (*(f32 *)v1 < 0.0f) {
            *(f32 *)v1 = 0.0f;
        }
        a0_2 = t0 + (t1 + 0x2F0);
        v1_2 = t0 + (t1 + 0x2F4);
        *(f32 *)a0_2 = FL(P, 0x450) + ((*(f32 *)(D + t1 + 4) * f3_2) * 0.5f);
        *(f32 *)v1_2 = FL(P, 0x454) + ((*(f32 *)(D + t1 + 8) * f3_2) * 0.5f);
        if (*(f32 *)a0_2 < 0.0f) {
            *(f32 *)a0_2 = 0.0f;
        }
        if (*(f32 *)v1_2 < 0.0f) {
            *(f32 *)v1_2 = 0.0f;
        }
        a0_3 = t0 + (t1 + 0x390);
        v1_3 = t0 + (t1 + 0x394);
        *(f32 *)a0_3 = FL(P, 0x450) + ((*(f32 *)(D + t1 + 4) * f7) * 0.5f);
        *(f32 *)v1_3 = FL(P, 0x454) + ((*(f32 *)(D + t1 + 8) * f7) * 0.5f);
        if (*(f32 *)a0_3 < 0.0f) {
            *(f32 *)a0_3 = 0.0f;
        }
        if (*(f32 *)v1_3 < 0.0f) {
            *(f32 *)v1_3 = 0.0f;
        }
        a0_4 = t0 + t1;
        q = *(f32 *)(t0 + (t4 * 4) + 0x20);
        temp_f0_2 = FL(P, 0x18) * q;
        t4 += 1;
        f3_3 = f5 + temp_f0_2;
        FL(a0_4, 0x70) = FL(P, 0x438) + (*(f32 *)(D + t1 + 4) * f5);
        FL(a0_4, 0x74) = FL(P, 0x43C) + (*(f32 *)(D + t1 + 8) * f5);
        FL(a0_4, 0x110) = FL(P, 0x438) + (*(f32 *)(D + t1 + 4) * f3_3);
        FL(a0_4, 0x114) = FL(P, 0x43C) + (*(f32 *)(D + t1 + 8) * f3_3);
        FL(a0_4, 0x1B0) = FL(P, 0x438) + (*(f32 *)(D + t1 + 4) * f7);
        FL(a0_4, 0x1B4) = FL(P, 0x43C) + (*(f32 *)(D + t1 + 8) * f7);
    }

    FL(P, 0x10) = FL(P, 0x10) + FL(P, 0x14);
    FL(P, 0x18) = FL(P, 0x18) + FL(P, 0x1C);
    if (FL(P, 0x8) <= 6.0f) {
        temp_f0_3 = FL(P, 0x20) + FL(P, 0x24);
        FL(P, 0x20) = temp_f0_3;
        if (temp_f0_3 < 0.0f) {
            FL(P, 0x20) = 0.0f;
        }
    }
}
