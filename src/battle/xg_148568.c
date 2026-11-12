/* Battle task list: adds the task in slot (arg0, arg1) to a list chosen by its type. */
#include "m2c_macros.h"

s32 BtlTaskList_AddTail(s32, s32, void *, void *);  /* extern */
extern u8 D_00340260[] __attribute__((section(".data")));
extern void *D_00387760;

void func_00148568(s32 arg0, s32 arg1) {
    s32 temp_v1;
    void *temp_a3;
    void *temp_s0;

    temp_a3 = M2C_FIELD(D_00387760, s32 *, 4) + (arg0 * 0x270);
    temp_s0 = temp_a3 + (arg1 * 0x50);
    if (M2C_FIELD(temp_s0, s32 *, 0x1C) != 0) {
        temp_v1 = *(s32 *)(D_00340260 + (*M2C_FIELD(temp_s0, s32 **, 0x20) * 0xC));
        if (temp_v1 != 0) {
            M2C_FIELD(temp_s0, s32 *, 0x28) = BtlTaskList_AddTail(M2C_FIELD(temp_a3, s32 *, 0x258), temp_v1, temp_s0, temp_a3);
        }
    }
}
