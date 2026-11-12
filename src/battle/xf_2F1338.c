#include "common.h"

void func_002E7FA0(s32 a);

/* Forwards the word at +0x4 of the object to func_002E7FA0. */
void func_002F1338(void *obj) {
    func_002E7FA0(*(s32 *)((u8 *)obj + 0x4));
}
