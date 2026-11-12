#include "common.h"

s32 func_001F3758(s32 arg0);
void func_0014EEF8(s32 arg0, s32 arg1);
void func_001617E0(s32 arg0);
void func_00147FB8(s32 arg0);
void EftCam_StopIfRunning(void);

void func_00161F80(s32 arg0) {
    u8 *temp_v1 = (u8 *)*(s32 *)((u8 *)arg0 + 0x38);
    s32 *temp_s1 = (s32 *)*(s32 *)(temp_v1 + 0x70);

    func_0014EEF8(*(s32 *)((u8 *)func_001F3758(arg0) + 0x38), (s32)(temp_v1 + 0x74));
    func_001617E0(arg0);
    func_00147FB8(*temp_s1);
    EftCam_StopIfRunning();
}
