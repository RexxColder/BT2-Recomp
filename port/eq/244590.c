#include "common.h"

void func_0024C030(s32 arg0);
void func_00250D90(u8 *arg0);
void func_0026E908(u8 *arg0);
void func_0028BB60(u8 *arg0);
extern u8 *D_00387958;

void func_00244590(s32 arg0) {
    s32 s0 = 3;
    s32 s1 = 0;

    func_0024C030(arg0);
    do {
        s0 -= 1;
        func_0026E908(D_00387958 + s1);
        s1 += 0x28;
    } while (s0 >= 0);
    func_00250D90(D_00387958);
    func_0028BB60(*(u8 **)(D_00387958 + 0xA4));
    func_0028BB60(*(u8 **)(D_00387958 + 0xA0));
    func_0028BB60(D_00387958);
}
