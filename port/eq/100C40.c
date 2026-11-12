#include "common.h"

s32 func_0028BAA8(s32 arg0);
void func_002EA588(s32 arg0, u8 *arg1, s32 arg2, s32 arg3);
s32 func_002EAFA8(s32 arg0);
void func_002EF218(void);
extern u8 D_0036C360[] __attribute__((section(".data")));
extern s32 D_00387F10;
extern s32 D_00387F14;
extern s32 D_00387F20;

void func_00100C40(void) {
    s32 r = func_0028BAA8(0x6880);

    D_00387F20 = 0;
    D_00387F10 = r;
    func_002EA588(0, D_0036C360, 0, r);
    while (func_002EAFA8(D_00387F20) != 3) {
        func_002EF218();
    }
    D_00387F14 = func_0028BAA8(0xFD04);
}
