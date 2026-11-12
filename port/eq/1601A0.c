#include "common.h"

s32 func_001EDB20(s32 arg0, s32 arg1);
s32 func_001EDBD8(s32 arg0, s32 arg1);
s32 func_001EDC20(s32 arg0, s32 arg1);
u8 *func_001F3758(s32 arg0);

s32 func_001601A0(u8 *arg0) {
    s32 temp_v0;
    u8 *temp_s0;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    temp_v0 = func_001EDB20((s32)(temp_s0 + 0xB00), *(s32 *)(*(u8 **)(func_001F3758((s32)arg0) + 0x38) + 0x1E80));
    *(s32 *)(temp_s0 + 8) = temp_v0;
    func_001EDBD8(temp_v0, 0);
    return func_001EDC20(*(s32 *)(temp_s0 + 8), 0);
}
