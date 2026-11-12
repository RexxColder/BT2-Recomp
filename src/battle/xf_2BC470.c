#include "common.h"

/* Wrappers of the facade table: each forwards its arguments to one callee (no arguments are touched). */
void func_00306F28(void);
void func_00306F40(void);
void func_00306F58(void);
void func_00306F70(void);
void func_00306FA0(void);
void func_00306FB8(void);
void func_00306FD0(void);
void func_00306FE8(void);

/* Calls func_00306F28, returns 1. */
s32 func_002BC470(void) {
    func_00306F28();
    return 1;
}

/* Tail call to func_00306FA0. */
void func_002BC490(void) {
    func_00306FA0();
}

/* Calls func_00306F40, returns 1. */
s32 func_002BC4A8(void) {
    func_00306F40();
    return 1;
}

/* Tail call to func_00306FB8. */
void func_002BC4C8(void) {
    func_00306FB8();
}

/* Calls func_00306F58, returns 1. */
s32 func_002BC4E0(void) {
    func_00306F58();
    return 1;
}

/* Tail call to func_00306FD0. */
void func_002BC500(void) {
    func_00306FD0();
}

/* Calls func_00306F70, returns 1. */
s32 func_002BC518(void) {
    func_00306F70();
    return 1;
}

/* Tail call to func_00306FE8. */
void func_002BC538(void) {
    func_00306FE8();
}
