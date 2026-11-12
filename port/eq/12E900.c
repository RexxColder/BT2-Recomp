#include "common.h"

#define FL(p, o) (*(f32 *)((u8 *)(p) + (o)))

void sceVu0MulMatrix(s32 a0, s32 a1, s32 a2);
void sceVu0UnitMatrix(s32 a0);
extern u8 *D_003876A0;
extern u8 *D_00387714;
extern u8 *gBtlCam;
extern u8 *gBtlCamView;

void func_0012E900(void) {
    f32 A[16];
    f32 B[16];
    u8 *S;
    u8 *V;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f20;
    f32 f21;
    f32 f23;

    S = gBtlCamView;
    if (*(s64 *)(D_003876A0 + 0x4D8) & 2) {
        if (*(s32 *)(*(u8 **)(gBtlCam + 0x600) + 0x250) != 0) {
            f23 = 2080.0f;
        } else {
            f23 = 2016.0f;
        }
    } else {
        f23 = 2048.0f;
    }
    V = D_00387714;
    *(f32 *)(V + 0x40) = FL(S, 0x224) * 0.25f;
    f2 = FL(S, 0x23C);
    f3 = FL(S, 0x240);
    f1 = FL(S, 0x244);
    f0 = FL(S, 0x238);
    f21 = (f1 * f3 * (f2 - f0)) / (f1 - f3);
    f20 = ((-f2 * f3) + (f0 * f1)) / (f1 - f3);

    sceVu0UnitMatrix((s32)A);
    f1 = FL(S, 0x248);
    A[0] = FL(S, 0x224) * f1;
    A[5] = FL(S, 0x224) * FL(S, 0x248);
    A[10] = 0.0f;
    A[11] = 1.0f;
    A[14] = 1.0f;
    A[15] = 0.0f;
    sceVu0UnitMatrix((s32)B);
    B[0] = FL(S, 0x228);
    B[5] = FL(S, 0x22C);
    B[10] = f21;
    B[12] = f23;
    B[13] = 2048.0f;
    B[14] = f20;
    sceVu0MulMatrix((s32)A, (s32)B, (s32)A);
    A[0] = A[0] * 0.25f;
    A[5] = A[5] * 0.25f;
    sceVu0MulMatrix((s32)V, (s32)A, (s32)S);
}
