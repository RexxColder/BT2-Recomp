#include "m2c_macros.h"

void func_00129C28(void *, void *);                /* extern */
void func_00129DE0(f32, void *, void *, void *);     /* extern */
void func_00209D78(s16, void *);                  /* extern */
extern f32 D_00384EE0 __attribute__((section(".sdata")));

/* Recomputes the ribbon/trail node at arg1 from arg0 and toggles its side flag (bit 0x52) on mode bits 0x40/0x80. */
void func_001AA848(void *arg0, void *arg1) {
    s32 sp[4];
    s32 temp_v0;

    func_00129DE0(D_00384EE0, arg1 + 0x90, arg0 + 0x10, arg1 + 0xA0);
    temp_v0 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_v0 & 0x40) {
        func_00209D78((s16) (M2C_FIELD(arg1, u16 *, 0x52) ^ 1), sp);
        func_00129C28(arg1 + 0xB0, sp);
        M2C_FIELD(arg1, u16 *, 0x52) = (u16) (M2C_FIELD(arg1, u16 *, 0x52) ^ 1);
        M2C_FIELD(arg1, s32 *, 0) = (s32) ((M2C_FIELD(arg1, s32 *, 0) & ~4) | 8);
    } else if (temp_v0 & 0x80) {
        func_00209D78((s16) (M2C_FIELD(arg1, u16 *, 0x52) ^ 1), sp);
        func_00129C28(arg1 + 0xB0, sp);
        M2C_FIELD(arg1, u16 *, 0x52) = (u16) (M2C_FIELD(arg1, u16 *, 0x52) ^ 1);
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) M2C_FIELD(arg1, s16 *, 0x5C);
    }
}
