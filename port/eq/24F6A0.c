#include "common.h"

void func_0026E9E8(s32 arg0);
void func_002510E0(void);
void func_002486E8(s32 arg0);
extern u8 *D_003876A4;
extern s32 D_003879A0;

void func_0024F6A0(void) {
    s32 s0;
    s32 s1;
    s32 v0;

    s0 = 0;
    s1 = 0;
    do {
        v0 = *(s32 *)(D_003876A4 + 0x1C);
        if ((v0 == 0x37) || (v0 == 0x29)) {
            if (s0 != 2) {
                func_0026E9E8(D_003879A0 + s1 + 0x24);
            }
        } else {
            func_0026E9E8(D_003879A0 + s1 + 0x24);
        }
        s0 += 1;
        s1 += 0x28;
    } while (s0 < 4);
    func_002510E0();
    if (*(s32 *)(D_003876A4 + 0x1C) != 0x37) {
        func_002486E8(0x37);
    }
}
