#include "common.h"

extern u8 *D_00387840;

void func_0018E4C8(s32 arg0, s32 arg1);
void func_0018E098(s32 arg0);
void EftPtcl3_SetStopDelay(s32 arg0, f32 farg0);
void EftPtcl3_Stop(s32 arg0);
void func_001E71D8(s32 arg0, s32 arg1);
void EftChain2_Stop(s32 arg0);

/* cvt.w.s: truncates toward zero. */
/* cvt.w.s truncates toward zero (saturating): plain cast */
static s32 cvt_w_s(f32 x) {
    return (s32)x;
}

void func_001A90A0(u8 *arg0) {
    u8 *s3 = *(u8 **)(D_00387840 + 8);
    u8 *s2 = *(u8 **)(arg0 + 0x38);
    s32 k;

    func_0018E4C8(*(s32 *)(s2 + 0x30), cvt_w_s(*(f32 *)(s3 + 0x0)));
    func_0018E098(*(s32 *)(s2 + 0x30));
    *(s32 *)(s2 + 0x30) = 0;
    EftPtcl3_SetStopDelay(*(s32 *)(s2 + 0x38), *(f32 *)(s3 + 0x4));
    EftPtcl3_SetStopDelay(*(s32 *)(s2 + 0x3C), *(f32 *)(s3 + 0x18));
    for (k = 0; k < 3; k++) {
        EftPtcl3_Stop(*(s32 *)(s2 + 0x38 + k * 4));
        *(s32 *)(s2 + 0x38 + k * 4) = 0;
    }
    func_001E71D8(s2 + 0x4C, cvt_w_s(*(f32 *)(s3 + 0x1C)));
    if (*(s32 *)(s2 + 0x8) == 1) {
        EftChain2_Stop(*(s32 *)(s2 + 0x54));
        *(s32 *)(s2 + 0x54) = 0;
    }
}
