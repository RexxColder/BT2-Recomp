#include "m2c_macros.h"

void func_002113C0(void *, s32, s32, s32); /* extern */
void func_0025FBA8(s32);                         /* extern */

void func_001F9C90(void *arg0) {
    void *temp_t0;
    void *temp_v1;
    s32 temp_v0;

    func_0025FBA8(M2C_FIELD(arg0, s32 *, 0x152C));
    temp_v0 = M2C_FIELD(arg0, s32 *, 0x8EC);
    temp_t0 = M2C_FIELD(arg0, void **, 0x1530);
    M2C_FIELD(arg0, s32 *, 0x8E0) = temp_v0;
    M2C_FIELD(temp_t0, s32 *, 0xAF0) = (s32) (M2C_FIELD(temp_t0, s32 *, 0xAF0) & ~0x20);
    temp_v1 = M2C_FIELD(arg0, void **, 0x1530);
    M2C_FIELD(temp_v1, s32 *, 0xAF0) = (s32) (M2C_FIELD(temp_v1, s32 *, 0xAF0) & ~0x40);
    func_002113C0(arg0, 2, 0x71, 0);
    func_002113C0(arg0, 2, 2, 1);
}
