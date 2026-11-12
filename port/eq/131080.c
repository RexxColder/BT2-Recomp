#include "common.h"

extern u8 *D_003876A0;
extern u8 *gEftStageScroll;
extern f32 D_00384208;
extern f32 D_0038420C;
extern f32 D_00384210;

f32 EftMath_WrapAngle(f32 farg0);
void EftTexSet_Load32(u8 *arg0, u8 *arg1);
void func_001EC288(u8 *arg0, u8 *arg1);
void func_001EC308(u8 *arg0, u8 *arg1);
s32 func_001EC378(u8 *arg0, s32 arg1);
f32 cosf(f32 farg0);
f32 sinf(f32 farg0);
s32 rand(void);

s32 func_00131080(void) {
    u8 *ctx;
    u8 *arr;
    u8 *cur;
    u8 *tex;
    s32 begin;
    s32 end;
    f32 angle;
    f32 wrapped;
    f32 cosv;
    f32 sinv;

    ctx = D_003876A0;
    if ((*(u64 *)(ctx + 0x4D8) & 0x4000000000000000ULL) != 0) {
        arr = *(u8 **)(ctx + 0x4) + 0x40;
    } else {
        arr = *(u8 **)(ctx + 0x4);
    }
    begin = *(s32 *)(arr + 0x1C);
    end = *(s32 *)(arr + 0x18);

    if (begin == end || *(s32 *)(arr + 0x20) == begin) {
        *(u8 *)(gEftStageScroll + 0x2B0) = 0;
        return (s32)gEftStageScroll;
    }

    *(u8 *)(gEftStageScroll + 0x2B0) = 1;
    cur = arr + ((begin >> 2) << 2);
    tex = arr + ((end >> 2) << 2);

    *(f32 *)(gEftStageScroll + 0x2A4) = (f32)*(s32 *)cur;
    cur += 4;
    *(f32 *)(gEftStageScroll + 0x2A8) = (f32)*(s32 *)cur;
    cur += 4;
    *(f32 *)(gEftStageScroll + 0x2A0) =
        ((f32)*(s32 *)cur * D_00384208) * *(f32 *)(gEftStageScroll + 0x2A4);
    cur += 4;
    *(f32 *)(gEftStageScroll + 0x2AC) = (f32)*(s32 *)cur;
    cur += 4;

    angle = *(f32 *)(gEftStageScroll + 0x2AC);
    if (angle < 0.0f) {
        angle = ((f32)rand() / D_0038420C) * 360.0f;
    }
    wrapped = EftMath_WrapAngle((angle / 180.0f) * D_00384210);
    cosv = cosf(wrapped);
    sinv = sinf(wrapped);
    *(f32 *)(gEftStageScroll + 0x290) = cosv;
    *(f32 *)(gEftStageScroll + 0x294) = sinv;

    EftTexSet_Load32(gEftStageScroll + 0x8, tex);
    func_001EC288(gEftStageScroll + 0x210, cur);
    func_001EC308(gEftStageScroll + 0x210, gEftStageScroll + 0x8);
    return func_001EC378(gEftStageScroll + 0x210, 1);
}
