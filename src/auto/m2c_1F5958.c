#include "m2c_macros.h"

M2C_UNK func_001F91F8(void *);                      /* extern */
f32 func_001FB810();                                /* extern */
M2C_UNK func_002113C0(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */

void func_001F5958(void *arg0) {
    void *temp_t0;
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;

    M2C_FIELD(arg0, f32 *, 0x15C) = func_001FB810(arg0);
    M2C_FIELD(arg0, s32 *, 0x8EC) = -1;
    memset(arg0 + 0x910, 0, 0x40);
    memset(arg0 + 0xA30, 0, 0x20);
    memset(arg0 + 0xAC4, 0, 0x34);
    func_001F91F8(arg0);
    M2C_FIELD(arg0, s32 *, 0xB8C) = 0;
    M2C_FIELD(arg0, s32 *, 0xB90) = 0;
    M2C_FIELD(arg0, s32 *, 0xB78) = 0;
    M2C_FIELD(arg0, s32 *, 0xB7C) = 0;
    memset(arg0 + 0x1514, 0, 0x18);
    temp_t0 = M2C_FIELD(arg0, s32 *, 0x1530) + 0x1C;
    temp_v1 = M2C_FIELD(temp_t0, void **, 0x92C);
    if (temp_v1 != NULL) {
        M2C_FIELD(arg0, void **, 0x1540) = (void *) (temp_v1 + (((u32) M2C_FIELD(temp_v1, u32 *, 0xC) >> 2) * 4));
    }
    temp_v1_2 = M2C_FIELD(temp_t0, void **, 0x930);
    if (temp_v1_2 != NULL) {
        M2C_FIELD(arg0, void **, 0x1544) = (void *) (temp_v1_2 + (((u32) M2C_FIELD(temp_v1_2, u32 *, 0xC) >> 2) * 4));
    }
    temp_v1_3 = M2C_FIELD(temp_t0, void **, 0x934);
    if (temp_v1_3 != NULL) {
        M2C_FIELD(arg0, void **, 0x1548) = (void *) (temp_v1_3 + (((u32) M2C_FIELD(temp_v1_3, u32 *, 0xC) >> 2) * 4));
    }
    func_002113C0(arg0, 0, 0x4000, 0);
    func_002113C0(arg0, 0, 0x1000, 0);
    func_002113C0(arg0, 0, 0x10000, 0);
    func_002113C0(arg0, 8, 1, 0);
}
