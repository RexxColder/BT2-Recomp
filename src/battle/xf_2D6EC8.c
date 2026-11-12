#include "common.h"

void func_002D7A80(s32 a, f32 f12, f32 f13);
void func_002D7B18(s32 a);

/* Forwards the word at +0x24 of the object to func_002D7A80 (f12/f13 pass through). */
void func_002D6EC8(void *obj, f32 f12, f32 f13) {
    func_002D7A80(*(s32 *)((u8 *)obj + 0x24), f12, f13);
}

/* Forwards the word at +0x24 of the object to func_002D7B18. */
void func_002D6EE0(void *obj) {
    func_002D7B18(*(s32 *)((u8 *)obj + 0x24));
}
