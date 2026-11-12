#include "m2c_macros.h"

void *BtlObjVis_GetView_207EA0();                     /* extern */
void *func_00269A40(void *, s32);                    /* extern */
void func_003126C8(void *, void *);          /* extern */
extern M2C_UNK D_002C3630 __attribute__((section(".data")));

void func_00208DE8(s32 unused0, void *arg1, s32 arg2) {
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = BtlObjVis_GetView_207EA0(unused0);
    if (temp_v0 == 0) {
        func_003126C8(arg1, &D_002C3630);
        return;
    }
    temp_v0_2 = func_00269A40(temp_v0, arg2);
    if (temp_v0_2 == 0) {
        func_003126C8(arg1, (char *)temp_v0 + 0x9A0);
        return;
    }
    func_003126C8(arg1, (char *)temp_v0_2 + 0x30);
}
