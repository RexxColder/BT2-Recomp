#include "m2c_macros.h"

extern M2C_UNK func_001EB270 __attribute__((section(".data")));

#ifdef __mips__
#define LOOP_IS_UPDATE(p) ((void *)(p) == (void *)&func_001EB270)
#else
#define LOOP_IS_UPDATE(p) ((u32)(unsigned long)(p) == 0x001EB270u)
#endif

void func_001EB880(void *arg0) {
    u16 temp_v0;
    void *temp_a0;

    if ((arg0 != NULL) && LOOP_IS_UPDATE(*M2C_FIELD(arg0, s32 **, 0x28))) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x38);
        if (temp_a0 != NULL) {
            temp_v0 = M2C_FIELD(temp_a0, u16 *, 0x60);
            if (temp_v0 & 1 & 0xFFFF) {
                M2C_FIELD(temp_a0, u16 *, 0x60) = (u16) (temp_v0 | 4);
            }
        }
    }
}
