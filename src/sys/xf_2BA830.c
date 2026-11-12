#include "common.h"

void func_002D6FA0(s32 a);
void func_002D6FA8(s32 a);
void func_002D6FB0(s32 a);
void func_002D6FB8(s32 a);
void func_002D6CD0(void);
void func_002D6CE0(void);

/* Forwards the word at +0xA8 of the object to func_002D6FA0. */
void func_002BA830(void *obj) {
    func_002D6FA0(*(s32 *)((u8 *)obj + 0xA8));
}

/* Forwards the word at +0xA8 of the object to func_002D6FA8. */
void func_002BA848(void *obj) {
    func_002D6FA8(*(s32 *)((u8 *)obj + 0xA8));
}

/* Forwards the word at +0xA8 of the object to func_002D6FB0. */
void func_002BA860(void *obj) {
    func_002D6FB0(*(s32 *)((u8 *)obj + 0xA8));
}

/* Forwards the word at +0xA8 of the object to func_002D6FB8. */
void func_002BA878(void *obj) {
    func_002D6FB8(*(s32 *)((u8 *)obj + 0xA8));
}

/* Calls func_002D6CD0 with no argument. */
void func_002BA890(void) {
    func_002D6CD0();
}

/* Calls func_002D6CE0 with no argument. */
void func_002BA8A8(void) {
    func_002D6CE0();
}
