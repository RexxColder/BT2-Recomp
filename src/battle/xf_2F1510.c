#include "common.h"

void func_002E7B80(s32 a);
void func_002E7B88(s32 a);
void func_002E7B90(s32 a);
void func_002E7B98(s32 a);
void func_002E7BA0(s32 a);
void func_002E7BA8(s32 a);
void func_002E7BB0(s32 a);

/* Forwards the word at +0x4 of the object to func_002E7B80. */
void func_002F1510(void *obj) {
    func_002E7B80(*(s32 *)((u8 *)obj + 0x4));
}

/* Forwards the word at +0x4 of the object to func_002E7B88. */
void func_002F1528(void *obj) {
    func_002E7B88(*(s32 *)((u8 *)obj + 0x4));
}

/* Forwards the word at +0x4 of the object to func_002E7B90. */
void func_002F1540(void *obj) {
    func_002E7B90(*(s32 *)((u8 *)obj + 0x4));
}

/* Forwards the word at +0x4 of the object to func_002E7B98. */
void func_002F1558(void *obj) {
    func_002E7B98(*(s32 *)((u8 *)obj + 0x4));
}

/* Forwards the word at +0x4 of the object to func_002E7BA8. */
void func_002F1570(void *obj) {
    func_002E7BA8(*(s32 *)((u8 *)obj + 0x4));
}

/* Forwards the word at +0x4 of the object to func_002E7BA0. */
void func_002F1588(void *obj) {
    func_002E7BA0(*(s32 *)((u8 *)obj + 0x4));
}

/* Forwards the word at +0x4 of the object to func_002E7BB0. */
void func_002F15A0(void *obj) {
    func_002E7BB0(*(s32 *)((u8 *)obj + 0x4));
}
