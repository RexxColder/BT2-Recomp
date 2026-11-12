#include "common.h"

void Vec4_Set(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
extern u8 *D_003878E0;
extern u8 *D_003876A0;
extern u8 *D_00387AD8;
extern u8 *D_00387AE4;

void func_001DF600(s32 arg0, f32 farg0) {
    u8 vec[16];
    u8 *pkt;
    u8 *tail;
    f32 limit;
    f32 fx;
    s16 v0Val;
    s16 a1Val;

    if (farg0 <= 0.0f) {
        return;
    }
    if ((*(s32 *)(D_003878E0 + 8) & 8) != 0) {
        return;
    }

    Vec4_Set((s32)vec, 128.0f, 128.0f, 128.0f, farg0);

    pkt = D_00387AD8;
    D_00387AD8 = pkt + 0x40;
    *(s64 *)(pkt + 0x10) = ((s64)0x44000000 << 32) | 0x8001;
    *(s64 *)(pkt + 0x20) = 0x46;
    *(s64 *)(pkt + 0x00) = ((s64)0xA000 << 16) | 3;
    *(s64 *)(pkt + 0x18) = 0x4410;

    limit = 2147483648.0f;
    fx = *(f32 *)(vec + 0x0);
    *(u8 *)(pkt + 0x28) = (u8)(fx < limit ? (s32)fx : (s32)(fx - limit));
    fx = *(f32 *)(vec + 0x4);
    *(u8 *)(pkt + 0x29) = (u8)(fx < limit ? (s32)fx : (s32)(fx - limit));
    fx = *(f32 *)(vec + 0x8);
    *(u8 *)(pkt + 0x2A) = (u8)(fx < limit ? (s32)fx : (s32)(fx - limit));
    fx = *(f32 *)(vec + 0xC);
    *(u8 *)(pkt + 0x2B) = (u8)(fx < limit ? (s32)fx : (s32)(fx - limit));
    *(f32 *)(pkt + 0x2C) = 1.0f;

    if ((*(u64 *)(D_003876A0 + 0x4D8) & 2) == 0) {
        v0Val = 0x7000;
        a1Val = -0x7000;
    } else if (arg0 != 0) {
        v0Val = -0x8000;
        a1Val = -0x7000;
    } else {
        v0Val = 0x7000;
        a1Val = -0x8000;
    }
    *(s16 *)(pkt + 0x32) = 0x7200;
    *(s16 *)(pkt + 0x30) = v0Val;
    *(s16 *)(pkt + 0x38) = a1Val;
    *(s16 *)(pkt + 0x3A) = -0x7200;
    *(u64 *)(pkt + 0x30) = *(u64 *)(pkt + 0x30) | 0x00FFFFFF00000000ULL;
    *(u64 *)(pkt + 0x38) = *(u64 *)(pkt + 0x38) | 0x00FFFFFF00000000ULL;
    *(u8 *)(pkt + 0x37) = 0xFF;
    *(u8 *)(pkt + 0x3F) = 0xFF;

    tail = *(u8 **)(D_00387AE4 + 0xC);
    *(u8 **)(tail + 4) = pkt;
    *(u8 **)(D_00387AE4 + 0xC) = pkt;
}
