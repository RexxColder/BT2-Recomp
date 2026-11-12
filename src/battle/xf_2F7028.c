#include "common.h"

void func_002F17A8(s32 a);

/* Forwards the word at +0x4 of the object to func_002F17A8. */
void func_002F7028(void *obj) {
    func_002F17A8(*(s32 *)((u8 *)obj + 0x4));
}
