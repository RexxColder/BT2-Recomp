#include "common.h"

void func_002DA7D8(void);
void func_002DC678(void);
void func_002DCE00(s32 arg0);
extern s32 D_00347600 __attribute__((section(".data")));

void func_002DC9C8(void) {
    s32 count = *(s32 *)(D_00347600 + 0xC);
    s32 s0;
    s32 s1;

    if (count > 0) {
        s0 = D_00347600 + 0x10;
        s1 = count;
        do {
            if (*(s32 *)s0 != 1) {
                func_002DCE00(s0);
            }
            s1 -= 1;
            s0 += 0x100;
        } while (s1 != 0);
    }
    func_002DA7D8();
    func_002DC678();
}
