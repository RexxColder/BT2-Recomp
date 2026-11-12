#include "common.h"

void func_002F9300(void *arg0);
extern u8 D_0037D808[] __attribute__((section(".data")));
extern u8 D_0037D830[] __attribute__((section(".data")));

s32 func_002FA8D0(void *arg0) {
    s32 (*temp_v0)(s32);

    if (arg0 == NULL) {
        func_002F9300(D_0037D808);
        return 0;
    }
    temp_v0 = *(s32 (**)(s32))((u8 *)*(void **)arg0 + 0x4C);
    if (temp_v0 == NULL) {
        func_002F9300(D_0037D830);
        return 0;
    }
    return temp_v0(*(s32 *)((u8 *)arg0 + 0x4));
}
