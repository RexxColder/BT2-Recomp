#include "common.h"

extern s32 func_002D07B0();
extern void func_002D4108(u8 *obj);
extern s32 func_002D4258();
extern void func_002D41D0();

/* 0x002D40B0: if func_002D07B0(obj, 5) is nonzero, run the helpers and return func_002D4258(obj); else return the (zero) result. */
s32 func_002D40B0(u8 *obj) {
    s32 r = func_002D07B0(obj, 5);
    s32 saved;

    if (r == 0) {
        return r;
    }
    func_002D4108(obj);
    saved = func_002D4258(obj);
    func_002D41D0(obj);
    return saved;
}
