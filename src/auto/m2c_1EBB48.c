#include "m2c_macros.h"

M2C_UNK func_001EAF20(s32);                         /* extern */
extern M2C_UNK func_001EB270 __attribute__((section(".data")));

#ifdef __mips__
#define LOOP_IS_UPDATE(p) ((void *)(p) == (void *)&func_001EB270)
#else
#define LOOP_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001EB270u)
#endif

void func_001EBB48(void *arg0) {
    void *temp_a0;
    void *var_s0;

    if (arg0 != NULL) {
        if (LOOP_IS_UPDATE(*M2C_FIELD(arg0, s32 **, 0x28))) {
            temp_a0 = M2C_FIELD(arg0, void **, 0x38);
            if ((temp_a0 != NULL) && (M2C_FIELD(temp_a0, u16 *, 0x60) & 1 & 0xFFFF)) {
                var_s0 = M2C_FIELD(temp_a0, void **, 0x64);
                if (var_s0 != NULL) {
                    do {
                        func_001EAF20(M2C_FIELD(var_s0, s32 *, 0));
                        var_s0 = M2C_FIELD(var_s0, void **, 8);
                    } while (var_s0 != NULL);
                }
            }
        }
    }
}
