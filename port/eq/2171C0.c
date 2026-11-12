#include "common.h"

void func_002171C0(s32 arg0, f32 farg0, f32 farg1) {
    f32 cur;
    f32 n;
    f32 f1;
    f32 x;
    f32 cur2;
    f32 a2;

    cur = *(f32 *)(arg0 + 0xA44);
    n = -*(f32 *)(arg0 + 4) * farg1;
    f1 = *(f32 *)(arg0 + 0) * farg1;
    if (cur + farg0 < n) {
        x = cur + farg0;
    } else if (n < cur - farg0) {
        x = cur - farg0;
    } else {
        x = n;
    }
    *(f32 *)(arg0 + 0xA44) = x;

    cur2 = *(f32 *)(arg0 + 0xA48);
    if (cur2 + farg0 < f1) {
        *(f32 *)(arg0 + 0xA48) = cur2 + farg0;
        return;
    }
    a2 = cur2 - farg0;
    if (f1 < a2) {
        *(f32 *)(arg0 + 0xA48) = a2;
    } else {
        *(f32 *)(arg0 + 0xA48) = f1;
    }
}
