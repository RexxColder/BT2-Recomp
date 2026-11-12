#include "common.h"

void func_002E7BD0(s32 a);
void func_002E7BD8(s32 a);
void func_002E7BE0(s32 a);

/* Forwards the word at +0x4 of the object to func_002E7BD0. */
void func_002F15E8(void *obj) {
    func_002E7BD0(*(s32 *)((u8 *)obj + 0x4));
}

/* Forwards the word at +0x4 of the object to func_002E7BD8. */
void func_002F1600(void *obj) {
    func_002E7BD8(*(s32 *)((u8 *)obj + 0x4));
}

/* Forwards the word at +0x4 of the object to func_002E7BE0. */
void func_002F1618(void *obj) {
    func_002E7BE0(*(s32 *)((u8 *)obj + 0x4));
}
