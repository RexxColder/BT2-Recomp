#include "m2c_macros.h"

M2C_UNK EftBubble_UpdateBurst(void *);              /* extern */
M2C_UNK EftBubble_UpdateTrail(void *);              /* extern */
extern void *D_003876A0;
extern void **gEftBubble;

void EftBubble_UpdateChrs(void) {
    s32 var_s1;
    void *var_s0;

    if (!(M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 0x100)) {
        var_s1 = 1;
        var_s0 = *gEftBubble;
        do {
            if (M2C_FIELD(var_s0, u8 *, 0xC) & 1 & 0xFF) {
                EftBubble_UpdateTrail(var_s0);
            }
            if (M2C_FIELD(var_s0, u8 *, 0xC) & 2) {
                EftBubble_UpdateBurst(var_s0);
            }
            var_s1 -= 1;
            var_s0 += 0x10;
        } while (var_s1 >= 0);
    }
}
