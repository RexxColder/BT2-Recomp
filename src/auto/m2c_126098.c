#include "m2c_macros.h"

M2C_UNK BtlTaskList_AddFirst(s32, M2C_UNK *, M2C_UNK); /* extern */
s32 BtlTaskList_Create(M2C_UNK, M2C_UNK, M2C_UNK);  /* extern */
s32 func_00126560();                                /* extern */
M2C_UNK func_00126578(M2C_UNK);                     /* extern */
s32 func_00126580();                                /* extern */
M2C_UNK func_00126688(M2C_UNK);                     /* extern */
M2C_UNK func_00126D40();                            /* extern */
M2C_UNK func_00127018();                            /* extern */
M2C_UNK func_00128E90();                            /* extern */
M2C_UNK func_0012E888();                            /* extern */
M2C_UNK func_001E4C08();                            /* extern */
M2C_UNK func_001EBDC8(M2C_UNK);                     /* extern */
M2C_UNK func_001F3768();                            /* extern */
void *func_0028BAA8(M2C_UNK);                       /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern M2C_UNK D_0033FFE0 __attribute__((section(".data")));
extern void *D_003876A0;
extern void *gBtlScene;

void func_00126098(s32 arg0) {
    void *temp_v0;

    temp_v0 = func_0028BAA8(0x2C);
    gBtlScene = temp_v0;
    memset(temp_v0, 0, 0x2C);
    M2C_FIELD(gBtlScene, s32 *, 0x1C) = arg0;
    if (arg0 == 0) {
        M2C_FIELD(gBtlScene, s32 *, 0x1C) = 0x1E;
    }
    if (func_00126560() != 0) {
        M2C_FIELD(gBtlScene, s32 *, 0x1C) = 0xF;
        if (func_00126580() >= 5) {
            func_00126578(8);
        }
        if (func_00126580() < 3) {
            func_00126578(2);
        }
    } else {
        func_00126578(2);
    }
    if (M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 2) {
        func_00126688(0);
    } else {
        func_00126688(1);
    }
    func_001EBDC8(0);
    func_00128E90();
    func_001F3768();
    func_0012E888();
    func_00127018();
    func_00126D40();
    func_001E4C08();
    M2C_FIELD(gBtlScene, s32 *, 0) = BtlTaskList_Create(0, 1, 0);
    BtlTaskList_AddFirst(M2C_FIELD(gBtlScene, s32 *, 0), &D_0033FFE0, 0);
}
