#include "common.h"

void EftCam_StopIfRunning(void);
void func_00147FB8(s32 arg0);
void func_0014EEF8(s32 arg0, s32 arg1);
s32 func_001F3758(s32 arg0);

void func_00149028(s32 arg0) {
    u8 *temp_s0;
    s32 *temp_s1;
    s32 v;

    temp_s0 = *(u8 **)((u8 *)arg0 + 0x38);
    temp_s1 = *(s32 **)(temp_s0 + 0x90);
    v = func_001F3758(arg0);
    func_0014EEF8(*(s32 *)((u8 *)v + 0x38), (s32)(temp_s0 + 0x94));
    func_00147FB8(*temp_s1);
    if (*(s32 *)temp_s0 & 0x80) {
        EftCam_StopIfRunning();
    }
}
