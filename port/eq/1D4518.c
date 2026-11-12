#include "common.h"

f32 func_00208670(s32 arg0);
void func_001D7E50(s32 arg0, f32 arg1, f32 arg2, f32 arg3);

/* 0x001D4518(obj): cnt = obj->+4 (unsigned). When cnt % 6 == 0: r = func_00208670(obj->+0), then
 * func_001D7E50(obj->+0, 45.0f, 80.0f, r) and func_001D7E50(obj->+0, -45.0f, 80.0f, r). Then obj->+4 = cnt + 1. */
void func_001D4518(u8 *arg0) {
    s32 cnt = *(s32 *)(arg0 + 4);
    s32 a;
    f32 r;

    if ((u32)cnt % 6U == 0) {
        a = *(s32 *)arg0;
        r = func_00208670(a);
        func_001D7E50(*(s32 *)arg0, 45.0f, 80.0f, r);
        func_001D7E50(*(s32 *)arg0, -45.0f, 80.0f, r);
    }
    *(s32 *)(arg0 + 4) = cnt + 1;
}
