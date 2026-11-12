#include "common.h"

s32 Rand_Range(void *arg0);
s32 func_002B4B08(void *arg0, s32 arg1);
void func_002B4CB0(void *arg0);
s32 func_002B93D0(s32 arg0, s32 arg1);
s32 func_002B9FC0(void *arg0);
extern s32 D_00378260 __attribute__((section(".data")));
extern s32 D_00378288 __attribute__((section(".data")));

s32 func_002B4510(u8 *arg0) {
    u8 *s1;
    void *a0;
    s32 t;
    s32 t2;
    s32 t3;

    s1 = arg0 + 8;
    t = func_002B93D0(*(s32 *)(s1 + 8), *(s32 *)(s1 + 0xC));
    t2 = func_002B4B08(arg0, t);
    a0 = (void *)&D_00378260;
    if (t2 != 0) {
        *(s32 *)(arg0 + 0xAC) = t2;
        *(s32 *)(arg0 + 0xB0) = t;
        if (func_002B9FC0(s1) == 1) {
            t3 = func_002B4B08(arg0, 0x20000);
            a0 = (void *)&D_00378288;
            if (t3 != 0) {
                *(s32 *)(arg0 + 0x180) = t3;
                *(s32 *)(arg0 + 0x184) = 0x20000;
                return 0;
            }
        } else {
            *(s32 *)(arg0 + 0x184) = 0;
            *(s32 *)(arg0 + 0x180) = 0;
            return 0;
        }
    }
    Rand_Range(a0);
    func_002B4CB0(arg0);
    return -1;
}
