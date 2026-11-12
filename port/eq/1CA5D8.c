#include "common.h"

extern u8 *gBtlCamView;
extern f32 D_003851C4;
extern f32 D_003851C8;
extern f32 D_003851CC;
extern f32 D_003851D0;

f32 func_00129CD8(void *arg0, void *arg1, f32 farg0);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
void func_00129C38(void *arg0, void *arg1);
void Vec3_Sub(f32 *arg0, f32 *arg1, f32 *arg2);
void Vec3_Add(f32 *arg0, f32 *arg1, f32 *arg2);
void Vec3_Normalize(f32 *arg0, f32 *arg1);
void Vec3_Cross(f32 *arg0, f32 *arg1, f32 *arg2);
void Mtx_StoreIdentity(void *arg0);

void func_001CA5D8(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 farg0) {
    f32 b[20];
    f32 *V0 = b;
    f32 *V1 = b + 4;
    f32 *V2 = b + 8;
    f32 *A = b + 12;
    f32 *B = b + 16;
    f32 f22;
    f32 f21;
    f32 f1r;

    A[0] = *(f32 *)(gBtlCamView + 8);
    A[1] = *(f32 *)(gBtlCamView + 0x18);
    A[2] = *(f32 *)(gBtlCamView + 0x28);
    A[3] = 1.0f;

    f22 = func_00129CD8(A, arg1, farg0);
    if (f22 < 0.0f) {
        f21 = -f22 * D_003851C4;
        func_00129BD0(B, A, -1.0f);
    } else {
        f21 = f22 * D_003851C8;
        func_00129C38(B, A);
    }
    B[3] = 1.0f;
    Vec3_Sub(B, arg1, B);
    Vec3_Normalize(B, B);
    func_00129BD0(B, B, f21);
    Vec3_Add(V2, arg1, B);
    V2[3] = 1.0f;
    Vec3_Normalize(V2, V2);

    /* second call: the asm sets a0 and a1 only (f12 is garbage here), so the float is not passed */
    f1r = ((f32 (*)(void *, void *))func_00129CD8)(A, arg2);
    if (f22 < 0.0f) {
        f21 = -f1r * D_003851CC;
        func_00129BD0(B, A, -1.0f);
    } else {
        f21 = f1r * D_003851D0;
        func_00129C38(B, A);
    }
    B[3] = 1.0f;
    Vec3_Sub(B, arg2, B);
    Vec3_Normalize(B, B);
    func_00129BD0(B, B, f21);
    Vec3_Add(V0, arg2, B);
    V0[3] = 1.0f;
    Vec3_Normalize(V0, V0);
    Vec3_Cross(V1, V2, V0);
    Vec3_Normalize(V1, V1);

    Mtx_StoreIdentity(arg0);
    arg0[0] = V0[0];
    arg0[1] = V0[1];
    arg0[2] = V0[2];
    arg0[4] = V1[0];
    arg0[5] = V1[1];
    arg0[6] = V1[2];
    arg0[8] = V2[0];
    arg0[9] = V2[1];
    arg0[10] = V2[2];
    arg0[12] = arg3[0];
    arg0[13] = arg3[1];
    arg0[14] = arg3[2];
}
