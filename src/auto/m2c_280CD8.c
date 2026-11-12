#include "m2c_macros.h"

M2C_UNK GfxClut_InitPacket(s32, M2C_UNK);           /* extern */
M2C_UNK func_002793F0(s32, M2C_UNK);                /* extern */
M2C_UNK func_0027AA30(s32);                         /* extern */
M2C_UNK func_0027B890();                            /* extern */
M2C_UNK func_0027C2E0(s32, M2C_UNK);                /* extern */
M2C_UNK func_0027E6B0(s32, M2C_UNK);                /* extern */
M2C_UNK func_0027EBD0(s32, M2C_UNK);                /* extern */
M2C_UNK func_0027F628(s32, M2C_UNK);                /* extern */
M2C_UNK func_0027F968(M2C_UNK);                     /* extern */
M2C_UNK func_00280940(s32, M2C_UNK);                /* extern */
M2C_UNK func_00280BC0();                            /* extern */
M2C_UNK func_00281F50(s32);                         /* extern */
M2C_UNK func_002825E0();                            /* extern */
M2C_UNK func_00283880();                            /* extern */
M2C_UNK func_002847E8(s32, M2C_UNK);                /* extern */
M2C_UNK func_00284FC8();                            /* extern */
M2C_UNK func_00285D68(s32, M2C_UNK);                /* extern */
s32 func_0028BAA8(M2C_UNK);                         /* extern */
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */
extern s32 D_00387AFC;

void func_00280CD8(void) {
    s32 temp_v0;

    temp_v0 = func_0028BAA8(0x3D00);
    D_00387AFC = temp_v0;
    memset(temp_v0, 0, 0x3D00);
    func_00281F50(D_00387AFC + 0x2F00);
    func_0027AA30(D_00387AFC + 0x3090);
    func_00285D68(D_00387AFC, 0x3E80);
    func_0027C2E0(D_00387AFC + 0x4C0, 0x3E84);
    func_00280940(D_00387AFC + 0xA80, 0x3E60);
    func_00280940(D_00387AFC + 0x1040, 0x3E60);
    func_0027EBD0(D_00387AFC + 0x1600, 0x3E88);
    func_002847E8(D_00387AFC + 0x2040, 0x3E94);
    func_002825E0();
    func_00283880();
    func_00284FC8();
    func_0027F968(0x3E9C);
    func_0027E6B0(D_00387AFC + 0x1B40, 0x3E8C);
    func_0027F628(D_00387AFC + 0x2500, 0x3E90);
    func_002793F0(D_00387AFC + 0x3100, 0x3E98);
    GfxClut_InitPacket(D_00387AFC + 0x3800, 0x3E7C);
    func_0027B890();
    func_00280BC0();
}
