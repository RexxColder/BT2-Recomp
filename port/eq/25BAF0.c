#include "m2c_macros.h"

s32 func_0025A310(void);
void func_0028BB60(s32 arg0);
extern s32 D_00388A00 __attribute__((section(".data")));

void func_0025BAF0(void) {
    func_0025A310();
    if (D_00388A00 != 0) {
        func_0028BB60(D_00388A00);
        D_00388A00 = 0;
    }
}
