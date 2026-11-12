#include "common.h"

extern u8 D_0039D938[] __attribute__((section(".data")));

void func_002F9F58(void) {
    u8 *p;
    void (**fp)(void);
    void (*f)(void);
    s32 i;

    p = D_0039D938;
    for (i = 31; i >= 0; i--) {
        fp = *(void (***)(void))p;
        p += 0x10;
        if (fp != NULL) {
            f = *fp;
            if (f != NULL) {
                f();
            }
        }
    }
}
