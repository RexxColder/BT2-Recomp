#include "common.h"

s32 EftSmoke_GetPos(s32 arg0, s32 arg1, void *arg2);
void EftGeyser_Update(void);

s32 EftGeyser_GetSmokePos(u8 *arg0) {
    s32 temp_a1;
    s32 temp_v1;
    u8 *q;

    if (arg0 == NULL) {
        return 0;
    }
    temp_a1 = **(s32 **)(arg0 + 0x28);
    if (temp_a1 == (s32)0x00131760u && (arg0[0] & 1) == 0) { /* PS2 address of EftGeyser_Update */
        q = *(u8 **)(arg0 + 0x38);
        temp_v1 = *(s32 *)(q + 0xEC);
        if (temp_v1 != 0) {
            return EftSmoke_GetPos(temp_v1, temp_a1, arg0);
        }
    }
    return 0;
}
