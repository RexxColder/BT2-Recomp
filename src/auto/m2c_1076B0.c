#include "m2c_macros.h"

M2C_UNK Res_RelocateOffsets(void **, void *, void *); /* extern */
M2C_UNK func_001076A0();                            /* extern */
void **func_0028BAA8(M2C_UNK);                      /* extern */
M2C_UNK memset(void **, M2C_UNK, M2C_UNK);          /* extern */
extern void *D_003876A0;
extern void **gObjOutline;

void func_001076B0(void) {
    void **temp_v0;
    void *temp_a1;
    void *temp_v1;

    temp_v0 = func_0028BAA8(0x20);
    gObjOutline = temp_v0;
    memset(temp_v0, 0, 0x20);
    func_001076A0();
    temp_v1 = M2C_FIELD(D_003876A0, void **, 0x24);
    *gObjOutline = temp_v1 + (((u32) M2C_FIELD(temp_v1, u32 *, 0x18) >> 2) * 4);
    temp_a1 = *gObjOutline;
    Res_RelocateOffsets(gObjOutline, temp_a1, temp_a1);
}
