#include "common.h"

void *memcpy(void *arg0, void *arg1, u32 arg2);
s32 strlen(void *arg0);
void func_002F9300(void *arg0, s32 arg1, s32 arg2);
void func_002F9660(void *arg0);
s32 func_002F9860(void *arg0, s32 arg1);
extern s32 D_0037D198 __attribute__((section(".data")));
extern s32 D_0037D1C0 __attribute__((section(".data")));
extern s8 D_0039DB38 __attribute__((section(".data")));

void func_002F9798(u8 *arg0, s32 arg1, s32 arg2) {
    s32 len;
    s32 temp_a2;

    if (arg0 == NULL) {
        func_002F9300((void *)&D_0037D198, arg1, arg2);
        return;
    }
    len = strlen(arg0);
    if (len == 0) {
        D_0039DB38 = 0;
        return;
    }
    func_002F9660(arg0);
    temp_a2 = len + 1;
    if (func_002F9860(arg0, len) == 1) {
        memcpy((void *)&D_0039DB38, arg0, temp_a2);
        return;
    }
    func_002F9300((void *)&D_0037D1C0, (s32)arg0, temp_a2);
}
