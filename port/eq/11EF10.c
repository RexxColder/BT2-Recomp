#include "common.h"

u8 *func_00126040(void *arg0);
s32 func_00126058(u8 *arg0, s32 arg1, s32 arg2);
f32 BtlCharApi_GetHeight(s32 arg0);
u8 *BtlMember_GetActiveGauge(u8 *arg0);
s32 func_00241718(u8 *arg0, s32 arg1);
f32 func_0011EB68(u8 *arg0);
f32 func_0011EBC8(u8 *arg0);
extern f32 D_00384084;
extern f32 D_00384088;
extern f32 D_0038408C;
extern f32 D_00384090;

s32 func_0011EF10(u8 *arg0, u8 *arg1) {
    u8 *s3;
    u8 *q;
    u8 *g;
    s32 n;
    s32 op;
    s32 r;
    f32 fn;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f20;
    f32 h;

    s3 = func_00126040(arg0);
    n = (s8)arg1[0xB];
    op = (s8)arg1[0xA];
    q = arg0 + 0x1080;
    fn = (f32)n;
    if ((u32)op >= 0x13) {
        return 0;
    }

    switch (op) {
    case 0:
        return 1;
    case 1:
        f20 = func_0011EB68(arg0);
        f0 = func_0011EBC8(arg0);
        f0 = f0 + f0;
        f1 = fn * D_00384084;
        f20 = f20 + f0;
        return f1 <= f20;
    case 2:
        h = BtlCharApi_GetHeight(*(s32 *)arg0);
        f1 = fn * D_00384088;
        f2 = *(f32 *)(q + 0x70);
        f0 = h * f1;
        return f2 < f0;
    case 3:
        return (3 * n) < *(s32 *)(arg0 + 0x14C);
    case 4:
        if (func_00126058(arg0, 1, 1) != 0) {
            return 1;
        }
        return (*(u32 *)(q + 0x8C) & 0x40) != 0;
    case 5:
        return func_00126058(arg0, 2, 1) != 0;
    case 6:
        return func_00126058(arg0, 2, 0x200) == 0;
    case 7:
        return *(u8 *)(q + 0x148) == 0;
    case 8:
        return (*(u32 *)(q + 0x18) & 1) == 0;
    case 9:
        if (*(u8 *)(q + 0x148) != 0) {
            return 0;
        }
        /* falls through to the case 18 test */
    case 18:
        if (*(u8 *)(q + 0x124) != 0) {
            return 0;
        }
        return *(u8 *)(q + 0x125) == 0;
    case 10:
        return *(f32 *)(q + 0x134) < fn;
    case 11:
        f1 = *(f32 *)(q + 0x120);
        if (!(-1.0f < f1)) {
            return 0;
        }
        f0 = fn + D_0038408C;
        if (!(f1 <= f0)) {
            return 0;
        }
        return *(s32 *)(q + 0x90) != 26;
    case 12:
        f1 = *(f32 *)(q + 0x70);
        f0 = fn * 10.0f;
        return f1 < f0;
    case 13:
        g = BtlMember_GetActiveGauge(s3);
        return *(s32 *)(g + 0xC) >= 1000 * n;
    case 14:
        return *(f32 *)(q + 0x84) < fn;
    case 15:
        f0 = fn * D_00384090;
        f1 = *(f32 *)(s3 + 0xA30);
        return f0 <= f1;
    case 16:
        g = BtlMember_GetActiveGauge(s3);
        r = func_00241718(s3, 2);
        return *(s32 *)(g + 0xC) >= r;
    case 17:
        g = BtlMember_GetActiveGauge(s3);
        r = func_00241718(s3, 3);
        return *(s32 *)(g + 0xC) >= r;
    default:
        return 0;
    }
}
