#include "m2c_macros.h"

s32 Gsc_FindAction(s32, s32, M2C_UNK);              /* extern */
void *Gsc_FindFile();                               /* extern */
s32 func_002A02C0(s32, s32);                        /* extern */
void *func_002A04E8();                              /* extern */
M2C_UNK func_002A0508(void *);                      /* extern */

s32 Gsc_StartAction(s32 arg0, s32 arg1) {
    s32 temp_v0_2;
    void *temp_s1;
    void *temp_v0;

    temp_s1 = Gsc_FindFile(arg0);
    temp_v0 = func_002A04E8();
    M2C_FIELD(temp_v0, s32 *, 0x10) = arg1;
    M2C_FIELD(temp_v0, s32 *, 0xC) = func_002A02C0(arg0, M2C_FIELD(temp_s1, s32 *, 0x10));
    M2C_FIELD(temp_s1, s32 *, 0x10) = (s32) (M2C_FIELD(temp_s1, s32 *, 0x10) + 1);
    M2C_FIELD(temp_v0, s32 *, 0x14) = (s32) M2C_FIELD(temp_s1, s32 *, 0x20);
    temp_v0_2 = Gsc_FindAction(M2C_FIELD(temp_s1, s32 *, 0x1C), arg1, 1);
    M2C_FIELD(temp_v0, s32 *, 0x1C) = 0;
    M2C_FIELD(temp_v0, s32 *, 0x18) = temp_v0_2;
    M2C_FIELD(temp_v0, s32 *, 0x20) = 0;
    M2C_FIELD(temp_v0, s32 *, 0x24) = 0;
    M2C_FIELD(temp_v0, s32 *, 0x28) = 0;
    func_002A0508(temp_v0);
    return M2C_FIELD(temp_v0, s32 *, 0xC);
}
