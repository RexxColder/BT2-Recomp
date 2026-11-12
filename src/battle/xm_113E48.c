#include "m2c_macros.h"

void func_00113E20(void *, s32, s32);

// Walks a chain of 0x60-byte records from arg0 while the record's word at +0 has bit 2 clear, calling func_00113E20 on each (arg1 masked to a byte, arg2 passed through).
void func_00113E48(void *arg0, s32 arg1, s32 arg2) {
    u8 *var_s0;
    u8 *var_s1;
    s32 var_s2;
    s32 var_s3;

    var_s2 = arg1 & 0xFF;
    var_s3 = arg2;
    if (!(*(s32 *) arg0 & 2)) {
        var_s0 = arg0;
        var_s1 = var_s0;
        do {
            func_00113E20(var_s1, var_s2, var_s3);
            var_s1 += 0x60;
            var_s0 += 0x60;
        } while (!(*(s32 *) var_s0 & 2));
    }
}
