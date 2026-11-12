#include "common.h"

/* cvt.w.s under the default FCSR rounding mode: truncates toward zero */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(dst, x) do { \
    (dst) = (s32)(x); \
} while (0)

void TexFile_UploadOne(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00271370();
void func_00286B60(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
u8 *func_0029E5D8(s64 arg0, s32 arg1, s32 arg2, s64 arg3);
void Vu0Screen_StoreMtx(u8 *arg0);
void Vu0Clip_StoreMtx(u8 *arg0);
void func_002644F0(s32 arg0);
void ObjGs_AddFadeTex(s64 arg0, s32 arg1);
void func_00264540(u8 *arg0, u8 *arg1, s32 arg2, s64 arg3, s32 arg4, s32 arg5);

void func_002653E8(u8 *arg0, s32 arg1) {
    u8 *a0p;
    u8 *v0p;
    u8 *a1p;
    u8 *s0;
    u8 *s1;
    s64 s3;
    s64 a0v;
    s64 a3v;
    s32 a1v;
    s32 a2v;
    s32 s4;
    s32 lo;
    s32 r;

    a0p = *(u8 **)(arg0 + 0x44);
    if (!(*(s32 *)a0p & 1)) {
        return;
    }
    s0 = arg0 + 0xAF0;
    if ((*(s64 *)s0 & 0xA) != 0xA) {
        return;
    }
    if (*(s32 *)s0 & 0x200000) {
        return;
    }

    s4 = 0;
    TexFile_UploadOne(*(u8 **)(arg0 + 0x4C), *(u8 *)(a0p + 0x23), *(s32 *)(s0 + 0xC4), *(s32 *)(s0 + 0xC8));
    func_00271370();
    v0p = *(u8 **)(arg0 + 0x44);
    func_00286B60(*(u8 **)(arg0 + 0x4C), *(u8 *)(v0p + 0x28), *(u8 *)(v0p + 0x29), *(s32 *)(s0 + 0xBC), *(s32 *)(s0 + 0xC0));
    func_00271370();

    a3v = (s64)0xC000 << 20;
    a0p = *(u8 **)(arg0 + 0x44);
    v0p = *(u8 **)(arg0 + 0x4C);
    a1v = *(s32 *)(v0p + 0x10);
    a1p = (u8 *)(s64)a1v;
    a0v = (s64)*(s32 *)(s0 + 0xC8) << 37;
    a2v = *(s32 *)(s0 + 0xC4);
    s3 = *(s64 *)(a1p + ((*(u8 *)(a0p + 0x23)) << 6) + 0x30) | a0v | (s64)a2v | a3v;
    s0 = func_0029E5D8(a0v, a1v, a2v, a3v);
    Vu0Screen_StoreMtx(s0 + 0xF0);
    Vu0Clip_StoreMtx(s0 + 0x130);

    if (arg1 <= 0) {
        return;
    }
    s1 = arg0;
    do {
        if (arg1 >= 2) {
            func_002644F0(s4);
        }
        s0 = s1 + 0xB00;
        s1 += 0x40;
        if ((*(s64 *)s0 & 0xA) == 0xA) {
            lo = *(s32 *)s0;
            if (!(lo & 0x100000) && !(lo & 0x200000)) {
                CVT_W_S(r, *(f32 *)(s0 + 0x38));
                ObjGs_AddFadeTex(s3, r);
                func_00264540(arg0, s0, 1, s3, 0, 0);
            }
        }
        s4 += 1;
    } while (s4 < arg1);
}
