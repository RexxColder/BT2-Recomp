#include "m2c_macros.h"

M2C_UNK func_00273A48();                            /* extern */
M2C_UNK func_00280BC0();                            /* extern */

void func_00272C90(unsigned long r_a0, unsigned long r_a1, unsigned long r_a2, unsigned long r_a3, unsigned long r_t0, unsigned long r_t1, unsigned long r_t2, unsigned long r_t3) { /* asm: a0, a1, a2, a3, t0, t1, t2, t3 arrive and pass through untouched */
    func_00273A48(r_a0, r_a1, r_a2, r_a3, r_t0, r_t1, r_t2, r_t3);
    func_00280BC0();
}
