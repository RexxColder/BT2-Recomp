#include "common.h"

void func_00269708(void);
void func_0028BB60(s32 arg0);
extern u8 *D_00387A40;

void func_0025E5D8(void) {
    s32 q;

    func_00269708();
    q = *(s32 *)(D_00387A40 + 0x8);
    if (q != 0) {
        func_0028BB60(q);
    }
    q = *(s32 *)(D_00387A40 + 0x0);
    if (q != 0) {
        func_0028BB60(q);
    }
    func_0028BB60((s32)D_00387A40);
    D_00387A40 = NULL;
}
