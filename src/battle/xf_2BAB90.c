#include "common.h"

void func_002D6188(s32 a);

/* Forwards the word at +0xA8 of the object to func_002D6188. */
void func_002BAB90(void *obj) {
    func_002D6188(*(s32 *)((u8 *)obj + 0xA8));
}
