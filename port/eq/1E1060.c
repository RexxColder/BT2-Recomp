#include "common.h"

f32 func_001E1F08(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_001E4FB8(s32 arg0, s32 arg1);
s32 rand(void);

extern f32 D_00385660;

void func_001E1060(u8 *arg0, s32 arg1, f32 t) {
    f32 var_f0;
    f32 q;
    s32 rq;
    f32 dd;
    s32 a1v;
    s32 tmp;
    s32 idx;
    s32 v;
    s32 v3;

    if (t < *(f32 *)(arg0 + 0x68)) {
        return;
    }
    if (*(f32 *)(arg0 + 0x70) <= t) {
        if (func_001E4FB8(arg1, (s32)arg0) == 0) {
            return;
        }
    }

    var_f0 = *(f32 *)(arg0 + 0x6C);
    if (t < var_f0) {
        func_001E1F08(*(f32 *)(arg0 + 0x74), (s32)(arg0 + 0x10), (s32)(arg0 + 0x60), (s32)(arg0 + 0x90), (s32)(arg0 + 0xF0));
        var_f0 = *(f32 *)(arg0 + 0x6C);
    }
    if (var_f0 <= t) {
        var_f0 = *(f32 *)(arg0 + 0x70);
        if (t < var_f0) {
            var_f0 = func_001E1F08(*(f32 *)(arg0 + 0x78), (s32)(arg0 + 0x10), (s32)(arg0 + 0x60), (s32)(arg0 + 0xA0), (s32)(arg0 + 0x100));
        }
    }

    if (*(u8 *)(arg0 + 0x16E) == 0) {
        return;
    }

    if (*(s32 *)(arg0 + 0x174) != 0 && *(s32 *)(arg0 + 0x178) != 0) {
        a1v = *(s32 *)(arg0 + 0x17C);
        tmp = -a1v;
        idx = (s32)(((u32)~a1v) >> 31);
        if (*(s32 *)(arg0 + 0x198) >= *(s32 *)(arg0 + 0x174 + idx * 4)) {
            *(s32 *)(arg0 + 0x198) = 0;
            *(s32 *)(arg0 + 0x17C) = tmp;
            a1v = tmp;
        }
        if (a1v < 0) {
            *(u8 *)(arg0 + 0x16B) = 0;
        } else {
            *(u8 *)(arg0 + 0x16B) = 1;
        }
    }

    v = *(u8 *)(arg0 + 0x180);
    if (v == 0) {
        /* cvt.w.s: truncates toward zero */
        rq = (s32)var_f0;
        if (rq & 1) {
            goto end_block;
        }
    }

    v3 = *(s32 *)(arg0 + 0x184);
    if (v3 == 1) {
        q = (f32)rand() / D_00385660 * (f32)*(s32 *)(arg0 + 0x190);
        dd = q;
        rq = (s32)dd;
        *(s32 *)(arg0 + 0x198) = *(s32 *)(arg0 + 0x198) + 1;
        *(s32 *)(arg0 + 0x194) = *(s32 *)(arg0 + 0x194) + rq;
    } else {
        *(s32 *)(arg0 + 0x194) = *(s32 *)(arg0 + 0x194) + 1;
        *(s32 *)(arg0 + 0x198) = *(s32 *)(arg0 + 0x198) + 1;
    }

end_block:
    if (!(*(s32 *)(arg0 + 0x194) < *(s32 *)(arg0 + 0x190))) {
        *(s32 *)(arg0 + 0x194) = 0;
    }
    if (*(f32 *)(arg0 + 0x4C) <= 0.0f) {
        *(u8 *)(arg0 + 0x16B) = 0;
    }
}
