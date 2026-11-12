#include "m2c_macros.h"

extern void **D_003876A0;
extern void *D_00387930;

void func_00212DB0(void) {
    void *temp_v1;

    temp_v1 = *D_003876A0;
    M2C_FIELD(D_00387930, void **, 0x18) = (void *) (temp_v1 + (((u32) M2C_FIELD(temp_v1, u32 *, 0xC) >> 2) * 4));
}
