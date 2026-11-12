#include "common.h"

void func_0026E9E8(s32 arg0);
void func_002510E0(void);
extern s32 D_003879C0;

void func_00252C18(void) {
    s32 s0 = 1;
    s32 s1 = 0;

    do {
        s0 -= 1;
        func_0026E9E8(D_003879C0 + s1 + 0xC);
        s1 += 0x28;
    } while (s0 >= 0);
    func_002510E0();
}
