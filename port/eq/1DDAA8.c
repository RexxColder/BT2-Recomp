#include "common.h"

s32 func_00126598(s32 arg0);
void func_00128EF0(void);
void func_00128F08(void);
void func_00128F90(s32 arg0);
void func_001DD4C8(s32 arg0);
extern s32 gBtlCamView;

void func_001DDAA8(u8 *arg0) {
    u8 *temp_a0;

    temp_a0 = *(u8 **)(arg0 + 0x38);
    if (*(s32 *)(temp_a0 + 0x40) & 0x10) {
        if (func_00126598(*(s32 *)temp_a0) == 0) {
            return;
        }
    }
    func_00128EF0();
    func_00128F90(gBtlCamView + 0x100);
    func_001DD4C8((s32)arg0);
    func_00128F08();
}
