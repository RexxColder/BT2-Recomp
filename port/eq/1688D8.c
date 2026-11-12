#include "common.h"

s32 func_001F3758(s32 arg0);
extern void func_00168500();
extern void func_0014EEF8();
extern s32 func_00147FB8();

s32 func_001688D8(u8 *task) {
    u8 *obj = *(u8 **)(task + 0x38);
    u8 *other = *(u8 **)(func_001F3758((s32)task) + 0x38);
    u8 *child;
    u8 *info;

    child = *(u8 **)(obj + 0x120);
    func_00168500(task);
    func_0014EEF8(other, obj + 0x124);
    info = *(u8 **)(child + 0x20);
    if (*(s32 *)(info + 4) != 0) {
        return func_00147FB8(*(s32 *)child);
    }
    return (s32)info;
}
