#include "common.h"

#define TAB() (*(u8 **)(gBtlStage + 0x5C))

extern u8 *gBtlStage;
extern f32 D_00386FE0;
extern f32 D_00386FE4;
extern f32 D_00386FE8;
extern f32 D_00386FEC;
extern f32 D_00386FF0;
extern f32 D_00386FF4;
extern f32 D_00386FF8;
extern f32 D_00386FFC;
extern f32 D_00387000;

void func_003126C8(u8 *arg0, u8 *arg1);
void func_002102B0(u8 *arg0, s32 arg1, f32 farg0, f32 farg1);
void func_0020D048(u8 *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_0020D240(u8 *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);

s32 func_00274338(s32 arg0, u8 *arg1) {
    u8 sp[0x10];
    u8 *s0 = NULL;
    u8 *s1;
    s32 s3 = 0;
    s32 v;
    s32 idx;
    s32 a0;
    f32 f12;
    f32 f13;
    f32 f14;
    f32 f15;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23 = 1.0f;
    f32 f24;

    s1 = TAB() + (*(s32 *)(gBtlStage + 0x48) << 2) + arg0 * 0x50;
    if (*(s32 *)(s1 + 0) & 1) {
        return 0;
    }
    idx = *(s32 *)(s1 + 0xC);
    if (idx != 0) {
        s0 = TAB() + (idx << 2);
        *(u16 *)(s0 + 2) = (u16)(*(u16 *)(s0 + 2) & 0xFFFE);
    }
    if (s0 != NULL) {
        func_003126C8(sp, s0 + 0x10);
        f23 = *(f32 *)(s0 + 0xC);
        s3 = 1;
    }
    idx = *(s32 *)(s1 + 0x14);
    if (idx != 0) {
        s0 = TAB() + (idx << 2);
        *(u16 *)(s0 + 2) = (u16)(*(u16 *)(s0 + 2) & 0xFFFE);
    }
    idx = *(s32 *)(s1 + 0x1C);
    if (idx != 0) {
        s0 = TAB() + (idx << 2);
        *(u16 *)(s0 + 2) = (u16)(*(u16 *)(s0 + 2) & 0xFFFE);
    }
    idx = *(s32 *)(s1 + 0x10);
    if (idx != 0) {
        s0 = TAB() + (idx << 2);
        *(u16 *)(s0 + 2) = (u16)(*(u16 *)(s0 + 2) | 1);
    }
    idx = *(s32 *)(s1 + 0x18);
    if (idx != 0) {
        s0 = TAB() + (idx << 2);
        *(u16 *)(s0 + 2) = (u16)(*(u16 *)(s0 + 2) | 1);
    }
    idx = *(s32 *)(s1 + 0x20);
    if (idx != 0) {
        s0 = TAB() + (idx << 2);
        *(u16 *)(s0 + 2) = (u16)(*(u16 *)(s0 + 2) | 1);
    }
    *(s32 *)(s1 + 0x8) = 0;
    *(s32 *)(s1 + 0x0) = 3;
    *(s32 *)(s1 + 0x30) = 0;
    func_003126C8(s1 + 0x40, arg1);
    if (s3 == 0) {
        return 1;
    }
    func_002102B0(sp, 8, f23 + 200.0f, f23 + D_00386FE0);
    v = *(s32 *)(s1 + 0x34);
    if (v & 0x70) {
        f15 = 0.0f;
        f22 = 100.0f;
        a0 = 0;
        f20 = f15;
        f14 = f15;
        f13 = D_00386FE4;
        f24 = 1000.0f;
        f21 = f20;
        if (v & 0x10) {
            f14 = 1.0f;
            a0 = 1;
            f15 = D_00386FE8;
            f21 = 0.5f;
            f20 = D_00386FEC;
        }
        if (v & 0x20) {
            f14 = 2.0f;
            a0 = 1;
            f15 = 0.5f;
            f21 = D_00386FF0;
            f20 = D_00386FF4;
        }
        if (v & 0x40) {
            f14 = 3.0f;
            a0 = 1;
            f15 = D_00386FF8;
            f21 = 1.0f;
            f20 = D_00386FFC;
            f22 = 300.0f;
            f13 = D_00387000;
            f24 = 1000.0f;
        }
        if (a0 != 0) {
            f22 = f22 + f23;
            f13 = f13 + f23;
            f24 = f24 + f23;
            f12 = f22;
            func_0020D048(sp, f12, f13, f14, f15);
            func_0020D240(sp, f22, f24, f21, f20);
        }
    }
    return 1;
}
