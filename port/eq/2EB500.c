#include "common.h"

u8 *func_002EB4A8(void);
s32 func_002F1B30(s32 arg0, s32 arg1);
void func_002EA050(u8 *arg0);
extern u8 D_0037BD20[] __attribute__((section(".data")));
extern u8 D_0037BD58[] __attribute__((section(".data")));

u8 *func_002EB500(void) {
    u8 *p;
    s32 r;

    p = func_002EB4A8();
    if (p == NULL) {
        func_002EA050(D_0037BD20);
        return NULL;
    }
    r = func_002F1B30(0, 0x100);
    *(s32 *)(p + 0x4) = r;
    if (r == 0) {
        func_002EA050(D_0037BD58);
        return NULL;
    }
    *(s8 *)(p + 0x0) = 1;
    *(s8 *)(p + 0x1) = 1;
    *(s32 *)(p + 0x1C) = 0;
    *(s32 *)(p + 0x20) = 0;
    *(s32 *)(p + 0x24) = 0;
    *(s8 *)(p + 0x2) = 0;
    *(s32 *)(p + 0x8) = 0;
    *(s8 *)(p + 0x3) = 0;
    *(s32 *)(p + 0x30) = 0x200;
    return p;
}
