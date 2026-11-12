#include "common.h"

s32 Vec4_Set(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
f32 Mathf_Asin(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
void Mtx_StoreIdentity(s32 arg0);
void Mtx_RotateX(f32 farg0, s32 arg1, s32 arg2);
void Mtx_RotateY(f32 farg0, s32 arg1, s32 arg2);
void func_00191BC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00191C00(s32 arg0, s32 arg1);

void func_001929C0(u8 *arg0, u8 *arg1) {
    u8 *s2;
    u8 *s3;
    u8 *s4;
    s32 temp_v0;
    s32 prod;
    f32 f1;

    s3 = arg0 + 0x130;
    s4 = arg0 + 0x170;
    temp_v0 = *(s32 *)(arg0 + 0x60);
    s2 = *(u8 **)(arg1 + 0x38);
    *(s32 *)(arg0 + 0x60) = temp_v0 | 1;
    f1 = *(f32 *)arg1;
    if (f1 <= 0.0f) {
        *(s32 *)(arg0 + 0x60) = temp_v0 | 9;
    } else {
        *(f32 *)(arg0 + 0x118) = f1 * 30.0f;
    }
    if (*(u8 *)(s2 + 1) == 1) {
        Vec4_Set((s32)(arg1 + 0x20), 0.0f, 0.0f, 1.0f, 1.0f);
    }
    Mtx_StoreIdentity((s32)s3);
    *(f32 *)(arg0 + 0x1B0) = Mathf_Asin(-*(f32 *)(arg1 + 0x24));
    *(f32 *)(arg0 + 0x1B4) = atan2f(*(f32 *)(arg1 + 0x20), *(f32 *)(arg1 + 0x28));
    Mtx_RotateX(*(f32 *)(arg0 + 0x1B0), (s32)s4, (s32)s3);
    Mtx_RotateY(*(f32 *)(arg0 + 0x1B4), (s32)s4, (s32)s4);
    func_00191C00((s32)arg0, (s32)arg1);
    prod = *(s32 *)(s2 + 0x14) * *(s32 *)(s2 + 0x18);
    *(s32 *)(arg0 + 0x1BC) = prod;
    if (prod >= 2) {
        *(s32 *)(arg0 + 0x60) = *(s32 *)(arg0 + 0x60) | 0x20;
        *(f32 *)(arg0 + 0x1C0) = 1.0f / (f32)*(s32 *)(s2 + 0x14);
        *(f32 *)(arg0 + 0x1C4) = 1.0f / (f32)*(s32 *)(s2 + 0x18);
    }
    func_00191BC8((s32)arg0, *(s32 *)(arg1 + 0x34), *(s32 *)(arg1 + 0x30), *(s32 *)(arg1 + 0x30));
}
