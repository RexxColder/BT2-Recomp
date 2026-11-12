#include "common.h"

void Mtx_StoreIdentity(s32 arg0);
void Mtx_RotateY(f32 farg0, s32 arg1, s32 arg2);
void EftMath_MtxFromDir(s32 arg0, s32 arg1, f32 farg0);
void Mtx_Mul(s32 arg0, s32 arg1, s32 arg2);
void func_00128900(s32 arg0, s32 arg1);
void func_00183AE8(s32 arg0, s32 arg1, s32 arg2);
extern f32 D_00384B88;
extern u8 *D_00387A40;

void func_00183CC0(u8 *arg0) {
    f32 m1[16];
    f32 m2[16];
    f32 f1;
    u8 *s2;
    u8 *s3;

    s3 = (u8 *)(*(s32 *)(D_00387A40 + 8) + *(s32 *)(arg0 + 0xB08) * 0x1520);
    s2 = s3 + 0x9A0;
    if (*(u16 *)(arg0 + 0xAD6) & 0x20) {
        func_00183AE8((s32)arg0, 1, (s32)D_00387A40);
    } else {
        func_00183AE8((s32)arg0, 0, (s32)D_00387A40);
    }
    Mtx_StoreIdentity((s32)m1);
    Mtx_StoreIdentity((s32)m2);
    Mtx_RotateY(D_00384B88, (s32)m1, (s32)m1);
    EftMath_MtxFromDir((s32)m2, (s32)(arg0 + 0xA90), 0.0f);
    Mtx_Mul((s32)m2, (s32)m2, (s32)m1);
    f1 = *(f32 *)(arg0 + 0xA38) * *(f32 *)(arg0 + 0xB0C);
    m2[10] *= f1;
    m2[0] *= f1;
    m2[5] *= f1;
    func_00128900((s32)(s2 + 0x60), (s32)m2);
    *(f32 *)(s2 + 0x90) = *(f32 *)(arg0 + 0xA70);
    *(f32 *)(s2 + 0x94) = *(f32 *)(arg0 + 0xA74) + *(f32 *)(arg0 + 0xB20);
    *(f32 *)(s2 + 0x98) = *(f32 *)(arg0 + 0xA78);
    *(s8 *)(s3 + 0xAEC) = 0;
}
