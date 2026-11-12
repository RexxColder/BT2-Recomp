#include "common.h"

void func_0018E4C8(void *a0, s32 a1);
void func_0018E098(void *a0);
void EftPtcl3_SetStopDelay(void *a0, f32 f12);
void EftPtcl3_Stop(void *a0);
void func_001E71D8(void *a0, s32 a1);
void EftChain2_Stop(void *a0);
extern u8 *D_003878F4;
extern f32 D_00385A34;

/* truncates toward zero, written out */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(x, out) { (out) = (s32)(x); }

void func_001E8450(void *arg0) {
    u8 *s2;
    u8 *s3;
    u8 *s0;
    u8 *s1;
    s32 s4;
    s32 rnd;

    s3 = *(u8 **)(D_003878F4 + 0x210);
    s2 = *(u8 **)((u8 *)arg0 + 0x38);
    CVT_W_S(*(f32 *)s3, rnd);
    func_0018E4C8(*(void **)(s2 + 0x6C), rnd);
    s0 = s2 + 0x6C;
    s1 = s2 + 0x74;
    func_0018E098(*(void **)s0);
    *(s32 *)s0 = 0;
    EftPtcl3_SetStopDelay(*(void **)(s2 + 0x74), *(f32 *)(s3 + 4));
    EftPtcl3_SetStopDelay(*(void **)(s2 + 0x78), *(f32 *)(s3 + 0x18));
    s4 = 2;
    do {
        EftPtcl3_Stop(*(void **)s1);
        s4 -= 1;
        *(s32 *)s1 = 0;
        s1 += 4;
    } while (s4 >= 0);
    CVT_W_S(*(f32 *)(s3 + 0x1C), rnd);
    func_001E71D8(s2 + 0x88, rnd);
    EftChain2_Stop(*(void **)(s2 + 0x90));
    *(s32 *)(s2 + 0x90) = 0;
}
