#include "common.h"

void func_002EDE40(void);
void func_0032EAA0(void);
extern s64 D_0034BC18 __attribute__((section(".data")));
extern s64 D_0034BC20 __attribute__((section(".data")));

void func_002EDE58(void) {
    while (D_0034BC18 == 0) {
        func_002EDE40();
    }
    D_0034BC20 = 1;
    func_0032EAA0();
}
