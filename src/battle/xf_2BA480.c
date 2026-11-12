#include "common.h"

void func_002D6EC8(s32 a, f32 f12, f32 f13);
void func_002D6EE0(s32 a);

/* Forwards the word at +0xA8 of the object to func_002D6EC8 (f12/f13 pass through). */
void func_002BA480(void *obj, f32 f12, f32 f13) {
    func_002D6EC8(*(s32 *)((u8 *)obj + 0xA8), f12, f13);
}

/* Forwards the word at +0xA8 of the object to func_002D6EE0. */
void func_002BA498(void *obj) {
    func_002D6EE0(*(s32 *)((u8 *)obj + 0xA8));
}
