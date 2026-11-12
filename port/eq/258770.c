#include "common.h"

void func_0028BB60(s32 arg0);
void func_0029BD28(void);
extern u8 *D_00387A00;

void func_00258770(void) {
    func_0029BD28();
    func_0028BB60(*(s32 *)(D_00387A00 + 4));
    func_0028BB60(*(s32 *)(D_00387A00 + 0));
    func_0028BB60((s32)D_00387A00);
}
