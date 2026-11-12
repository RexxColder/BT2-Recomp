#include "common.h"

void func_002DA708(void *a0, s32 a1, s32 a2);
void func_002DA3A8(void *a0, void *a1, s32 a2);
void func_002C2FC0(void *a0);
void func_002D0BA0(void *a0, s32 a1);
void func_002BF880(void *a0);
void func_002C2F08(void *a0);
void func_002D2898(void *a0, s32 a1);
void *memcpy(void *arg0, const void *arg1, u32 arg2);
extern u8 D_00346C28 __attribute__((section(".data")));
extern u8 D_0037A370 __attribute__((section(".data")));
extern u8 D_00346DE8 __attribute__((section(".data")));

void func_002C2E48(void *arg0) {
    u8 *s0;
    s32 k;

    s0 = &D_00346C28;
    func_002DA708(s0, 0, 0x89);
    func_002DA3A8(s0, &D_0037A370, 0x190);
    memcpy(s0 + 0x190, arg0, 8);
    *(s32 *)(s0 + 0x198) = 0;
    func_002C2FC0(s0 + 0x19C);
    func_002D0BA0(s0 + 0x1B0, *(s32 *)((u8 *)arg0 + 4));
    func_002BF880(s0 + 0x1BC);
    func_002C2F08(s0);
    s0 += 0x220;
    for (k = 0; k < 8; k++) {
        *(s32 *)s0 = 0;
        s0 -= 4;
    }
    func_002D2898(&D_00346DE8, *(s32 *)arg0);
}
