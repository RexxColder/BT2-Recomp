#include "m2c_macros.h"

void *BtlTaskList_AddTail(s32, M2C_UNK *, s32);     /* extern */
extern M2C_UNK D_00343538 __attribute__((section(".data")));
extern void *D_003878F4;

void func_001E74D8(s32 arg0, s32 arg1) {
    void *temp_v1;
    void *temp_v1_2;

    switch (arg1) {                                 /* irregular */
    case 0:
        if (M2C_FIELD(D_003878F4, void **, 4) == NULL) {
            M2C_FIELD(D_003878F4, void **, 4) = BtlTaskList_AddTail(M2C_FIELD(D_003878F4, s32 *, 0), &D_00343538, arg0);
        }
        return;
    case 1:
        temp_v1 = M2C_FIELD(D_003878F4, void **, 4);
        if (temp_v1 != NULL) {
            temp_v1_2 = M2C_FIELD(temp_v1, void **, 0x38);
            if (M2C_FIELD(temp_v1, u8 *, 0) & 1 & 0xFF) {
                M2C_FIELD(temp_v1_2, s32 *, 0x38) = (s32) (M2C_FIELD(temp_v1_2, s32 *, 0x38) | 0x10);
                return;
            }
        }
        break;
    case 2:
        if (M2C_FIELD(D_003878F4, void **, 4) != NULL) {
            M2C_FIELD(D_003878F4, void **, 4) = NULL;
        }
        break;
    }
}
