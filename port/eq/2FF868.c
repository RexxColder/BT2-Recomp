#include "common.h"

s8 *strcpy(s8 *dst, s8 *src);
extern u8 D_00356EB0[] __attribute__((section(".data")));
extern u8 D_0037E670[] __attribute__((section(".data")));

void func_002FF868(s8 *arg0) {
    s8 *dst;
    s8 temp_a0;

    dst = (s8 *) D_00356EB0;
    if (arg0 == NULL) {
        dst[0] = 0;
        return;
    }
    temp_a0 = arg0[0];
    if ((temp_a0 != 0x2F) && (temp_a0 != 0x5C)) {
        dst[0] = (s8) D_0037E670[0];
        dst[1] = (s8) D_0037E670[1];
    } else {
        dst[0] = 0;
    }
    strcpy(dst, arg0);
}
