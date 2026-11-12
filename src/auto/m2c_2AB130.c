#include "m2c_macros.h"

M2C_UNK Res_RelocateOffsets(void **, void *, void *); /* extern */
extern void *D_003876A0;
extern void *D_00387E08;

void func_002AB130(void) {
    void *temp_v1;
    void *temp_v1_2;

    temp_v1 = M2C_FIELD(D_003876A0, void **, 0x28);
    temp_v1_2 = temp_v1 + (((u32) M2C_FIELD(temp_v1, u32 *, 0x48) >> 2) * 4);
    D_00387E08 = temp_v1_2;
    Res_RelocateOffsets(&D_00387E08, temp_v1_2, temp_v1_2);
}
