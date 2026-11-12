#include "m2c_macros.h"

s8 EftWater_GetSurfaceY(void *);                    /* extern */
M2C_UNK GfxLens_Clear();                            /* extern */
s32 func_002768D8(M2C_UNK);                         /* extern */
M2C_UNK func_0027A9E8(void *);                      /* extern */
M2C_UNK func_0027B9B8();                            /* extern */
M2C_UNK func_0027C2D8(void *);                      /* extern */
M2C_UNK func_0027C3B0(void *, s32);                 /* extern */
M2C_UNK func_0027EBA8(void *);                      /* extern */
M2C_UNK func_0027ED20(void *, s32);                 /* extern */
M2C_UNK func_00280938(void *);                      /* extern */
M2C_UNK func_002809F8(void *, s32, M2C_UNK);        /* extern */
M2C_UNK func_00281F00(void *);                      /* extern */
M2C_UNK func_002824C8();                            /* extern */
extern void *D_00387AFC;

void func_00280BC0(void) {
    void *temp_s0;

    func_00281F00(D_00387AFC + 0x2F00);
    func_0027A9E8(D_00387AFC + 0x3090);
    func_0027C2D8(D_00387AFC + 0x4C0);
    func_0027EBA8(D_00387AFC + 0x1600);
    func_00280938(D_00387AFC + 0xA80);
    func_00280938(D_00387AFC + 0x1040);
    func_0027B9B8();
    func_002824C8();
    GfxLens_Clear();
    M2C_FIELD(D_00387AFC, s8 *, 0x3CC8) = 1;
    M2C_FIELD(D_00387AFC, s8 *, 0x3CC8) = 1;
    M2C_FIELD(D_00387AFC, s8 *, 0x3CCA) = 0;
    M2C_FIELD(D_00387AFC, s8 *, 0x3CC1) = EftWater_GetSurfaceY(D_00387AFC + 0x3CC4);
    func_002809F8(D_00387AFC + 0xA80, func_002768D8(0), 1);
    func_002809F8(D_00387AFC + 0x1040, func_002768D8(1), 0);
    func_0027ED20(D_00387AFC + 0x1600, func_002768D8(2));
    temp_s0 = D_00387AFC;
    func_0027C3B0(temp_s0 + 0x4C0, func_002768D8(3));
}
