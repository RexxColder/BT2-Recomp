#include "common.h"

void func_002E7AB8(s32 a);
void func_002E7AC0(s32 a);

/* Forwards the word at +0x4 of the object to func_002E7AB8. */
void func_002F14B0(void *obj) {
    func_002E7AB8(*(s32 *)((u8 *)obj + 0x4));
}

/* Forwards the word at +0x4 of the object to func_002E7AC0. */
void func_002F14C8(void *obj) {
    func_002E7AC0(*(s32 *)((u8 *)obj + 0x4));
}
