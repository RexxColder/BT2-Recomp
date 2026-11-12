#include "common.h"

void func_002EA050(void *arg0, s32 arg1);
void func_002F2BD8(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037CB00[] __attribute__((section(".data")));

void func_002F5898(void *arg0, s16 arg1) {
    s32 temp_v0;

    if (arg0 == NULL) {
        func_002EA050(D_0037CB00, arg1);
        return;
    }
    temp_v0 = *(s32 *)((u8 *)arg0 + 0x8);
    *(s16 *)((u8 *)arg0 + 0x3E) = arg1;
    if (temp_v0 != 0) {
        func_002F2BD8(temp_v0, ((s32)arg1 << 16) >> 5, (s32)*(s16 *)((u8 *)arg0 + 0x3C) << 0xB);
    }
}
