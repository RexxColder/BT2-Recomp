#include "m2c_macros.h"

M2C_UNK func_00312638(void *, void *, void *);      /* extern */
M2C_UNK func_00312680(void *, f32, void *);         /* extern */

// Fade slot color calc: func_00312680(slot, slot->f50, slot+0x30) then func_00312638(slot, slot, slot+0x10).
void FadeSlot_CalcColor(void *arg0) {
    func_00312680(arg0, M2C_FIELD(arg0, f32 *, 0x50), (u8 *)arg0 + 0x30);
    func_00312638(arg0, arg0, (u8 *)arg0 + 0x10);
}
