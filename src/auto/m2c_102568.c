#include "m2c_macros.h"

M2C_UNK StgRigid_Init();                            /* extern */
M2C_UNK func_00105698();                            /* extern */
M2C_UNK func_0011E868(M2C_UNK);                     /* extern */
M2C_UNK func_00126098(M2C_UNK);                     /* extern */
M2C_UNK func_001F6C38(M2C_UNK);                     /* extern */
M2C_UNK func_00242300();                            /* extern */
M2C_UNK func_0025A400();                            /* extern */
M2C_UNK func_0025BEB8();                            /* extern */
M2C_UNK func_0025E2D0(M2C_UNK);                     /* extern */
M2C_UNK func_00262330(M2C_UNK, M2C_UNK, M2C_UNK);   /* extern */
M2C_UNK func_00272070();                            /* extern */
M2C_UNK func_00278C80();                            /* extern */
M2C_UNK func_00280CD8();                            /* extern */
extern void *D_003876A0;

void func_00102568(void) {
    void *temp_v1;
    void *temp_v1_2;

    func_00272070();
    func_0025E2D0(0);
    func_00262330(0, 0, 0);
    func_00262330(0, 1, 1);
    func_001F6C38(2);
    func_0011E868(2);
    func_0025BEB8();
    func_0025A400();
    func_00280CD8();
    func_00278C80();
    func_00105698();
    StgRigid_Init();
    func_00242300();
    func_00126098(0);
    temp_v1 = M2C_FIELD(D_003876A0, void **, 0);
    M2C_FIELD(D_003876A0, void **, 0xB0) = (void *) (temp_v1 + (((u32) M2C_FIELD(temp_v1, u32 *, 8) >> 2) * 4));
    temp_v1_2 = M2C_FIELD(D_003876A0, void **, 0);
    M2C_FIELD(D_003876A0, void **, 0xB4) = (void *) (temp_v1_2 + (((u32) M2C_FIELD(temp_v1_2, u32 *, 0x10) >> 2) * 4));
    M2C_FIELD(D_003876A0, s32 *, 0x2C) = 0;
}
