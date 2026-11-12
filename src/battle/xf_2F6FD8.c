#include "common.h"

void func_002F17A0(s32 a);

/* Forwards the word at +0x4 of the object to func_002F17A0. */
void func_002F6FD8(void *obj) {
    func_002F17A0(*(s32 *)((u8 *)obj + 0x4));
}
