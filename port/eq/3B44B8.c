#include "m2c_macros.h"

void func_2B45D8(s32);
void func_2B65C0(void);
void func_003B4B20(void *);
void func_28BB60(void *);
extern void *D_00421384 __attribute__((section(".data")));
extern void *D_0038B950 __attribute__((section(".data")));

void func_003B44B8(void) {
    func_2B45D8(M2C_FIELD(D_00421384, s32 *, 0xE0));
    func_2B65C0();
    func_003B4B20((u8 *)D_00421384 + 0x20);
    if (D_0038B950 != 0) {
        func_28BB60(D_0038B950);
        D_0038B950 = 0;
    }
    if (D_00421384 != 0) {
        func_28BB60(D_00421384);
        D_00421384 = 0;
    }
}
