#include "common.h"

void func_00302768(s32 a);

/* Forwards the word at +0xC of the object to func_00302768. */
void func_002EFCB8(void *obj) {
    func_00302768(*(s32 *)((u8 *)obj + 0xC));
}
