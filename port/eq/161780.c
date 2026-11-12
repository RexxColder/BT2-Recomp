#include "common.h"

s32 func_001EDB20(void *arg0, s32 arg1);
void func_001EDBD8(s32 arg0, s32 arg1);
void func_001EDC20(s32 arg0, s32 arg1);
void *func_001F3758(void *arg0);

void func_00161780(void *arg0) {
    u8 *obj;
    u8 *temp_s0;
    s32 temp_v0;

    obj = func_001F3758(arg0);
    temp_s0 = *(u8 **)((u8 *)arg0 + 0x38) + 0xA70;
    temp_v0 = func_001EDB20(temp_s0, *(s32 *)(*(u8 **)(obj + 0x38) + 0x1E80));
    *(s32 *)(temp_s0 + 0x30) = temp_v0;
    func_001EDBD8(temp_v0, 0);
    func_001EDC20(*(s32 *)(temp_s0 + 0x30), 0);
}
