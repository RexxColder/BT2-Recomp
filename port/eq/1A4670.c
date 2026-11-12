#include "common.h"

s32 func_001267E8(s32 a0, u8 a1);
void func_00128EF0(void);
void func_00128F90(s32 a0);
void func_00128F08(void *a0);
void func_001A28C0(void *a0, void *a1);
void func_001A3A38(void *a0, void *a1);
extern s32 gBtlCamView;

void func_001A4670(void *arg0) {
    u8 *s0;
    u8 *s1;
    u8 *s2;

    s0 = *(u8 **)((u8 *)arg0 + 0x38);
    s1 = s0 + 0x10;
    s2 = *(u8 **)(s1 + 0x38);
    if (func_001267E8(*(s32 *)s1, *(u8 *)(s0 + 0x54)) != 0) {
        return;
    }
    func_00128EF0();
    func_00128F90(gBtlCamView + 0x100);
    switch (s2[1]) {
    case 0:
        func_001A28C0(s0, s1);
        break;
    case 1:
        func_001A3A38(s0, s1);
        break;
    }
    func_00128F08(s0);
}
