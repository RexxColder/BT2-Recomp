#include "common.h"

extern s32 D_00346E58 __attribute__((section(".data")));
extern s32 D_0037A340[] __attribute__((section(".data")));

typedef s32 (*VtFn18)(void *arg0, s32 arg1, s32 arg2, s32 *arg3);
typedef s32 (*VtFn1C)(void *arg0, s32 arg1, s32 *arg2);

s32 func_002DCE50(void *arg0);
void *func_002DCFE8(s32 arg0, s32 arg1, s32 arg2);

void func_002C9890(void **arg0, s32 *arg1, void **arg2, s32 *arg3) {
    s32 sp[4];
    u8 *s0, *s1, *v;
    s32 s2, idx;
    s32 bump = 0;

    *arg1 = 0;
    *arg2 = NULL;
    *arg3 = 0;
    (*(VtFn18 *)((u8 *)*arg0 + 0x18))(arg0, 1, 0x7FFFFFFF, sp);
    s0 = (u8 *)func_002DCFE8(sp[0], sp[1], 0xCC);
    if (s0 == NULL) {
        bump = 1;
    } else if (func_002DCE50(s0) & 4) {
        if (sp[1] < ((s32)s0 - sp[0]) + 6) {
            bump = 1;
        } else {
            idx = (s0[5] >> 3) & 7;
            *arg1 = D_0037A340[idx];
            if (*arg1 == 3) {
                s2 = (sp[0] - (s32)s0) + sp[1];
                s1 = (u8 *)func_002DCFE8((s32)s0, s2, 0x22);
                if (s1 != NULL && (func_002DCE50(s1) & 0x20)) {
                    v = (u8 *)func_002DCFE8((s32)s0, s2, 2);
                    if (v == NULL) {
                        bump = 1;
                    } else {
                        *arg2 = s1;
                        *arg3 = (s32)v - (s32)s1;
                    }
                }
            }
        }
    }
    if (bump) {
        D_00346E58 += 1;
    }
    (*(VtFn1C *)((u8 *)*arg0 + 0x1C))(arg0, 1, sp);
}
