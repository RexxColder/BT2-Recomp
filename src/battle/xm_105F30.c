#include "m2c_macros.h"

void *memset(void *, int, unsigned int);
extern u16 D_0033F408[] __attribute__((section(".data")));
extern void *D_003876A0;

// Clears the 16-byte block at arg0, then stores the u16 entry of table D_0033F408 selected by the word at D_003876A0+0xC0 into arg0+0xC.
void func_00105F30(void *arg0) {
    memset(arg0, 0, 16);
    M2C_FIELD(arg0, u16 *, 0xC) = D_0033F408[M2C_FIELD(D_003876A0, s32 *, 0xC0)];
}
