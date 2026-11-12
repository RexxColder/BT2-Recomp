#include "common.h"

u8 *func_003B4B58(u8 *arg0);
void func_2B7290(u8 *arg0, s32 arg1, u8 *arg2);
void func_003B50B0(u8 *arg0, s32 arg1);
void func_003B5158(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4);
void func_003B5288(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4);

/* 0x003B48F8: s1 = func_003B4B58(arg0) (arg0 passed through, GUESS arity 1); if s1 == 0 return 0. Copies the 0x18-byte
 * record arg0 to s1+0x1AC; word0 w: s1->0xC4 = (w >= 0x33B2), dst word0 = w < 0x33B2 ? w : w - 0x33B2; s1->0xCC = 2,
 * s1->0xC8 = 0, s1->0xD0 = 0; func_2B7290(s1->0xC0, 1, s1+0x1AC); func_003B50B0(s1, s1->0x1B0); then the float
 * vectors (rows 0..3 = {0,0,1,1},{1,0,1,1},{0,1,1,1},{1,1,1,1}; then 128.0 x16) through func_003B5158 and func_003B5288;
 * returns s1. */
u8 *func_003B48F8(u8 *arg0) {
    u8 *s1;
    f32 sp[32];
    s32 w;
    s32 i;

    s1 = func_003B4B58(arg0);
    if (s1 == 0) {
        return s1;
    }
    memcpy(s1 + 0x1AC, arg0, 0x18);
    w = *(s32 *)arg0;
    *(s32 *)(s1 + 0xC4) = (w >= 0x33B2);
    *(s32 *)(s1 + 0x1AC) = (w < 0x33B2) ? w : w - 0x33B2;
    *(s32 *)(s1 + 0xCC) = 2;
    *(s32 *)(s1 + 0xC8) = 0;
    *(s32 *)(s1 + 0xD0) = 0;
    func_2B7290(*(u8 **)(s1 + 0xC0), 1, s1 + 0x1AC);
    func_003B50B0(s1, *(s32 *)(s1 + 0x1B0));

    sp[0] = 0.0f;
    sp[1] = 0.0f;
    sp[2] = 1.0f;
    sp[3] = 1.0f;
    sp[4] = 1.0f;
    sp[5] = 0.0f;
    sp[6] = 1.0f;
    sp[7] = 1.0f;
    sp[8] = 0.0f;
    sp[9] = 1.0f;
    sp[10] = 1.0f;
    sp[11] = 1.0f;
    sp[12] = 1.0f;
    sp[13] = 1.0f;
    sp[14] = 1.0f;
    sp[15] = 1.0f;
    for (i = 16; i < 32; i++) {
        sp[i] = 128.0f;
    }
    func_003B5158(s1, &sp[0], &sp[4], &sp[8], &sp[12]);
    func_003B5288(s1, &sp[16], &sp[20], &sp[24], &sp[28]);
    return s1;
}
