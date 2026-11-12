#include "common.h"

s32 func_00126598(s32 arg0);
s32 func_001267E8(s32 arg0, u8 arg1);
void func_00128EF0(void);
void func_00128F08(void);
void func_00128F90(s32 arg0);
void func_001B2930(u8 *arg0);
extern s32 gBtlCamView;

void func_001B31D8(u8 *arg0) {
    u8 *s0;

    s0 = *(u8 **)(arg0 + 0x38);
    if (func_001267E8(*(s32 *)(s0 + 0x00), *(u8 *)(s0 + 0xA44)) != 0) {
        return;
    }
    if (*(s32 *)(s0 + 0xA40) & 0x10) {
        if (func_00126598(*(s32 *)(s0 + 0x00)) == 0) {
            return;
        }
    }
    func_00128EF0();
    func_00128F90(gBtlCamView + 0x100);
    func_001B2930(arg0);
    func_00128F08();
}
