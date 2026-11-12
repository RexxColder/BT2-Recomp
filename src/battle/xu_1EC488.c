#include "common.h"

void func_001EC818(s32 arg0, s32 arg1);
void func_001ECF40(s32 arg0, s32 arg1);

/* Flag 0x8 of the word at +0x68 selects the callee; both get the byte arg1 & 0xFF. */
void func_001EC488(s32 arg0, s32 arg1) {
    s32 temp = arg1 & 0xFF;

    if (*(s32 *)(arg0 + 0x68) & 8) {
        func_001EC818(arg0, temp);
        return;
    }
    func_001ECF40(arg0, temp);
}
