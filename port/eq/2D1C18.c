#include "common.h"

void func_002C2FF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_0037A530[] __attribute__((section(".data")));
extern s32 D_0037A558[] __attribute__((section(".data")));

void func_002D1C18(u8 *arg0, s32 *arg1, s32 *arg2) {
    s32 fn;
    s32 temp_v0;
    s32 temp_a3;

    temp_v0 = *(s32 *)arg0;
    temp_a3 = *(s32 *)(arg0 + 4);
    fn = D_0037A558[temp_v0 * 2 + temp_a3];
    if (fn == 0) {
        func_002C2FF0(0, 0xFF000221, (s32)arg1, (s32)arg2);
        *arg1 = 0;
        *arg2 = 1;
        return;
    }
    ((void (*)(s32, s32, s32, s32))fn)(D_0037A530[temp_v0], (s32)arg0, (s32)arg1, (s32)arg2);
}
