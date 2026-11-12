#include "common.h"

extern void func_002C4DB8();
extern void func_002C4AA8();
extern void func_002C4E68();
extern void func_002C4CC0();
extern void func_002C4F00();
extern void func_002C4FB0();

/* 0x002C4A50: runs six helpers on obj; the first fills two s32 out values at sp+0 and sp+4. */
void func_002C4A50(u8 *obj) {
    u8 sp[8];

    func_002C4DB8(obj, sp, sp + 4);
    func_002C4AA8(obj);
    func_002C4E68(obj);
    func_002C4CC0(obj);
    func_002C4F00(obj);
    func_002C4FB0(obj);
}
