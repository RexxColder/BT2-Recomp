#include "common.h"

void func_00249548();
void func_0026E908(s32 arg0);
void func_0028BB60(s32 arg0);
extern u8 *D_003879F8;

void func_002578E0(unsigned long r_a0, unsigned long r_a1, unsigned long r_a2, unsigned long r_a3, unsigned long r_t0, unsigned long r_t1, unsigned long r_t2, unsigned long r_t3) { /* asm: a0, a1, a2, a3, t0, t1, t2, t3 arrive and pass through untouched */
    func_00249548(r_a0, r_a1, r_a2, r_a3, r_t0, r_t1, r_t2, r_t3);
    func_0026E908((s32)(D_003879F8 + 0x18));
    func_0028BB60(*(s32 *)(D_003879F8 + 0x8));
    func_0028BB60(*(s32 *)(D_003879F8 + 0x4));
    func_0028BB60(*(s32 *)(D_003879F8 + 0x0));
    func_0028BB60((s32)D_003879F8);
}
