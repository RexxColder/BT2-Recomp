#include "m2c_macros.h"

M2C_UNK Rand_Range(M2C_UNK *);                      /* extern */
M2C_UNK func_002B2A18(s32);                         /* extern */
M2C_UNK func_002B3DE0(s32);                         /* extern */
M2C_UNK func_002B4CB0(void *);                      /* extern */
s32 func_002B4D30(void *);                          /* extern */
M2C_UNK func_002B7138(void *);                      /* extern */
M2C_UNK func_002B93F0(s32);                         /* extern */
M2C_UNK func_002BA048(void *);                      /* extern */
M2C_UNK func_002BC0A8(void *);                      /* extern */
M2C_UNK func_002BD380(M2C_UNK);                     /* extern */
M2C_UNK func_002BD648(s32);                         /* extern */
M2C_UNK func_002FFB40(s32);                         /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern M2C_UNK D_003782B0 __attribute__((section(".data")));

void func_002B45F0(void *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_6;
    s32 temp_a0_7;
    void **temp_a0_4;
    void **temp_a0_5;

    if (arg0 != NULL) {
        func_002BD380(1);
        func_002B7138(arg0);
        M2C_FIELD(arg0, s32 *, 0) = 0;
        func_002BD380(0);
        func_002BA048(arg0);
        temp_a0 = M2C_FIELD(arg0, s32 *, 0xA8);
        if (temp_a0 != 0) {
            func_002B93F0(temp_a0);
        }
        temp_a0_2 = M2C_FIELD(arg0, s32 *, 0x48);
        if (temp_a0_2 != 0) {
            func_002FFB40(temp_a0_2);
        }
        temp_a0_3 = M2C_FIELD(arg0, s32 *, 0x40);
        if (temp_a0_3 != 0) {
            func_002BD648(temp_a0_3);
        }
        temp_a0_4 = M2C_FIELD(arg0, void ***, 0x1C0);
        if (temp_a0_4 != NULL) {
            M2C_FIELD(*temp_a0_4, M2C_UNK (**)(void *), 0xC)(temp_a0_4);
        }
        temp_a0_5 = M2C_FIELD(arg0, void ***, 0x1E0);
        if (temp_a0_5 != NULL) {
            M2C_FIELD(*temp_a0_5, M2C_UNK (**)(void *), 0xC)(temp_a0_5);
        }
        temp_a0_6 = M2C_FIELD(arg0, s32 *, 0x2D0);
        if (temp_a0_6 != 0) {
            func_002B2A18(temp_a0_6);
        }
        temp_a0_7 = M2C_FIELD(arg0, s32 *, 0x3C);
        if (temp_a0_7 != 0) {
            func_002B3DE0(temp_a0_7);
        }
        func_002BC0A8(arg0 + 0x284);
        func_002BC0A8(arg0 + 0x2A4);
        func_002B4CB0(arg0);
        if (func_002B4D30(arg0) != 0) {
            Rand_Range(&D_003782B0);
        }
        memset(arg0, 0, 0x304);
        M2C_FIELD(arg0, s32 *, 0) = 0;
    }
}
