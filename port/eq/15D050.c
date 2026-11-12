#include "common.h"

u8 *func_001F3758(u8 *arg0);
void EftCam_StopIfRunning(void);
void func_0014EEF8(u8 *arg0, u8 *arg1);
void func_00147FB8(s32 arg0);

void func_0015D050(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x38);
    u8 *other = *(u8 **)(func_001F3758(arg0) + 0x38);
    u8 *cam = *(u8 **)(obj + 0xB0);

    EftCam_StopIfRunning();
    func_0014EEF8(other, obj + 0xB4);
    if (*(s32 *)(*(u8 **)(cam + 0x20) + 4) != 0) {
        func_00147FB8(*(s32 *)cam);
    }
}
