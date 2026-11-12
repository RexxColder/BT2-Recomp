#include "common.h"

typedef s32 (*Vec4SetWide)(void *, void *, s32, s32, s32, s32, s32, s32,
                           s64, s64, s64, s64, s64, s64, s64, s64,
                           f32, f32, f32, f32);

s32 Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
void func_00128C58(f32 farg0, void *arg0, void *arg1);
void Mtx_Translate(void *arg0, void *arg1, void *arg2);
void Mtx_RotateX(void *arg0, void *arg1, f32 farg0);
void Mtx_RotateY(void *arg0, void *arg1, f32 farg0);
void Mtx_RotateZ(void *arg0, void *arg1, f32 farg0);
void func_00129C50(void *arg0, void *arg1, void *arg2);
f32 EftMath_WrapAngle(f32 farg0);
f32 Mathf_Asin(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);

void func_0018A2C8(u8 *arg0, u8 *arg1, u8 *arg2, f32 farg12, f32 farg13, f32 farg14,
                   f32 farg15, f32 farg16) {
    s64 sp[14];
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    void *m;

    /* frame copies: the 64-byte struct at a1 (also the stack args of the first call), the vec at a2 */
    sp[0] = *(s64 *)(arg1 + 0x00);
    sp[1] = *(s64 *)(arg1 + 0x08);
    sp[2] = *(s64 *)(arg1 + 0x10);
    sp[3] = *(s64 *)(arg1 + 0x18);
    sp[4] = *(s64 *)(arg1 + 0x20);
    sp[5] = *(s64 *)(arg1 + 0x28);
    sp[6] = *(s64 *)(arg1 + 0x30);
    sp[7] = *(s64 *)(arg1 + 0x38);
    sp[8] = *(s64 *)(arg2 + 0x00);
    sp[9] = *(s64 *)(arg2 + 0x08);

    f20 = *(f32 *)(arg0 + 0x88) * 0.5f;
    f23 = 0.0f;
    f22 = -f20;
    f21 = 1.0f;

    /* first call: 8 int regs (a0 = &sp60, a1 = a1, a2..t3 from a1), 8 stack slots, f12..f15 */
    ((Vec4SetWide)Vec4_Set)((void *)&sp[12], arg1,
                            (s32)sp[4], (s32)sp[3], (s32)sp[1], (s32)sp[2], (s32)sp[0], (s32)sp[7],
                            sp[0], sp[1], sp[2], sp[3], sp[4], sp[5], sp[6], sp[7],
                            farg15 * f20, farg16 * f20, f23, f21);

    func_00129BD0((void *)&sp[10], arg0, farg12);

    Vec4_Set(arg0 + 0x40, f22, f22, f23, f21);
    Vec4_Set(arg0 + 0x50, f22, f20, f23, f21);
    Vec4_Set(arg0 + 0x60, f20, f22, f23, f21);
    Vec4_Set(arg0 + 0x70, f20, f20, f23, f21);

    m = (void *)sp;
    Mtx_Translate(m, m, (void *)&sp[12]);
    func_00128C58(farg12, m, m);
    Mtx_RotateZ(m, m, EftMath_WrapAngle(*(f32 *)(arg0 + 0xA4) + *(f32 *)(arg0 + 0xAC)));

    f20 = Mathf_Asin(-*(f32 *)(arg0 + 0x14));
    f21 = atan2f(*(f32 *)(arg0 + 0x10), *(f32 *)(arg0 + 0x18));
    Mtx_RotateX(m, m, EftMath_WrapAngle(f20));
    Mtx_RotateY(m, m, EftMath_WrapAngle(f21));
    Mtx_Translate(m, m, (void *)&sp[10]);
    Mtx_RotateX(m, m, EftMath_WrapAngle(farg13));
    Mtx_RotateY(m, m, EftMath_WrapAngle(farg14));
    Mtx_Translate(m, m, (void *)&sp[8]);

    func_00129C50(arg0 + 0x40, m, arg0 + 0x40);
    func_00129C50(arg0 + 0x50, m, arg0 + 0x50);
    func_00129C50(arg0 + 0x60, m, arg0 + 0x60);
    func_00129C50(arg0 + 0x70, m, arg0 + 0x70);
}
