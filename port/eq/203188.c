#include "common.h"

extern s32 func_00202E60();
extern s32 func_002031E0();

/* 0x00203188: returns obj->+0x118C (re-read after func_002031E0 when it equals +0x1180). */
s32 func_00203188(u8 *obj) {
    s32 v;

    if (func_00202E60(obj, *(s32 *)(obj + 0x118C)) == 0) {
        func_002031E0(obj);
    }
    v = *(s32 *)(obj + 0x118C);
    if (v == *(s32 *)(obj + 0x1180)) {
        func_002031E0(obj);
        return *(s32 *)(obj + 0x118C);
    }
    return v;
}
