#include "common.h"

void func_002D61C0(s32 a);

/* Forwards the word at +0xA8 of the object to func_002D61C0. */
void func_002BABF0(void *obj) {
    func_002D61C0(*(s32 *)((u8 *)obj + 0xA8));
}
