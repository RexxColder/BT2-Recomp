#include "common.h"

s32 func_002E93C0();
void func_002E93D8(void);
void func_002EC388(s8 *arg0);
extern s8 D_00366A58[] __attribute__((section(".data")));

/* 0x002EC478: calls func_002E93C0(), then walks 15 entries of 0x48 bytes at D_00366A58 (down from 15 to 0,
 * the counter decrements once per entry): entries whose first byte is 1 go through func_002EC388(entry).
 * Ends with a tail call to func_002E93D8(). */
void func_002EC478(unsigned long r_a0, unsigned long r_a1, unsigned long r_a2, unsigned long r_a3, unsigned long r_t0, unsigned long r_t1, unsigned long r_t2, unsigned long r_t3) { /* asm: a0, a1, a2, a3, t0, t1, t2, t3 arrive and pass through untouched */
    s32 count;
    s8 *entry;

    count = 0xF;
    func_002E93C0(r_a0, r_a1, r_a2, r_a3, r_t0, r_t1, r_t2, r_t3);
    entry = D_00366A58;
    do {
        if (*entry == 1) {
            func_002EC388(entry);
        }
        count -= 1;
        entry += 0x48;
    } while (count >= 0);
    func_002E93D8();
}
