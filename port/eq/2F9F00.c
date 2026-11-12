#include "common.h"

void func_002F9300(void *arg0);
extern u8 D_0037D3C0[] __attribute__((section(".data")));
extern u8 D_0037D3E0[] __attribute__((section(".data")));

void func_002F9F00(void *arg0) {
    void (*temp_v0)(s32);

    if (arg0 == NULL) {
        func_002F9300(D_0037D3C0);
        return;
    }
    temp_v0 = *(void (**)(s32))((u8 *)*(void **)arg0 + 0x28);
    if (temp_v0 == NULL) {
        func_002F9300(D_0037D3E0);
        return;
    }
    temp_v0(*(s32 *)((u8 *)arg0 + 0x4));
}
