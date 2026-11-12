#include "common.h"

void func_002E15E8(void);
void func_002E1630(s32 arg0, s32 arg1, s32 arg2);
void func_002E1B70(s32 arg0);
void func_002E2098(void);
extern u8 D_0037B088[] __attribute__((section(".data")));
extern u8 D_0037B124 __attribute__((section(".data")));
extern u8 *D_0039D648 __attribute__((section(".data")));

void func_002E1558(s32 arg0, s32 arg1, s32 arg2) {
    while (D_0037B124 != 4) {
        /* original: jalr $at with $at = -1 (no valid target), then loops back */
        ((void (*)(void))(s32)-1)();
    }
    D_0039D648 = D_0037B088;
    func_002E1B70(4);
    func_002E2098();
    func_002E1630(arg0, arg1, arg2);
    func_002E15E8();
}
